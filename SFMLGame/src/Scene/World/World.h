#pragma once

#include "../SceneNode/SceneNode.h"
#include "../../Holders/Holders.h"
#include "../../Entities/Aircraft/Aircraft.h"
#include "../../Inputs/CommandQueue/CommandQueue.h"

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

	//////////////////////////////////////////////////////////
	// \brief
	//		  Spawn point for the entity aricrafts.
	// 
	//////////////////////////////////////////////////////////
	struct SpawnPoint
	{
		SpawnPoint(Aircraft::Type type, float x, float y)
			: type(type)
			, x(x), y(y)
		{	}

		Aircraft::Type type;
		float x;
		float y;
	};

private:
	// ========== World props ===========
	sf::RenderWindow& window;
	sf::View		  view;
	TextureHolder	  textures;
	FontHolder&		  fonts;
	SceneNode		  sceneGraph;
	sf::FloatRect	  worldBounds;

	std::array<SceneNode*, Layer::LayerCount> sceneLayers;

	// ===========   Input    ==========
	CommandQueue	  commandQueue;

	// =========== User props ==========
	sf::Vector2f	  spawnPos;
	float_t			  scrollSpeed;
	Aircraft*		  playerAircraft;

	// =========== Enemies ===========
	std::vector<SpawnPoint> enemySpawnPoints;
	std::vector<Aircraft*> activeEnemies;

public:
	/////////////////////////////////////////////////
	// \brief
	//		Constructor that takes a window
	//		of the game.
	// 
	/////////////////////////////////////////////////
	World(sf::RenderWindow& window, FontHolder& fonts);

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

	/////////////////////////////////////////////////
	// \brief
	//		Returns the queue of the commands.
	// 
	/////////////////////////////////////////////////
	CommandQueue& GetCommandQueue();
	
    /////////////////////////////////////////////////
	// \brief
	//   Return true if player is still alive.
	// 
	/////////////////////////////////////////////////
	bool HasAlivePlayer() const;

	/////////////////////////////////////////////////
	// \brief
	//   Return true if player reach the end of 
	//   mission.
	// 
	/////////////////////////////////////////////////
	bool HasPlayerReachedEnd() const;

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

	/////////////////////////////////////////////////
	// \breif
	//		   Adapts the player velocity.
	// 
	/////////////////////////////////////////////////
	void AdaptPlayerVelocity();

	/////////////////////////////////////////////////
	// \brief
	//		Adapts the player position on
	//		the visiable part of the game.
	// 
	/////////////////////////////////////////////////
	void AdaptPlayerPosition();

	/////////////////////////////////////////////////
	// \brief
	//	  Guide the Missile to the most neerest 
	//    enemy.
	// 
	/////////////////////////////////////////////////
	void GuideMissiles();

private:
	/////////////////////////////////////////////////
	// \brief
	//    Handle the collision between entities
	//    in the game screen.
	// 
	/////////////////////////////////////////////////
	void HandleCollision();

private:
	/////////////////////////////////////////////////
	// \brief
	//    This is a section for helper functions.
	// 
	/////////////////////////////////////////////////

	void AddEnemies();
	void AddEnemy(Aircraft::Type type, float x, float y);
	void SpawnEnemies();
	void DestroyEntitiesOutsideView();

	sf::FloatRect GetViewBounds() const;
	sf::FloatRect GetBattlefieldBounds() const;
};


//////////////////////////////////////////////////////
// \brief
//	   Check categories of the collision pair.
// 
//////////////////////////////////////////////////////
bool MatchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);