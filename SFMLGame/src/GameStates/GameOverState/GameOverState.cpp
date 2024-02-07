#include "GameOverState.h"
#include "../../Tools/Utility.h"
#include "../../Inputs/Player/Player.h"

#include <SFML/Graphics/RectangleShape.hpp>

GameOverState::GameOverState(StateStack& stack, Context context)
	: State(stack, context)
	, elipsedTime(sf::Time::Zero)
	, gameOverText()
{
	sf::Font& font = context.fonts->Get(Font::FontID::Main);
	Player* player = context.player;
	sf::Vector2f windowSize(context.window->getSize());
	
	gameOverText.setFont(font);

	if (player->GetMissionStatus() == Player::MissionStatus::MissionFailure)
	{
		gameOverText.setString("Mission failure!");
	}
	else
	{
		gameOverText.setString("Mission successful!");
	}

	gameOverText.setCharacterSize(70);
	CenteredUnit(gameOverText);
	gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::Draw()
{
	sf::RenderWindow* window = GetContext().window;
	window->setView(window->getDefaultView());
	
	// Create dark back.
	sf::RectangleShape background;
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setSize(window->getView().getSize());

	window->draw(background);
	window->draw(gameOverText);
}

bool GameOverState::Update(sf::Time deltaTime)
{
	// Show the state for 3 seconds.
	elipsedTime += deltaTime;
	if (elipsedTime >= sf::seconds(3.f))
	{
		RequestStackClear();
		RequestStackPush(States::ID::Menu);
	}

	return false;
}

bool GameOverState::HandleEvent(const sf::Event& event)
{
	return false;
}
