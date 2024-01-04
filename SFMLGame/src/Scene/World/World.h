#pragma once

#include "../SceneNode/SceneNode.h"
#include "../../Holders/Holders.h"
#include "../../Entities/Aircraft/Aircraft.h"

#include<SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/NonCopyable.hpp>


#include <array>

//////////////////////////////////////////////
// \brief
//		The class represents the world
//		hierarchy in the game.
// 
//////////////////////////////////////////////
class World : private sf::NonCopyable
{
public:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};

private:
	// ========== World props ===========
	sf::RenderWindow& window;
	sf::View		  view;
	TextureHolder	  textures;
	SceneNode		  sceneGraph;

	std::array<SceneNode*, Layer::LayerCount> sceneLayers;

	sf::FloatRect	  worldBounds;

	// =========== User props ==========
	sf::Vector2f	  spawnPos;
	float_t			  scrollSpeed;
	Aircraft*		  playerAircraft;

public:
	/////////////////////////////////////////////////
	// \brief
	//		Constructor that takes a window
	//		of the game.
	// 
	/////////////////////////////////////////////////
	World(sf::RenderWindow& window);

public:
	/////////////////////////////////////////////////
	// \brief
	//		Updates the state of the world.
	// 
	/////////////////////////////////////////////////
	void Update(sf::Time delta);

	/////////////////////////////////////////////////
	// \brief
	//	     Draw the world on the window.
	// 
	/////////////////////////////////////////////////
	void Draw();

private:
	/////////////////////////////////////////////////
	// \brief
	//		Load the textures to TexturesHolder.
	// 
	/////////////////////////////////////////////////
	void LoadTextures();

	/////////////////////////////////////////////////
	// \brief
	//				Builds the scene.
	// 
	/////////////////////////////////////////////////
	void BuildScene();
};

