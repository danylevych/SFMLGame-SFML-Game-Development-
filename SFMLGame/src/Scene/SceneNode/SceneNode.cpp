#include "SceneNode.h"

#include <algorithm>
#include <cassert>

#include "../../Enums/Category.h"
#include "../../Tools/Utility.h"

#include "../../Inputs/Command/Command.h"
#include "../../Inputs/CommandQueue/CommandQueue.h"


void SceneNode::AttachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::DetachChild(const SceneNode& node)
{
	auto found = std::find_if(children.begin(), children.end(), [&node](Ptr& item) {
		return item.get() == &node;
	});

	assert(found != children.end());

	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	DrawCurrent(target, states);

	for (auto iter = children.begin(), end = children.end(); iter != end; ++iter)
	{
		(*iter)->draw(target, states);
	}
}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{ /* User define a behavior in his class. */ }

sf::FloatRect SceneNode::GetBoundingRect() const
{
	return sf::FloatRect();
}

bool SceneNode::IsMarkedForRemoval() const
{
	return IsDestroyed();
}

bool SceneNode::IsDestroyed() const
{
	return false;
}

void SceneNode::CheckNodeCollision(SceneNode& node, std::set<Pair>& collisioPairs)
{
	// If the node is not this (because we do not want to process a collision between the same node),
	// And if the nodes are colliding with each other,
	// And if the nodes are not destroyed,
	// We can add the node's pair to our collision pairs.
	if (this != &node && Collision(*this, node) && !IsDestroyed() && !node.IsDestroyed())
	{
		collisioPairs.insert(std::minmax(this, &node));
	}

	for (auto& child : children)
	{
		child->CheckNodeCollision(node, collisioPairs);
	}
}

void SceneNode::CheckSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
	CheckNodeCollision(sceneGraph, collisionPairs);

	for (auto& child : sceneGraph.children)
	{
		CheckSceneCollision(*child, collisionPairs);
	}
}

void SceneNode::Update(sf::Time delta, CommandQueue& commands)
{
	UpdateCurrent(delta, commands);
	UpdateChildren(delta, commands);
}

sf::Transform SceneNode::GetWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	
	for (const SceneNode* node = this; node != nullptr; node = node->parent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

sf::Vector2f SceneNode::GetWorlPosition() const
{
	return GetWorldTransform() * sf::Vector2f();
}

uint32_t SceneNode::GetCategory() const
{
	return Category::SceneAirLauer;
}

void SceneNode::OnCommand(const Command& command, sf::Time deltaTime)
{
	if (command.category & GetCategory()) // Our node is in the query.
	{
		command.action(*this, deltaTime);
	}

	for (auto& child : children) // Apply the command for each child.
	{
		child->OnCommand(command, deltaTime);
	}
}

void SceneNode::RemoveWrecks()
{
	// Here we remove all elements from graph, which were markered for removal.
	// We use std::mem_fn instand of std::bind because std::mem_fn create callable
	// instance, other words:
	//     std::mem_fn(&SceneNode::IsMarkedForRemoval) - return the ref to the method,
	//                                                   so you can write somenthing like
	//                                                   memFunc().
	//
	//   std::bind(&SceneNode::IsMarkedForRemoval, _1) - except of the method name need to 
	//                                                   take the instance of the class.
	//
	// So this is a difference between these two methods.
	auto wreckfielBegin = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::IsMarkedForRemoval));
	// std::remove_if - sorts the sequency by placed remove element to the end of the container.
	
	children.erase(wreckfielBegin, children.end());

	std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::RemoveWrecks));
}

void SceneNode::UpdateChildren(sf::Time delta, CommandQueue& commands)
{
	for (auto& child : children)
	{
		child->Update(delta, commands);
	}
}

void SceneNode::UpdateCurrent(sf::Time delta, CommandQueue& commands)
{ /* The user define the realization in derived classes.*/ }


float Distance(const SceneNode& lhs, const SceneNode& rhs)
{
	return VectorLenght(lhs.GetWorlPosition() - rhs.GetWorlPosition());
}

bool Collision(const SceneNode& left, const SceneNode& right)
{
	return left.GetBoundingRect().intersects(right.GetBoundingRect());
}
