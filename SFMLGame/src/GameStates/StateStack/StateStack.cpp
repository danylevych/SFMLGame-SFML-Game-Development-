#include "StateStack.h"

#include <cassert>


StateStack::StateStack(State::Context context)
    : context(context)
{   }


State::Ptr StateStack::CreateState(States::ID stateId)
{
    auto foundState = factories.find(stateId);
    
    assert(foundState != factories.end());

    return foundState->second();
}

void StateStack::Update(sf::Time deltaTime)
{
    for (auto iter = stack.rbegin(); iter != stack.rend(); ++iter)
    {
        if (!(*iter)->Update(deltaTime))
        {
            break;
        }
    }

    ApplyPendingChanges();
}

void StateStack::Draw()
{
    // Drawing states from buttom to top.
    for (auto& item : stack)
    {
        item->Draw();
    }
}

void StateStack::HandleEvent(const sf::Event& event)
{
    for (auto iter = stack.rbegin(); iter != stack.rend(); ++iter)
    {
        if (!(*iter)->HandleEvent(event))
        {
            break;
        }
    }

    ApplyPendingChanges();
}

void StateStack::PushState(States::ID stateId)
{
    pendingList.push_back(PendingChange(Action::Push, stateId));
}

void StateStack::PopState()
{
    pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates()
{
    pendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::IsEmpty() const
{
    return stack.empty();
}

void StateStack::ApplyPendingChanges()
{
    // The function exist because, operation
    // with stack can hapening for a long time.
    // So, one operation can be applying before
    // other, and sometimes the behavior is not
    // allowed, because it bring with itself
    // undefined behavior.

    for (auto& change : pendingList)
    {
        switch (change.action)
        {
        case Action::Push:
            stack.push_back(CreateState(change.stateId));
            break;

        case Action::Pop:
            stack.pop_back();
            break;

        case Action::Clear:
            stack.clear();
            break;
        }
    }
    
    pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateId(stateID)
{   }
