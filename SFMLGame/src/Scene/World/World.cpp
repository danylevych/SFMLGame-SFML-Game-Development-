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

	sf::Vector2f position = playerAircraft->getPosition();
	sf::Vector2f velocity = playerAircraft->GetVelocity();

	if (position.x <= worldBounds.left + 150 ||
		position.x >= worldBounds.left + worldBounds.width - 150)
	{
		velocity.x = -velocity.x;
		playerAircraft->SetVelocity(velocity);
	}

	sceneGraph.Update(delta);
}

void World::Draw()
{
	window.setView(view);
	window.draw(sceneGraph);
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
