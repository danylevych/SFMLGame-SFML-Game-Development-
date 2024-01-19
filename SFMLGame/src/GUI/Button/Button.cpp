#include "Button.h"

GUI::Button::Button(TextureHolder& textures, FontHolder& fonts)
	: Component()
	, callback()
	, isToggle(false)
	, text("", fonts.Get(Font::FontID::Main), 16)
	, normalTesxture(textures.Get(Textures::TextureID::ButtonNormal))
	, selectedTexture(textures.Get(Textures::TextureID::ButtonSelected))
	, pressedTexture(textures.Get(Textures::TextureID::ButtonPressed))
	, sprite(normalTesxture)
{
	// Set text on the center of the sprite button.
	sf::FloatRect buttonBounds = sprite.getLocalBounds();
	text.setPosition(buttonBounds.width / 2.f, buttonBounds.height / 2.f);
}

void GUI::Button::SetCallBack(Callback callback)
{
	this->callback = std::move(callback);
}

void GUI::Button::SetText(const std::string& text)
{
	this->text.setString(text);

	// Set te origin of the text in its center.
	sf::FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
}

void GUI::Button::SetToggle(bool flag)
{
	isToggle = flag;
}


bool GUI::Button::IsSelectable() const
{
	return true;
}

void GUI::Button::HandleEvent(const sf::Event& event)
{
}

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
	target.draw(text, states);
}

void GUI::Button::Select()
{
	Component::Select();
	sprite.setTexture(selectedTexture);
}

void GUI::Button::Deselect()
{
	Component::Deselect();
	sprite.setTexture(normalTesxture);
}

void GUI::Button::Activate()
{
	Component::Activate();

	// If we are toggle then we should show that the button is pressed.
	if (isToggle)
	{
		sprite.setTexture(pressedTexture);
	}

	// Turns out the std::function has an overloaded method that cast it 
	// to bool type. If the instance is empty it returns false. Under the
	// "empty" word I mean, that instance doesn't have any tied function.
	if (callback)
	{
		callback();
	}

	if (!isToggle)
	{
		Deactivate();
	}
}

void GUI::Button::Deactivate()
{
	Component::Deactivate();

	if (isToggle)
	{
		// Reset the texture settings.
		if (IsSelected())
		{
			sprite.setTexture(selectedTexture);
		}
		else
		{
			sprite.setTexture(normalTesxture);
		}
	}
}
