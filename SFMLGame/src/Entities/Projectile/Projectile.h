#pragma once

#include "../Entity/Entity.h"
#include "../../Holders/Holders.h"
#include <SFML/Graphics/Sprite.hpp>


//////////////////////////////////////////
// \brief
//    Represents the projectile for 
//    an aircraft.
// 
//////////////////////////////////////////
class Projectile : public Entity
{
public:
	enum Type
	{
		AlliedBullet,
		EnemyBullet,
		Missile,
		TypeCount
	};

private:
	Type type;
	sf::Sprite sprite;
	sf::Vector2f targetDirection;

public:
	Projectile(Type type, const TextureHolder& textures);

	virtual ~Projectile() override = default;

public:
	void GuideTowards(sf::Vector2f position);
	bool IsGuided() const;

	virtual unsigned int GetCategory() const;
	virtual sf::FloatRect GetBoundingRect() const;
	float GetMaxSpeed() const;
	int GetDamage() const;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void UpdateCurrent(sf::Time deltaTime, CommandQueue& commands) override;

};

