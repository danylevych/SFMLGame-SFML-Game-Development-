#pragma once

#include "../../Enums/TextureID.h"
#include <SFML/System/Time.hpp>
#include <vector>
#include <functional>

class Aircraft;

struct Direction
{
	Direction(float angle, float distance) : angle(angle), distance(distance) {	}

	float angle;
	float distance;
};

struct AircraftData
{
	int hitpoints;
	float speed;
	Textures::TextureID texture;
	std::vector<Direction> directuins;
	sf::Time fireInterval;
};

struct ProjectileData
{
	int damage;
	float speed;
	Textures::TextureID texture;
};

struct PickupData
{
	std::function<void(Aircraft&)> action;
	Textures::TextureID texture;
};


std::vector<AircraftData> InitializeAircraftData();
std::vector<ProjectileData> InitializeProjectileData();
std::vector<PickupData> InitializePickupData();
