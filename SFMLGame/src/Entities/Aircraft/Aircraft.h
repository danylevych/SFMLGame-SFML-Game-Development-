#pragma once

#include "../Entity/Entity.h"
#include "../../Holders/Holders.h"

#include <SFML/Graphics/Sprite.hpp>


/////////////////////////////////////////////////
// \brief
//	  The class represents the user aircraft.
// 
/////////////////////////////////////////////////
class Aircraft : public Entity
{
public:
	// This is the type for the aircraft.
	enum class Type
	{
		Ealge,
		Raptor
	};

private:
	Type type;
	sf::Sprite sprite;

public:
	Aircraft(Type type, TextureHolder& textures);

	virtual ~Aircraft() = default;

public:
	////////////////////////////////////////////////////
	// \brief
	//		An overloaded method of SceneNode
	//		for the class.
	// 
	////////////////////////////////////////////////////
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	////////////////////////////////////////////////////
	// \brief
	//		Return the category of the entity.
	// 
	////////////////////////////////////////////////////
	virtual uint32_t GetCategory() const override;

	////////////////////////////////////////////////////
	// \brief
	//		Converts the Aircraft::Type to 
	//		Textures::TextureID.
	////////////////////////////////////////////////////
	static Textures::TextureID ToTextureID(Type type);
};

