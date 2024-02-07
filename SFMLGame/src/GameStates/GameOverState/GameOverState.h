#pragma once
#include "../State/State.h"

#include <SFML/Graphics/Text.hpp>

class GameOverState : public State
{
private:
	sf::Text gameOverText;
	sf::Time elipsedTime;

public:
	GameOverState(StateStack& stack, Context context);
	
	virtual ~GameOverState() override = default;

public:
	virtual void Draw() override;
	virtual bool Update(sf::Time deltaTime) override;
	virtual bool HandleEvent(const sf::Event& event) override;
};

