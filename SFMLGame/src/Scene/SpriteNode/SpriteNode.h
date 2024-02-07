#pragma once

#include "../SceneNode/SceneNode.h"

#include <SFML/Graphics/Sprite.hpp>


////////////////////////////////////////////////
// \brief
//		The class that represent the 
//		sprite nodes.
// 
////////////////////////////////////////////////
class SpriteNode : public SceneNode
{
public:
	using Ptr = std::unique_ptr<SpriteNode>;

private:
	sf::Sprite sprite;

public:
	////////////////////////////////////////////////
	// \brief
	//		Constructor that takes a texture
	//		that will be applied for the sprite.
	// 
	////////////////////////////////////////////////
	SpriteNode(const sf::Texture& texture);

	////////////////////////////////////////////////
	// \brief
	//		Constructor that takes the texture
	//		that will be apllied for the sprite
	//		and the rectangle.
	// 
	////////////////////////////////////////////////
	SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

public:
	////////////////////////////////////////////////
	// \brief
	//		Overloaded method which draw the
	//		instance on the world.
	// 
	////////////////////////////////////////////////
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
};
