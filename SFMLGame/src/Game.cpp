#include "Game.h"

#include <iostream>
#include <SFML/Window/Event.hpp>



Game::Game()
	: window(sf::VideoMode(640, 480), "World", sf::Style::Close)
	, world(window)
	, player()
{
	// TODO: Create the text.
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time lastUpdateTime = sf::Time::Zero; // Last update.

	// A main or a game loop.
	while (window.isOpen())
	{
		ProcessEvent();

		lastUpdateTime += clock.restart(); // Get the delta time.

		// Here we look if our time is more than setted time for
		// each frame, if it is true we need to update the user
		// screen. This way is most common in game developing, 
		// because it give the update method a consatnt value of
		// delta time, that means we haven't any problems with 
		// the problem of huge differece between two values.
		while (lastUpdateTime > TIME_PER_FRAME)
		{
			lastUpdateTime -= TIME_PER_FRAME; // We substract the constant time in each iteration.
			ProcessEvent();

			Update(TIME_PER_FRAME);
		}

		// Fast computers will skip the above loop
		// and call the Render() a lot, but opposite
		// when the computer is slow the Render() will
		// be called fewer times.
		Render();
	}
}

void Game::ProcessEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		player.HandleEvent(event, world.GetCommandQueue());
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
	
	player.HandleRealTimeInput(world.GetCommandQueue());
}

void Game::Update(sf::Time delta)
{	
	world.Update(delta);
}

void Game::Render()
{
	window.clear(sf::Color::Black); // We need to clear window for the first time.
	world.Draw();
	window.display();
}
