#pragma once

#include "../../Scene/SceneNode/SceneNode.h"
#include <SFML/System/Vector2.hpp>


//////////////////////////////////////////////////
// \brief
//		This is the class that represents
//		the entity in our game.
// 
//////////////////////////////////////////////////
class Entity : public SceneNode
{
private:
	sf::Vector2f velocity;

public:
	Entity() = default;

	// We need to set the virtual word before
	// destructor definition because we use 
	// the inheritance.
	virtual ~Entity() = default;

public:
	///////////////////////////////////////////////////////
	// \brief
	// 		Returns to user the velocity value.
	// 
	///////////////////////////////////////////////////////
	sf::Vector2f GetVelocity() const;


	///////////////////////////////////////////////////////
	// \brief
	//    These set the velocity value for the entity.
	// 
	///////////////////////////////////////////////////////
	void SetVelocity(float x, float y);
	void SetVelocity(sf::Vector2f velocity);

private:
	///////////////////////////////////////////////////////
	// \brief
	//		Overloading the updating for the instance.
	// 
	///////////////////////////////////////////////////////
	virtual void UpdateCurrent(sf::Time delta) override;
};

