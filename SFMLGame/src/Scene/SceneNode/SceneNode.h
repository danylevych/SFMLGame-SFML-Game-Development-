#pragma once

#include <memory>
#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <set>

struct Command;
class CommandQueue;

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
	using Pair = std::pair<SceneNode*, SceneNode*>;

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

public:
	/////////////////////////////////////////////////////
	// \brief
	//		 Return the bounds for the node.
	// 
	/////////////////////////////////////////////////////
	virtual sf::FloatRect GetBoundingRect() const;

	/////////////////////////////////////////////////////
	// \brief
	//	   Check if the node is marked for removal.
	// 
	/////////////////////////////////////////////////////
	virtual bool IsMarkedForRemoval() const;

	/////////////////////////////////////////////////////
	// \brief
	//		   Check if the node is dstoyed.
	// 
	/////////////////////////////////////////////////////
	virtual bool IsDestroyed() const;

	/////////////////////////////////////////////////////
	// \brief
	//      Check collision between SceneNodes.
	// 
	/////////////////////////////////////////////////////
	void CheckNodeCollision(SceneNode& node, std::set<Pair>& collisioPairs);

	/////////////////////////////////////////////////////
	// \brief
	//		Check collision for the graph.
	// 
	/////////////////////////////////////////////////////
	void CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);

public:
	/////////////////////////////////////////////////////
	// \brief
	//		Update the scine node in the window.
	// 
	/////////////////////////////////////////////////////
	void Update(sf::Time delta, CommandQueue& commands);

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

	/////////////////////////////////////////////////////
	// \brief
	//   Remove objects were marcered for destroying.
	// 
	/////////////////////////////////////////////////////
	void RemoveWrecks();

private:
	/////////////////////////////////////////////////////
	// \brief
	//		Update the children for current node.
	// 
	/////////////////////////////////////////////////////
	void UpdateChildren(sf::Time delta, CommandQueue& commands);

	/////////////////////////////////////////////////////
	// \brief
	//				Update the curent node.
	// 
	/////////////////////////////////////////////////////
	virtual void UpdateCurrent(sf::Time delta, CommandQueue& commands);
};

float Distance(const SceneNode& lhs, const SceneNode& rhs);

bool Collision(const SceneNode& left, const SceneNode& right);