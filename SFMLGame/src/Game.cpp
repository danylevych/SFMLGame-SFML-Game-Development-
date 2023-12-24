#include "Game.h"

#include <SFML/Window/Event.hpp>


Game::Game()
	: window(sf::VideoMode(640, 480), "First SFML Game")
	, player()
{
	player.setRadius(40.f);
	player.setOrigin(20, 20); // Set the point of the player shape will be moving.
	player.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	player.setFillColor(sf::Color::Cyan);
}

void Game::Run()
{
	// A main or a game loop.
	while (window.isOpen())
	{
		ProcessEvent();
		Update();
		Render();
	}
}

void Game::ProcessEvent()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			HandlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::Update()
{
	sf::Vector2f movement(0.f, 0.f);

	if (isMovingUp)
	{
		movement.y -= 1;
	}

	if (isMovingDown)
	{
		movement.y += 1;
	}

	if (isMovingLeft)
	{
		movement.x -= 1;
	}

	if (isMovingRight)
	{
		movement.x += 1;
	}

	player.move(movement); // Move the player shape to the right position.
}

void Game::Render()
{
	window.clear(sf::Color::Black); // We need to clear window for the first time.
	window.draw(player);
	window.display();
}

void Game::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	switch (key)
	{
	case sf::Keyboard::W:
		isMovingUp = isPressed;
		break;

	case sf::Keyboard::S:
		isMovingDown = isPressed;
		break;

	case sf::Keyboard::A:
		isMovingLeft = isPressed;
		break;

	case sf::Keyboard::D:
		isMovingRight = isPressed;
		break;
	}

}
