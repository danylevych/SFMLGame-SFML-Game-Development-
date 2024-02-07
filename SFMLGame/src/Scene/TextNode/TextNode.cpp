#include "TextNode.h"

#include "../../Tools/Utility.h"


TextNode::TextNode(const FontHolder& fonts, const std::string& text)
	: SceneNode()
	, text(text, fonts.Get(Font::FontID::Main), 20)
{
	CenteredUnit(this->text);
}

void TextNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void TextNode::SetString(const std::string& text)
{
	this->text.setString(text);
	CenteredUnit(this->text);
}
