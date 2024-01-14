#pragma once

#include "../../Enums/StateID.h"
#include "../State/State.h"
#include <map>
#include <vector>
#include <functional>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>


class StateStack : sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};
	
private:
	struct PendingChange
	{
		PendingChange(Action action, States::ID stateID = States::ID::None);

		Action action;
		States::ID stateId;
	};
	
public:
	StateStack(State::Context context);

public:
	////////////////////////////////////////////////////
	// \brief
	//		Registrs the state into factory.
	// 
	////////////////////////////////////////////////////
	template <typename Type, typename ...Args>
	void RegistrState(States::ID stateId, Args... args);

	////////////////////////////////////////////////////
	// \brief
	//			Update the state state.
	////////////////////////////////////////////////////
	void Update(sf::Time deltaTime);

	////////////////////////////////////////////////////
	// \brief
	//		Draving the state into the screen.
	// 
	////////////////////////////////////////////////////
	void Draw();

	////////////////////////////////////////////////////
	// \brief
	//		Handle the event for the state.
	// 
	////////////////////////////////////////////////////
	void HandleEvent(const sf::Event& event);

	////////////////////////////////////////////////////
	// \brief
	//				Add state to stack.
	// 
	////////////////////////////////////////////////////
	void PushState(States::ID stateId);

	////////////////////////////////////////////////////
	// \brief
	//			Remove the element from stack.
	// 
	////////////////////////////////////////////////////
	void PopState();

	////////////////////////////////////////////////////
	// \brief
	//				Clear the stack.
	////////////////////////////////////////////////////
	void ClearStates();

	////////////////////////////////////////////////////
	// \brief
	//		Checks if the stack is empty.
	// 
	////////////////////////////////////////////////////
	bool IsEmpty() const;

private:
	////////////////////////////////////////////////////
	// \brief 
	//			Creates and retuens the state.
	// 
	////////////////////////////////////////////////////
	State::Ptr CreateState(States::ID stateId);

	////////////////////////////////////////////////////
	// \brief
	//			Applays the pending changes.
	// 
	////////////////////////////////////////////////////
	void ApplyPendingChanges();

private:
	std::vector<State::Ptr>                           stack;
	std::vector<PendingChange>                        pendingList;
	State::Context									  context;
	std::map<States::ID, std::function<State::Ptr()>> factories;
};

template<typename Type, typename ...Args>
inline void StateStack::RegistrState(States::ID stateId, Args... args)
{
	factories[stateId] = [this]() {
		return State::Ptr(new Type(*this, context, args...));
	};
}
