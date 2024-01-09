#include "World.h"


#include "../SpriteNode/SpriteNode.h"


World::World(sf::RenderWindow& window)
	: window(window)
	, view(window.getDefaultView())
	, textures()
	, sceneGraph()
	, sceneLayers()
	, worldBounds(0.f, 0.f, view.getSize().x, 2000.f)
	, spawnPos(window.getSize().x / 2.f, worldBounds.height - view.getSize().y / 2.f)
	, scrollSpeed(-50.f)
	, playerAircraft(nullptr)
{
	LoadTextures();
	BuildScene();
	
	// Prepare the view.
	view.setCenter(spawnPos);
}

void World::Update(sf::Time delta)
{
	view.move(0.f, scrollSpeed * delta.asSeconds());
	playerAircraft->SetVelocity(0.f, 0.f);

	// Forward commands to the scene graph.
	while (!commandQueue.IsEmpty())
	{
		sceneGraph.OnCommand(commandQueue.Pop(), delta);
	}

	AdaptPlayerVelocity();
	

	sceneGraph.Update(delta);
	AdaptPlayerPosition();
}

void World::Draw()
{
	window.setView(view);
	window.draw(sceneGraph);
}

CommandQueue& World::GetCommandQueue()
{
	return commandQueue;
}

void World::LoadTextures()
{
	textures.Load(Textures::TextureID::Eagle,  "data/Textures/Eagle.png");
	textures.Load(Textures::TextureID::Raptor, "data/Textures/Raptor.png");
	textures.Load(Textures::TextureID::Desert, "data/Textures/Desert.png");
}

void World::BuildScene()
{
	// Fill the sceneLayers and scene tree.
	for (auto& item : sceneLayers)
	{
		SceneNode::Ptr layer(new SceneNode());
		item = layer.get();
		sceneGraph.AttachChild(std::move(layer));
	}

	// Fill the world by our desert texture.
	sf::Texture& textureDesert = textures.Get(Textures::TextureID::Desert);
	sf::IntRect textureRect(worldBounds);
	textureDesert.setRepeated(true);

	// Creating a background scene.
	SpriteNode::Ptr backgroundSprite(new SpriteNode(textureDesert, textureRect));
	backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
	sceneLayers[Background]->AttachChild(std::move(backgroundSprite));

	// Creating user airplane.
	std::unique_ptr<Aircraft> aircraftPtr(new Aircraft(Aircraft::Type::Ealge, textures));
	playerAircraft = aircraftPtr.get();  // Tie the instance to aircraft.
	aircraftPtr->setPosition(spawnPos);
	aircraftPtr->SetVelocity(40.f, scrollSpeed);
	sceneLayers[Air]->AttachChild(std::move(aircraftPtr));

	// Creating an escort to player.
	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, textures));
	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, textures));

	leftEscort->setPosition(-80.f, 50);
	rightEscort->setPosition(+80.f, 50);

	playerAircraft->AttachChild(std::move(leftEscort));
	playerAircraft->AttachChild(std::move(rightEscort));
}

void World::AdaptPlayerVelocity()
{
	sf::Vector2f velocity = playerAircraft->GetVelocity();

	if (velocity.x != 0.f && velocity.y != 0.f) // Player is moving on a diagonal.
	{
		// Normalizing the diagonaly velocity of the player.
		playerAircraft->SetVelocity(velocity / std::sqrt(2.f));
	}

	// Add scroling velocity.
	playerAircraft->Accelerate(0.f, scrollSpeed);
}

void World::AdaptPlayerPosition()
{
	// Define the rectangle where our player can be.
	sf::FloatRect viewBounds(view.getCenter() - view.getSize() / 2.f, view.getSize());
	const float DISTANCE_TO_BORDER = 45.f;
	
	// Don't allow player left the screen.
	sf::Vector2f playerPos = playerAircraft->getPosition();
	
	// Set the right point.
	playerPos.x = std::min<float>(playerPos.x, viewBounds.left + viewBounds.width - DISTANCE_TO_BORDER);
	
	// Set the left point.
	playerPos.x = std::max<float>(playerPos.x, viewBounds.left + DISTANCE_TO_BORDER);

	// Set the top point.
	playerPos.y = std::max<float>(playerPos.y, viewBounds.top + DISTANCE_TO_BORDER);

	// Set the bottom point.
	playerPos.y = std::min<float>(playerPos.y, viewBounds.top + viewBounds.height - DISTANCE_TO_BORDER);

	playerAircraft->setPosition(playerPos);
}
