#include "DataTables.h"

#include "../../Entities/Aircraft/Aircraft.h"
#include "../../Entities/Projectile/Projectile.h"
#include "../../Entities/Pickup/Pickup.h"

std::vector<AircraftData> InitializeAircraftData()
{
	size_t size = static_cast<size_t>(Aircraft::Type::TypeCount);
	std::vector<AircraftData> data(size);

	size_t eagleIndex = static_cast<size_t>(Aircraft::Type::Ealge);
	size_t raptorIndex = static_cast<size_t>(Aircraft::Type::Raptor);
	size_t avengerIndex = static_cast<size_t>(Aircraft::Type::Avenger);

	// Init eagle.
	data[eagleIndex].hitpoints = 100;
	data[eagleIndex].speed = 200.f;
	data[eagleIndex].fireInterval = sf::seconds(1.f);
	data[eagleIndex].texture = Textures::TextureID::Eagle;

	// Init raptor.
	data[raptorIndex].hitpoints = 20;
	data[raptorIndex].speed = 80.f;
	data[raptorIndex].texture = Textures::TextureID::Raptor;
	data[raptorIndex].fireInterval = sf::Time::Zero;
	data[raptorIndex].directuins.push_back(Direction(+45.f, 80.f));
	data[raptorIndex].directuins.push_back(Direction(-45.f, 160.f));
	data[raptorIndex].directuins.push_back(Direction(+45.f, 80.f));

	// Init avender.
	data[avengerIndex].hitpoints = 40;
	data[avengerIndex].speed = 50.f;
	data[avengerIndex].texture = Textures::TextureID::Avenger;
	data[avengerIndex].fireInterval = sf::seconds(2.f);
	data[avengerIndex].directuins.push_back(Direction(+45.f, 50.f));
	data[avengerIndex].directuins.push_back(Direction(  0.f, 50.f));
	data[avengerIndex].directuins.push_back(Direction(-45.f, 100.f));
	data[avengerIndex].directuins.push_back(Direction(  0.f, 50.f));
	data[avengerIndex].directuins.push_back(Direction(+45.f, 50.f));

	return data;
}

std::vector<ProjectileData> InitializeProjectileData()
{
	std::vector<ProjectileData> data(Projectile::Type::TypeCount);

	data[Projectile::AlliedBullet].damage = 10;
	data[Projectile::AlliedBullet].speed = 300.f;
	data[Projectile::AlliedBullet].texture = Textures::TextureID::Bullet;

	data[Projectile::EnemyBullet].damage = 10;
	data[Projectile::EnemyBullet].speed = 300.f;
	data[Projectile::EnemyBullet].texture = Textures::TextureID::Bullet;

	data[Projectile::Missile].damage = 200;
	data[Projectile::Missile].speed = 150.f;
	data[Projectile::Missile].texture = Textures::TextureID::Missile;

	return data;
}

std::vector<PickupData> InitializePickupData()
{
	using namespace std::placeholders;

	std::vector<PickupData> data(Pickup::TypeCount);

	data[Pickup::HealthRefill].texture = Textures::TextureID::HealthRefill;
	data[Pickup::HealthRefill].action = std::bind(&Aircraft::Repair, _1, 25);

	data[Pickup::MissileRefill].texture = Textures::TextureID::MissileRefill;
	data[Pickup::MissileRefill].action = std::bind(&Aircraft::CollectMissile, _1, 3);

	data[Pickup::FireSpread].texture = Textures::TextureID::FireSpread;
	data[Pickup::FireSpread].action = std::bind(&Aircraft::IncreaSpread, _1);

	data[Pickup::FireRate].texture = Textures::TextureID::FireRate;
	data[Pickup::FireRate].action = std::bind(&Aircraft::IncreaseFireRate, _1);

	return std::vector<PickupData>();
}
