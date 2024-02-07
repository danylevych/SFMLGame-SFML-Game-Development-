#include "Projectile.h"

#include <cmath>
#include <cassert>
#include "../../Tools/Utility.h"
#include "../../Enums/Category.h"
#include "../../Utilities/DataTables/DataTables.h"


namespace
{
	const std::vector<ProjectileData> DATA_TABLE = InitializeProjectileData();
}


Projectile::Projectile(Type type, const TextureHolder& textures)
	: Entity(1)
	, type(type)
	, sprite(textures.Get(DATA_TABLE[type].texture))
	, targetDirection()
{
}

void Projectile::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Projectile::UpdateCurrent(sf::Time deltaTime, CommandQueue& commands)
{
	if (IsGuided())
	{
		const float APPOARCH_RATE = 200.f;

		sf::Vector2f newVelocity = UnitVector(APPOARCH_RATE * deltaTime.asSeconds() * targetDirection + GetVelocity());

		newVelocity *= GetMaxSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(ToDegree(angle) + 90.f);
		SetVelocity(newVelocity);
	}

	Entity::UpdateCurrent(deltaTime, commands);
}

void Projectile::GuideTowards(sf::Vector2f position)
{
	assert(IsGuided());
	targetDirection = UnitVector(position - GetWorlPosition());
}

bool Projectile::IsGuided() const
{
	return type == Missile;
}

unsigned int Projectile::GetCategory() const
{
	if (type == EnemyBullet)
	{
		return Category::EnemyProjectile;
	}
	else
	{
		return Category::AlliedProjectile;
	}
}

sf::FloatRect Projectile::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(sprite.getGlobalBounds());
}

float Projectile::GetMaxSpeed() const
{
	return DATA_TABLE[type].speed;
}

int Projectile::GetDamage() const
{
	return DATA_TABLE[type].damage;
}


