#pragma once


#include "../../Inputs/Command/Command.h"

#include <memory>
#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

struct Command;

///////////////////////////////////////////////////
// \brief
//		The class represents the heirarchy
//		on the game scene.
// 
///////////////////////////////////////////////////
class SceneNode : public sf::Transformable
				, public sf::Drawable
				, private sf::NonCopyable  // We can't copy the instance.
{
public:
	using Ptr = std::unique_ptr<SceneNode>;

private:
	SceneNode* parent;
	std::vector<Ptr> children;

public:
	SceneNode() = default;
	virtual ~SceneNode() = default;

public:
	/////////////////////////////////////////////////////
	// \brief
	//			Add the child to the list.
	// 
	/////////////////////////////////////////////////////
	void AttachChild(Ptr child);

	/////////////////////////////////////////////////////
	// \brief
	//			Remove the child from sequence.
	// 
	/////////////////////////////////////////////////////
	Ptr DetachChild(const SceneNode& node);

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Overriden method from sf::Drawable, 
	//		for drawing our items in the game
	//		window.
	// 
	/////////////////////////////////////////////////////	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	/////////////////////////////////////////////////////
	// \brief
	//		The mthod provide to us an ability
	//		to draw only curent instance on the
	//		game screen, instand of drawing all
	//		children of the instance.
	// 
	/////////////////////////////////////////////////////
	virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	/////////////////////////////////////////////////////
	// \brief
	//		Update the scine node in the window.
	// 
	/////////////////////////////////////////////////////
	void Update(sf::Time delta);

	/////////////////////////////////////////////////////
	// \brief
	//		Returns the object transform in the
	//		world map.
	// 
	/////////////////////////////////////////////////////
	sf::Transform GetWorldTransform() const;

	/////////////////////////////////////////////////////
	// \brief
	//		Returns the position of object in
	//		the world coordinate system.
	// 
	/////////////////////////////////////////////////////
	sf::Vector2f GetWorlPosition() const;

	/////////////////////////////////////////////////////
	// \brief
	//		Return the category for the instance
	//		of the SceneNode.
	// 
	/////////////////////////////////////////////////////
	virtual uint32_t GetCategory() const;

	/////////////////////////////////////////////////////
	// \brief
	//		Execute the command for the scene node.
	// 
	/////////////////////////////////////////////////////
	void OnCommand(const Command& command, sf::Time deltaTime);

private:
	/////////////////////////////////////////////////////
	// \brief
	//		Updtate the children for current node.
	// 
	/////////////////////////////////////////////////////
	void UpdateChildren(sf::Time delta);

	/////////////////////////////////////////////////////
	// \brief
	//				Update the curent node.
	// 
	/////////////////////////////////////////////////////
	virtual void UpdateCurrent(sf::Time delta);
};

