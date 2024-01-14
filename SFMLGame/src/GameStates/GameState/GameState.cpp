#include "GameState.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

GameState::GameState(StateStack& stack, State::Context context)
	: State(stack, context)
	, world(*context.window)
	, player(*context.player)
{	}

void GameState::Draw()
{
	world.Draw();
}

bool GameState::Update(sf::Time deltaTime)
{
	world.Update(deltaTime);
	player.HandleRealTimeInput(world.GetCommandQueue());
	
	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	player.HandleEvent(event, world.GetCommandQueue());

	// If the user want to pause the game.
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		RequestStackPush(States::ID::Pause);
	}

	return true;
}
