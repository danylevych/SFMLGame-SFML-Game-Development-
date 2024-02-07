#include "GameState.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

GameState::GameState(StateStack& stack, State::Context context)
	: State(stack, context)
	, world(*context.window, *context.fonts)
	, player(*context.player)
{	
	player.SetMissionStatus(Player::MissionStatus::MissionRunning);
}

void GameState::Draw()
{
	world.Draw();
}

bool GameState::Update(sf::Time deltaTime)
{
	world.Update(deltaTime);

	if (!world.HasAlivePlayer())
	{
		player.SetMissionStatus(Player::MissionStatus::MissionFailure);
		RequestStackPush(States::ID::GameOver);
	}
	else if (world.HasPlayerReachedEnd())
	{
		player.SetMissionStatus(Player::MissionStatus::MissionSuccess);
		RequestStackPush(States::ID::GameOver);
	}

	player.HandleRealTimeInput(world.GetCommandQueue());
	
	return true;
}

bool GameState::HandleEvent(const sf::Event& event)
{
	player.HandleEvent(event, world.GetCommandQueue());

	// If the user want to pause the game.
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		//RequestStackPop();
		RequestStackPush(States::ID::Pause);
	}

	return true;
}
