#pragma once

#include "../../Enums/Category.h"
#include "../../Scene/SceneNode/SceneNode.h"

#include <cassert>
#include <functional>
#include <SFML/System/Time.hpp>

class SceneNode;

///////////////////////////////////////////////////
// \brief
//		Represents the command for the game.
// 
///////////////////////////////////////////////////
struct Command
{
public:
	std::function<void(SceneNode&, sf::Time)>  action;
	uint32_t								   category;

public:
	Command() : action(), category(Category::None) { }
};

// Return the function for the derived class.
template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> DerivedAction(Function fn)
{
	return [=](SceneNode& node, sf::Time deltaTime) {
		// Check if cast safe.
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node invoke function on it.
		fn(static_cast<GameObject&>(node), deltaTime);
	};
}