#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>


#include "Holders/Holders.h"


class Game
{
private:
	sf::RenderWindow window;
	sf::Sprite player;

	// User moving.
	bool isMovingUp    = false;
	bool isMovingDown  = false;
	bool isMovingLeft  = false;
	bool isMovingRight = false;

	// Define how much time one frame will occure.
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	// Player's speed.
	const float playerSpeed = 100.f;

	// Holders.
	TextureHolder textures;

public:
	Game();

public:
	////////////////////////////////////////////////////////////////////
	// 
	//		This method starts a game, it is better to say
	//		run a game loop.
	// 
	////////////////////////////////////////////////////////////////////
	void Run();

private:
	////////////////////////////////////////////////////////////////////
	// 
	//			This method handels the user input.
	// 
	////////////////////////////////////////////////////////////////////
	void ProcessEvent();

	////////////////////////////////////////////////////////////////////
	// 
	//		This one updates the state for the player shape or 
	//		another shapes that will be shown on the screen.
	//		delta is the parameter that defines the time of each
	//		frame in our computer.
	// 
	////////////////////////////////////////////////////////////////////
	void Update(sf::Time delta);

	////////////////////////////////////////////////////////////////////
	// 
	//		This method displaes all objects in user screen. 
	// 
	////////////////////////////////////////////////////////////////////
	void Render();

	////////////////////////////////////////////////////////////////////
	// 
	//		This method handles the user input such as: moving
	//		or shooting ect.
	// 
	////////////////////////////////////////////////////////////////////
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

