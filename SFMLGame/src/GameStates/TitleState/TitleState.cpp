#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, background(context.textures->Get(Textures::TextureID::TitleScreen))
	, label("Press any key to continue...", context.fonts->Get(Font::FontID::Main))
	, isTextShown(false)
{	
	// Set the label in the correct position.
	sf::FloatRect labelSize = label.getLocalBounds();
	sf::Vector2u windowSize = context.window->getSize();

	label.setOrigin(labelSize.width / 2.f, labelSize.height / 2.f); // Set origin in the centre.
	label.setPosition(windowSize.x / 2.f, windowSize.y / 2.f); // Set pos to the center of screen.
}

void TitleState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	window->clear(sf::Color::Black);
	window->draw(background);
	if (isTextShown)
	{
		window->draw(label);
	}
}

bool TitleState::Update(sf::Time deltaTime)
{
	static sf::Time blinkAnimTime = sf::Time::Zero;

	blinkAnimTime += deltaTime;

	if (blinkAnimTime >= LABEL_ANIME_TIME)
	{
		isTextShown = !isTextShown;
		blinkAnimTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		RequestStackPop(); // Delete the current state.
		RequestStackPush(States::ID::Menu); // Open a new state of the app.
	}

	return true;
}
