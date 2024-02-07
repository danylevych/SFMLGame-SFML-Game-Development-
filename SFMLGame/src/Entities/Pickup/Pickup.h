#pragma once

#include "../Entity/Entity.h"
#include <SFML/Graphics/Sprite.hpp>
#include "../../Holders/Holders.h"
#include "../Aircraft/Aircraft.h"


class Pickup : public Entity
{
public:
	enum Type
	{
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		TypeCount
	};

private:
	Type type;
	sf::Sprite sprite;

public:
	Pickup(Pickup::Type type, const TextureHolder& textures);

	virtual ~Pickup() override = default;

public: // Override section.
	//////////////////////////////////////////////////
	// \brief
	//     Override GetCategory for the class.
	// 
	//////////////////////////////////////////////////
	virtual unsigned int GetCategory() const override;

	//////////////////////////////////////////////////
	// \brief
	//   Return the bounds for the instance in the
	//   game world.
	// 
	//////////////////////////////////////////////////
	virtual sf::FloatRect GetBoundingRect() const;

private:
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void Apply(Aircraft& player) const;

};

