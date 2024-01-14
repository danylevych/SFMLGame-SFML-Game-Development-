#pragma once

#include "../../Enums/StateID.h"
//#include "../StateStack/StateStack.h"
#include "../../Holders/Holders.h"
//#include "../../Inputs/Player/Player.h"

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


class StateStack;
class Player;

////////////////////////////////////////////////
// \brief
//		Abstract class represents some
//		states of the game.
// 
////////////////////////////////////////////////
class State
{
public:
	using Ptr = std::unique_ptr<State>;
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		Player* player;
	};

private:
	StateStack* stack;
	Context context;

public:
	State(StateStack& stack, Context context);
	
	virtual ~State() = default;

public: // Virtual Methods
	////////////////////////////////////////////////
	// \brief
	//		Draws the scene state in a window.
	// 
	////////////////////////////////////////////////
	virtual void Draw() = 0; 

	////////////////////////////////////////////////
	// \brief
	//		Updates the state of the scene.
	// 
	////////////////////////////////////////////////
	virtual bool Update(sf::Time) = 0;

	////////////////////////////////////////////////
	// \brief
	//		Handles events that can happened
	//		on the scene state.
	// 
	////////////////////////////////////////////////
	virtual bool HandleEvent(const sf::Event& event) = 0;

protected:
	////////////////////////////////////////////////
	// \brief
	// 
	////////////////////////////////////////////////
	void RequestStackPush(States::ID stateID);

	////////////////////////////////////////////////
	// \brief
	//		
	////////////////////////////////////////////////
	void RequestStackPop();

	////////////////////////////////////////////////
	// \brief
	// 
	////////////////////////////////////////////////
	void RequestStackClear();

	////////////////////////////////////////////////
	// \brief
	//		Returns the context of the state.
	// 
	////////////////////////////////////////////////
	Context GetContext() const;
};

