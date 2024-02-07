#include "Player.h"

#include <map>
#include <string>
#include <algorithm>

#include "../../Entities/Aircraft/Aircraft.h"

using namespace std::placeholders;


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
		aircraft.Accelerate(velocity * aircraft.GetMaxSpeed());
	}
};


Player::Player()
	: status(MissionStatus::MissionRunning)
{
	// Initialize the key and commands.
	InitBindedKeys();
	InitBindedCommands();
}

void Player::InitBindedKeys()
{
	// Set the keys.
	bindedKeys[sf::Keyboard::Up]    = Action::MoveUp;
	bindedKeys[sf::Keyboard::Down]  = Action::MoveDown;
	bindedKeys[sf::Keyboard::Left]  = Action::MoveLeft;
	bindedKeys[sf::Keyboard::Right] = Action::MoveRight;
	bindedKeys[sf::Keyboard::Space] = Action::Fire;
	bindedKeys[sf::Keyboard::M]     = Action::LaunchMissile;
}

void Player::InitBindedCommands()
{
	// Set the commands for each action.
	bindedCommands[Action::MoveLeft].action      = DerivedAction<Aircraft>(AircraftMover(-1,  0.f));
	bindedCommands[Action::MoveRight].action     = DerivedAction<Aircraft>(AircraftMover(+1,  0.f));
	bindedCommands[Action::MoveUp].action        = DerivedAction<Aircraft>(AircraftMover(0.f, -1));
	bindedCommands[Action::MoveDown].action      = DerivedAction<Aircraft>(AircraftMover(0.f, +1));
	bindedCommands[Action::Fire].action          = DerivedAction<Aircraft>(std::bind(&Aircraft::Fire, _1));
	bindedCommands[Action::LaunchMissile].action = DerivedAction<Aircraft>(std::bind(&Aircraft::LaunchMissile, _1));

	// Set the category for each command.
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
	case Player::Action::Fire:
		return true;
	}

	return false;
}

void Player::BindKey(const sf::Keyboard::Key& key, Action action)
{
	for (auto iter = bindedKeys.begin(); iter != bindedKeys.end();)
	{
		if (iter->second == action)
		{
			iter = bindedKeys.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	bindedKeys[key] = action;
}

sf::Keyboard::Key Player::GetBindedKey(Action action) const
{
	return std::find_if(bindedKeys.begin(), bindedKeys.end(), 
		[action](const std::pair<sf::Keyboard::Key, Action>& item) -> bool {
			return item.second == action;
	})->first;
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

void Player::SetMissionStatus(MissionStatus status)
{
	this->status = status;	
}

Player::MissionStatus Player::GetMissionStatus() const
{
	return status;
}
