#include "SceneNode.h"

#include <algorithm>
#include <cassert>

#include "../../Enums/Category.h"


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

void SceneNode::Update(sf::Time delta)
{
	UpdateCurrent(delta);
	UpdateChildren(delta);
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
	return Category::Scene;
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

void SceneNode::UpdateChildren(sf::Time delta)
{
	for (auto& child : children)
	{
		child->Update(delta);
	}
}

void SceneNode::UpdateCurrent(sf::Time delta)
{ /* The user define the realization in derived classes.*/ }
