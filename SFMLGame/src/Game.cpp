#include "Game.h"

#include <SFML/Window/Event.hpp>


Game::Game()
	: window(sf::VideoMode(640, 480), "First SFML Game")
	, player()
	, textures()
{
	textures.Load(Textures::TextureID::Airplane, "data/img/Eagle.png");

	player.setTexture(textures.Get(Textures::TextureID::Airplane));
	//player.setScale(4.f, 4.f);
	// Set the point of the player shape will be moving.
	//player.setOrigin(texture.getSize().x * 0.5f / 2.f, texture.getSize().y * 0.5f / 2.f); 
	player.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
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

void Game::Update(sf::Time delta)
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

	// With multiplaying movement vector by delta we firstly
	// make user's moving more smoothest and finaly, we remove
	// dependence for frame. 
	player.move(movement * playerSpeed * delta.asSeconds()); // Move the player shape to the right position.
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
