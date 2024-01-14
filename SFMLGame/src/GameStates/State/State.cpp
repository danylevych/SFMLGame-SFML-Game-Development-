#include "State.h"

#include "../StateStack/StateStack.h"


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, player(&player)
{	}

State::State(StateStack& stack, Context context)
	: stack(&stack)
	, context(context)
{	}

void State::RequestStackPush(States::ID stateID)
{
	stack->PushState(stateID);
}

void State::RequestStackPop()
{
	stack->PopState();
}

void State::RequestStackClear()
{
	stack->ClearStates();
}

State::Context State::GetContext() const
{
	return context;
}
