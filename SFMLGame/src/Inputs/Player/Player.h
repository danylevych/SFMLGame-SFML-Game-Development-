#pragma once


#include "../CommandQueue/CommandQueue.h"

#include <map>
#include <SFML/Window/Event.hpp>


/////////////////////////////////////////////
// \brief
//		Class represents the palyer 
//		input system.
// 
/////////////////////////////////////////////
class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		ActionCount
	};

private:
	std::map<Action, Command> bindedCommands;
	std::map<sf::Keyboard::Key, Action> bindedKeys;

public:
	Player();

public:
	/////////////////////////////////////////////
	// \brief
	//		 Bind the Key to Action.
	/////////////////////////////////////////////
	void BindKey(const sf::Keyboard::Key& key, Action action);

	/////////////////////////////////////////////
	// \brief
	//		Returns the binded Key for
	//		the action.
	// 
	/////////////////////////////////////////////
	sf::Keyboard::Key GetBindedKey(Action action) const;

	/////////////////////////////////////////////
	// \brief
	//		Handles the event, that in the 
	//		queue of the window events.
	// 
	/////////////////////////////////////////////
	void HandleEvent(const sf::Event& event, CommandQueue& commands);

	/////////////////////////////////////////////
	// \brief
	//		Handles the event that isn't
	//		depend on the queue of events.
	// 
	/////////////////////////////////////////////
	void HandleRealTimeInput(CommandQueue& commands);

private:
	/////////////////////////////////////////////
	// \brief
	//	     Initialize the bindedKeys.
	// 
	/////////////////////////////////////////////
	void InitBindedKeys();

	/////////////////////////////////////////////
	// \brief
	//		Initialize the bindedCommands.
	// 
	/////////////////////////////////////////////
	void InitBindedCommands();

	/////////////////////////////////////////////
	// \brief
	//		Check if the action is realtime.
	// 
	/////////////////////////////////////////////
	bool IsRealtimeAction(Action action) const;
};
