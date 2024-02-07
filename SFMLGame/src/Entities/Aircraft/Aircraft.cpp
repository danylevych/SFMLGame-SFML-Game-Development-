#include "Aircraft.h"

#include "../../Enums/Category.h"
#include "../../Utilities/DataTables/DataTables.h"
#include "../../Tools/Utility.h"
#include "../Pickup/Pickup.h"


// This syntaxis means, that we create a variable, that only
// will be accesible in the file, in other words it will be internal.
namespace
{
	const std::vector<AircraftData> DATA_TABLE = InitializeAircraftData();
}


Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
	: Entity(DATA_TABLE[type].hitpoints)
	, type(type)
	, sprite(textures.Get(ToTextureID(type)))
	, traveledDistance(0.f)
	, directionIndex(0)

	, fireCommand()
	, missileCommand()
	, dropPickupCommand()

	, isFiring(false)
	, isLaunchingMissile(false)
	, isMarkedForRemoval(false)

	, missileAmmo(2)
	, spreadLevel(1)
	, fireRateLevel(1)

	, fireCountDown(sf::Time::Zero)
{	

	// Get the bounds in the entity's coordinate system,
	// thus without entity transformation.
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // Origin pos in the center.

	InitCommands(textures);
	InitTexts(fonts);

	UpdateText();
}

void Aircraft::InitCommands(const TextureHolder& textures)
{
	fireCommand.category = Category::SceneAirLauer;
	fireCommand.action = [this, &textures](SceneNode& node, sf::Time deltaTime) {
		CreateBullets(node, textures);
	};

	missileCommand.category = Category::SceneAirLauer;
	missileCommand.action = [this, &textures](SceneNode& node, sf::Time deltaTime) {
		CreateProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
	};

	dropPickupCommand.category = Category::Pickup;
	dropPickupCommand.action = [this, &textures](SceneNode& node, sf::Time deltaTime) {
		CreatePickup(node, textures);
	};
}

void Aircraft::InitTexts(const FontHolder& fonts)
{
	// Init the hitpoint text.
	std::unique_ptr<TextNode> health(new TextNode(fonts));
	hitpointsText = health.get();
	AttachChild(std::move(health));

	if (GetCategory() == Category::PlayerAircraft)
	{
		std::unique_ptr<TextNode> missileText(new TextNode(fonts));
		missileText->setPosition(0, 70);
		missileDisplay = missileText.get();
		AttachChild(std::move(missileText));
	}
}

void Aircraft::DrawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

uint32_t Aircraft::GetCategory() const
{
	switch (type)
	{
	case Aircraft::Type::Ealge:
		return Category::PlayerAircraft;
	
	default:
		return Category::EnemyAircraft;
	}
}

void Aircraft::UpdateCurrent(sf::Time deltaTime, CommandQueue& commands)
{
	if (IsDestroyed())
	{
		CheckPicupDrop(commands);

		isMarkedForRemoval = true;
		return;
	}

	// Check is bulets or missile are fired.
	CheckProjectileLaunch(deltaTime, commands);

	UpdateMovementPattern(deltaTime);
	Entity::UpdateCurrent(deltaTime, commands);
	UpdateText();
}

sf::FloatRect Aircraft::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

float_t Aircraft::GetMaxSpeed() const
{
	return DATA_TABLE[type].speed;
}

void Aircraft::Fire()
{
	// Only with fire interval != 0 are able to fire.
	if (DATA_TABLE[type].fireInterval != sf::Time::Zero)
	{
		isFiring = true;
	}
}

void Aircraft::LaunchMissile()
{
	if (missileAmmo > 0)
	{
		isLaunchingMissile = true;
		missileAmmo--;
	}
}

bool Aircraft::IsAllied() const
{
	return type == Ealge;
}

void Aircraft::IncreaseFireRate()
{
	if (fireRateLevel < 10)
	{
		fireRateLevel++;
	}
}

void Aircraft::IncreaSpread()
{
	if (spreadLevel < 3)
	{
		spreadLevel++;
	}
}

void Aircraft::CollectMissile(uint32_t count)
{
	missileAmmo += count;
}

bool Aircraft::IsMarkedForRemoval() const
{
	return isMarkedForRemoval;
}

void Aircraft::UpdateText()
{
	hitpointsText->SetString(std::to_string(GetHitpoints()) + " HP");
	hitpointsText->setPosition(0.f, 50.f);
	//hitpointsText->setRotation(getRotation());

	if (missileDisplay)
	{
		if (missileAmmo == 0) // Player doesn't have any missiles.
		{
			missileDisplay->SetString("");
		}
		else
		{
			missileDisplay->SetString("M: " + std::to_string(missileAmmo));
		}
	}
}

void Aircraft::UpdateMovementPattern(sf::Time deltaTime)
{
	// Enemy airplane movement.
	const auto& directions = DATA_TABLE[type].directuins;
	
	if (!directions.empty())
	{
		// Change the vector of direction.
		if (traveledDistance > directions[directionIndex].distance)
		{
			directionIndex = (directionIndex + 1) % directions.size();
			traveledDistance = 0.f;
		}

		// Compute velocity from direction.
		float radians = ToRadian(directions[directionIndex].angle + 90.f); // "+ 90.f" because we work with inersed cord system.
		float vx = GetMaxSpeed() * std::cos(radians);
		float vy = GetMaxSpeed() * std::sin(radians);

		SetVelocity(vx, vy);

		traveledDistance += GetMaxSpeed() * deltaTime.asSeconds();
	}
}

void Aircraft::CheckProjectileLaunch(sf::Time deltaTime, CommandQueue& commands)
{
	// Enemies try to fire all the time.
	if (!IsAllied())
	{
		Fire();
	}
	
	if (isFiring && fireCountDown <= sf::Time::Zero)
	{
		commands.Push(fireCommand);
		fireCountDown += sf::seconds(1.f / (fireRateLevel + 1));
		isFiring = false;
	}
	else if (fireCountDown > sf::Time::Zero)
	{
		fireCountDown -= deltaTime;
		isFiring = false;
	}

	// Check for missile launch.
	if (isLaunchingMissile)
	{
		commands.Push(missileCommand);
		isLaunchingMissile = false;
	}
}

void Aircraft::CreateBullets(SceneNode& node, const TextureHolder& textures) const
{
	Projectile::Type type = IsAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (spreadLevel)
	{
	case 1:
		CreateProjectile(node, type, 0.0f, 0.5f, textures);
		break;

	case 2:
		CreateProjectile(node, type, -0.33f, 0.33f, textures);
		CreateProjectile(node, type, +0.33f, 0.33f, textures);
		break;

	case 3:
		CreateProjectile(node, type, -0.5f, 0.33f, textures);
		CreateProjectile(node, type, -0.0f, 0.5f, textures);
		CreateProjectile(node, type, +0.5f, 0.33f, textures);
		break;
	}
}

void Aircraft::CreateProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
	std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

	sf::Vector2f offset(xOffset * sprite.getGlobalBounds().width, yOffset * sprite.getGlobalBounds().height);
	sf::Vector2f velocity(0, projectile->GetMaxSpeed());

	float sign = IsAllied() ? -1.f : 1.f;
	projectile->setPosition(GetWorlPosition() + offset * sign);
	projectile->SetVelocity(velocity * sign);

	node.AttachChild(std::move(projectile));
}

void Aircraft::CheckPicupDrop(CommandQueue& commands)
{
	// If the aircraft is not an allied one and the RandInt() return 0,
	// we can create the pickup.
	if (!IsAllied() && RandInt(3) == 0)
	{
		commands.Push(dropPickupCommand);
	}
}

void Aircraft::CreatePickup(SceneNode& node, const TextureHolder& textures)
{
	Pickup::Type typePickup = static_cast<Pickup::Type>(RandInt(Pickup::Type::TypeCount));

	std::unique_ptr<Pickup> pickup(new Pickup(typePickup, textures));
	pickup->setPosition(GetWorlPosition());
	pickup->SetVelocity(0.f, 1.f);
	node.AttachChild(std::move(pickup));
}

Textures::TextureID Aircraft::ToTextureID(Type type)
{
	switch (type)
	{
	case Aircraft::Type::Ealge:
		return Textures::TextureID::Eagle;

	case Aircraft::Type::Raptor:
		return Textures::TextureID::Raptor;

	case Aircraft::Type::Avenger:
		return Textures::TextureID::Avenger;
	}
}
