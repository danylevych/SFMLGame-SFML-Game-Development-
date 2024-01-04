#pragma once


#include "Scene/World/World.h"


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>


///////////////////////////////////////////////
// \brief
//		The class represents the game obj.
// 
///////////////////////////////////////////////
class Game
{
private:
	sf::RenderWindow window;
	World			 world;

	// User moving.
	bool isMovingUp    = false;
	bool isMovingDown  = false;
	bool isMovingLeft  = false;
	bool isMovingRight = false;

	// Define how much time one frame will occure.
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

	// Player's speed.
	const float playerSpeed = 100.f;

public:
	Game();

public:
	////////////////////////////////////////////////////////////////////
	// \brief
	//		This method starts a game, it is better to say
	//		run a game loop.
	// 
	////////////////////////////////////////////////////////////////////
	void Run();

private:
	////////////////////////////////////////////////////////////////////
	// \brief
	//			This method handels the user input.
	// 
	////////////////////////////////////////////////////////////////////
	void ProcessEvent();

	////////////////////////////////////////////////////////////////////
	// \brief
	//		This one updates the state for the player shape or 
	//		another shapes that will be shown on the screen.
	//		delta is the parameter that defines the time of each
	//		frame in our computer.
	// 
	////////////////////////////////////////////////////////////////////
	void Update(sf::Time delta);

	////////////////////////////////////////////////////////////////////
	// \brief
	//		This method displaes all objects in user screen. 
	// 
	////////////////////////////////////////////////////////////////////
	void Render();

	////////////////////////////////////////////////////////////////////
	// \brief
	//		This method handles the user input such as: moving
	//		or shooting ect.
	// 
	////////////////////////////////////////////////////////////////////
	void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

