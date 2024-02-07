#pragma once

#include "../../Holders/Holders.h"
#include "../SceneNode/SceneNode.h"

#include <string>
#include <SFML/Graphics/Text.hpp>


/////////////////////////////////////////////////////////
// \brief
//      Represents the text node for the scene.
// 
/////////////////////////////////////////////////////////
class TextNode : public SceneNode
{
private:
	sf::Text text;

public:
	TextNode(const FontHolder& fonts, const std::string& text = "");
	virtual ~TextNode() override = default;

private:
	/////////////////////////////////////////////////////
	// \brief 
	//		Override the drawing for the node.
	// 
	/////////////////////////////////////////////////////
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	/////////////////////////////////////////////////////
	// \brief
	//         Sets the text for the node.
	// 
	/////////////////////////////////////////////////////
	void SetString(const std::string& text);
};

