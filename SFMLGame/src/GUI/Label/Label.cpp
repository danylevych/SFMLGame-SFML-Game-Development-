#include "Label.h"

#include <SFML/Graphics/Color.hpp>


GUI::Label::Label(const std::string& text, FontHolder& fonts, size_t charSize)
	: text(text, fonts.Get(Font::FontID::Main), charSize)
{	}

bool GUI::Label::IsSelectable() const
{
	return false;
}

void GUI::Label::HandleEvent(const sf::Event& event)
{	}

void GUI::Label::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(text, states);
}

void GUI::Label::SetFont(const sf::Font& font)
{
	text.setFont(font);
}

void GUI::Label::SetString(const std::string& text)
{
	this->text.setString(text);
}

void GUI::Label::SetCharacterSize(size_t size)
{
	text.setCharacterSize(size);
}

void GUI::Label::SetFontColor(const sf::Color& color)
{
	text.setFillColor(color);
}
