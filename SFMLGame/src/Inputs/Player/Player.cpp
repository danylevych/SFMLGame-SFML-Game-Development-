#include "Player.h"

#include <iostream>

#include "../../Entities/Aircraft/Aircraft.h"


///////////////////////////////////////////////////
// \brief
//		Functor represents the movement of
//		the aircraft.
// 
///////////////////////////////////////////////////
struct AircraftMover
{
public:
	sf::Vector2f velocity;

public:
	AircraftMover(float xVelocity, float yVelocity)
		: velocity(xVelocity, yVelocity)
	{	}

	void operator()(Aircraft& aircraft, sf::Time delataTime) const
	{
		aircraft.Accelerate(velocity);
	}
};

Player::Player()
{
	InitBindedKeys();
	InitBindedCommands();
}

void Player::InitBindedKeys()
{
	bindedKeys[sf::Keyboard::Up] = Action::MoveUp;
	bindedKeys[sf::Keyboard::Down] = Action::MoveDown;
	bindedKeys[sf::Keyboard::Left] = Action::MoveLeft;
	bindedKeys[sf::Keyboard::Right] = Action::MoveRight;
}

void Player::InitBindedCommands()
{
	const float PLAYER_SPEED = 40.f;

	bindedCommands[Action::MoveLeft].action  = DerivedAction<Aircraft>(AircraftMover(-PLAYER_SPEED, 0.f));
	bindedCommands[Action::MoveRight].action = DerivedAction<Aircraft>(AircraftMover(+PLAYER_SPEED, 0.f));
	bindedCommands[Action::MoveUp].action    = DerivedAction<Aircraft>(AircraftMover(0.f, -PLAYER_SPEED));
	bindedCommands[Action::MoveDown].action  = DerivedAction<Aircraft>(AircraftMover(0.f, +PLAYER_SPEED));
	
	for (auto& item : bindedCommands)
	{
		item.second.category = Category::PlayerAircraft;
	}
}

bool Player::IsRealtimeAction(Action action) const
{
	switch (action)
	{
	case Player::Action::MoveLeft:
	case Player::Action::MoveRight:
	case Player::Action::MoveUp:
	case Player::Action::MoveDown:
		return true;
	}
	return false;
}

void Player::BindKey(const sf::Keyboard::Key& key, Action action)
{
	bindedKeys[key] = action;
}

sf::Keyboard::Key Player::GetBindedKey(Action action) const
{
	return std::find_if(bindedKeys.begin(), bindedKeys.end(), 
		[action](const std::pair<sf::Keyboard::Key, Action>& item) -> bool {
			return item.second == action;
	})->first;

	for (const auto& keyValPair : bindedKeys)
	{
		if (keyValPair.second == action)
		{
			return keyValPair.first;
		}
	}
}

void Player::HandleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = bindedKeys.find(event.key.code);
		if (found != bindedKeys.end() && !IsRealtimeAction(found->second))
		{
			commands.Push(bindedCommands[found->second]);
		}
	}
}

void Player::HandleRealTimeInput(CommandQueue& commands)
{
	for (auto& item : bindedKeys)
	{
		if (sf::Keyboard::isKeyPressed(item.first) && IsRealtimeAction(item.second))
		{
			commands.Push(bindedCommands[item.second]);
		}
	}
}
