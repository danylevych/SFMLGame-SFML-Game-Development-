#include "Aircraft.h"

Aircraft::Aircraft(Type type, TextureHolder& textures)
	: type(type)
	, sprite(textures.Get(ToTextureID(type)))
{	
	// Get the bounds in the entity's coordinate system,
	// thus without entity transformation.
	sf::FloatRect bounds = sprite.getLocalBounds();

	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // Origin pos in the center.
}


void Aircraft::DrawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}


Textures::TextureID Aircraft::ToTextureID(Type type)
{
	switch (type)
	{
	case Aircraft::Type::Ealge:
		return Textures::TextureID::Eagle;

	case Aircraft::Type::Raptor:
		return Textures::TextureID::Raptor;
	}
}
