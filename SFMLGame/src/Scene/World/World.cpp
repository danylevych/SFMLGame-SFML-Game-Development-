#include "World.h"


#include "../SpriteNode/SpriteNode.h"
#include "../../Entities/Pickup/Pickup.h"


World::World(sf::RenderWindow& window, FontHolder& fonts)
	: window(window)
	, view(window.getDefaultView())
	, textures()
	, sceneGraph()
	, sceneLayers()
	, worldBounds(0.f, 0.f, view.getSize().x, 2000.f)
	, spawnPos(window.getSize().x / 2.f, worldBounds.height - view.getSize().y / 2.f)
	, scrollSpeed(-50.f)
	, playerAircraft(nullptr)
	, fonts(fonts)
	, enemySpawnPoints()
	, activeEnemies()
{
	LoadTextures();
	BuildScene();
	
	// Prepare the view.
	view.setCenter(spawnPos);
}

void World::Update(sf::Time delta)
{
	view.move(0.f, scrollSpeed * delta.asSeconds());
	playerAircraft->SetVelocity(0.f, 0.f);
	
	DestroyEntitiesOutsideView();
	GuideMissiles();

	// Forward commands to the scene graph.
	while (!commandQueue.IsEmpty())
	{
		sceneGraph.OnCommand(commandQueue.Pop(), delta);
	}

	AdaptPlayerVelocity();

	HandleCollision();
	sceneGraph.RemoveWrecks();
	SpawnEnemies();

	sceneGraph.Update(delta, commandQueue);
	AdaptPlayerPosition();
}

void World::Draw()
{
	window.setView(view);
	window.draw(sceneGraph);
}

CommandQueue& World::GetCommandQueue()
{
	return commandQueue;
}

bool World::HasAlivePlayer() const
{
	return !playerAircraft->IsMarkedForRemoval();
}

bool World::HasPlayerReachedEnd() const
{
	return !worldBounds.contains(playerAircraft->getPosition());
}

void World::LoadTextures()
{
	// Load airctaft's textures
	textures.Load(Textures::TextureID::Eagle,   "data/Textures/Eagle.png");
	textures.Load(Textures::TextureID::Raptor,  "data/Textures/Raptor.png");
	textures.Load(Textures::TextureID::Avenger, "data/Textures/Avenger.png");

	// Load map's texture.
	textures.Load(Textures::TextureID::Desert, "data/Textures/Desert.png");
	
	// Load projectile's textures.
	textures.Load(Textures::TextureID::Bullet,  "data/Textures/Bullet.png");
	textures.Load(Textures::TextureID::Missile, "data/Textures/Missile.png");

	// Load pickup's textures.
	textures.Load(Textures::TextureID::HealthRefill,  "data/Textures/HealthRefill.png");
	textures.Load(Textures::TextureID::MissileRefill, "data/Textures/MissileRefill.png");
	textures.Load(Textures::TextureID::FireRate,      "data/Textures/FireRate.png");
	textures.Load(Textures::TextureID::FireSpread,    "data/Textures/FireSpread.png");
}

void World::BuildScene()
{
	// Fill the sceneLayers and scene tree.
	for (auto& item : sceneLayers)
	{
		SceneNode::Ptr layer(new SceneNode());
		item = layer.get();
		sceneGraph.AttachChild(std::move(layer));
	}


	// Fill the world by our desert texture.
	sf::Texture& textureDesert = textures.Get(Textures::TextureID::Desert);
	sf::IntRect textureRect(worldBounds);
	textureDesert.setRepeated(true);

	// Creating a background scene.
	SpriteNode::Ptr backgroundSprite(new SpriteNode(textureDesert, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->AttachChild(std::move(backgroundSprite));

	// Creating user airplane.
	std::unique_ptr<Aircraft> aircraftPtr(new Aircraft(Aircraft::Type::Ealge, textures, fonts));
	playerAircraft = aircraftPtr.get();  // Tie the instance to aircraft.
	aircraftPtr->setPosition(spawnPos);
	aircraftPtr->SetVelocity(40.f, scrollSpeed);
	sceneLayers[Air]->AttachChild(std::move(aircraftPtr));

	AddEnemies();
}

void World::AdaptPlayerVelocity()
{
	sf::Vector2f velocity = playerAircraft->GetVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f) // Player is moving on a diagonal.
	{
		// Normalizing the diagonaly velocity of the player.
		playerAircraft->SetVelocity(velocity / std::sqrt(2.f));
	}

	// Add scroling velocity.
	playerAircraft->Accelerate(0.f, scrollSpeed);
}

void World::AdaptPlayerPosition()
{
	// Define the rectangle where our player can be.
	sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());
	const float DISTANCE_TO_BORDER = 45.f;
	
	// Don't allow player left the screen.
	sf::Vector2f playerPos = playerAircraft->getPosition();
	
	// Set the right point.
	playerPos.x = std::min<float>(playerPos.x, viewBounds.left + viewBounds.width - DISTANCE_TO_BORDER);
	
	// Set the left point.
	playerPos.x = std::max<float>(playerPos.x, viewBounds.left + DISTANCE_TO_BORDER);

	// Set the top point.
	playerPos.y = std::max<float>(playerPos.y, viewBounds.top + DISTANCE_TO_BORDER);

	// Set the bottom point.
	playerPos.y = std::min<float>(playerPos.y, viewBounds.top + viewBounds.height - DISTANCE_TO_BORDER);

	playerAircraft->setPosition(playerPos);
}

void World::GuideMissiles()
{
	// Setup commands that stores all enemies in activeEnemies.
	Command enemyColector;
	enemyColector.category = Category::EnemyAircraft;
	enemyColector.action = DerivedAction<Aircraft>([this](Aircraft& enemy, sf::Time) {
		if (!enemy.IsDestroyed())
		{
			activeEnemies.push_back(&enemy);
		}
	});

	// Setup command that guides the missile to the closest enemy to the player.
	Command missileGuider;
	missileGuider.category = Category::AlliedProjectile;
	missileGuider.action = DerivedAction<Projectile>([this](Projectile& missile, sf::Time) {
		// Ignore unguided bullets.
		if (!missile.IsGuided())
		{
			return;
		}

		float minDistance = std::numeric_limits<float>::max();
		Aircraft* closestEnemy = nullptr;

		for (auto& enemy : activeEnemies)
		{
			float enemyDistance = Distance(missile, *enemy);

			if (enemyDistance < minDistance)
			{
				minDistance = enemyDistance;
				closestEnemy = enemy;
			}
		}

		if (closestEnemy)
		{
			missile.GuideTowards(closestEnemy->getPosition());
		}
	});

	// Push commans and reset active enemies.
	commandQueue.Push(enemyColector);
	commandQueue.Push(missileGuider);
	activeEnemies.clear();
}

void World::HandleCollision()
{
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.CheckSceneCollision(sceneGraph, collisionPairs);

	for (auto& item : collisionPairs)
	{
		// The item has a type 'const SceneNode::Pair&' but MatchesCategories takes 'SceneNode::Pair&',
		// so we remove const from the reference.
		auto itemRef = const_cast<SceneNode::Pair&>(item);

		// Handle collision between player and enemy aircrafts.
		if (MatchesCategories(itemRef, Category::PlayerAircraft, Category::EnemyAircraft))
		{
			auto& player = dynamic_cast<Aircraft&>(*item.first);
			auto& enemy = dynamic_cast<Aircraft&>(*item.second);

			player.Damage(enemy.GetHitpoints());
			enemy.Destroy();
		}
		// Handle collision between a pickup and the player.
		else if (MatchesCategories(itemRef, Category::PlayerAircraft, Category::Pickup))
		{
			auto& player = dynamic_cast<Aircraft&>(*item.first);
			auto& pickup = dynamic_cast<Pickup&>(*item.second);

			pickup.Apply(player);
			pickup.Destroy();
		}
		// Handle the collision between projectiles and aircrafts types.
		else if (MatchesCategories(itemRef, Category::PlayerAircraft, Category::EnemyProjectile) ||
			     MatchesCategories(itemRef, Category::EnemyAircraft, Category::AlliedProjectile))
		{
			auto& aircraft = dynamic_cast<Aircraft&>(*item.first);
			auto& projectile = dynamic_cast<Projectile&>(*item.second);

			aircraft.Damage(projectile.GetDamage());
			projectile.Destroy();
		}
	}
}

void World::AddEnemies()
{
	// Add enemies to the spawn point container.
	AddEnemy(Aircraft::Raptor, 0.f, 500.f);
	AddEnemy(Aircraft::Raptor, 0.f, 1000.f);
	AddEnemy(Aircraft::Raptor, +100.f, 1100.f);
	AddEnemy(Aircraft::Raptor, -100.f, 1100.f);
	AddEnemy(Aircraft::Avenger, -70.f, 1400.f);
	AddEnemy(Aircraft::Avenger, -70.f, 1600.f);
	AddEnemy(Aircraft::Avenger, 70.f, 1400.f);
	AddEnemy(Aircraft::Avenger, 70.f, 1600.f);

	// Sort all enemies according to their y value.
	std::sort(enemySpawnPoints.begin(), enemySpawnPoints.end(), [](SpawnPoint left, SpawnPoint right) {
		return left.y < right.y;
	});
}

void World::AddEnemy(Aircraft::Type type, float x, float y)
{
	SpawnPoint spawn(type, spawnPos.x + x, spawnPos.y - y);
	enemySpawnPoints.push_back(spawn);
}

void World::SpawnEnemies()
{
	while (!enemySpawnPoints.empty() && enemySpawnPoints.back().y > GetBattlefieldBounds().top)
	{
		SpawnPoint spawn = enemySpawnPoints.back();

		std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, textures, fonts));
		enemy->setPosition(spawn.x, spawn.y);
		enemy->setRotation(180.f);

		sceneLayers[Air]->AttachChild(std::move(enemy));

		// Remove spawn pos for the spawned enemy.
		enemySpawnPoints.pop_back();
	}
}

void World::DestroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;

	command.action = DerivedAction<Entity>([this](Entity& entity, sf::Time) {
		if (!GetBattlefieldBounds().intersects(entity.GetBoundingRect()))
		{
			entity.Destroy();
		}
	});

	commandQueue.Push(command);
}

sf::FloatRect World::GetViewBounds() const
{
	return sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
}

sf::FloatRect World::GetBattlefieldBounds() const
{
	sf::FloatRect bounds = GetViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100.f;

	return bounds;
}

bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	uint32_t category1 = colliders.first->GetCategory();
	uint32_t category2 = colliders.second->GetCategory();

	// Make sure first pair entry has category type1 and second has type2.
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		// Swap the entries, because we need to have the first one order.
		std::swap(colliders.first, colliders.second);
		return true;
	}

	return false;
}
