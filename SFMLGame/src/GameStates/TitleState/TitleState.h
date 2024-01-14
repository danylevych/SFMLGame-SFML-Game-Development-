#pragma once

#include "../State/State.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

//////////////////////////////////////////////////////
// \brief
//		Represents the title screen of our app.
// 
//////////////////////////////////////////////////////
class TitleState : public State
{
private:
	sf::Sprite background;
	sf::Text   label;
	
	bool isTextShown;
	const sf::Time LABEL_ANIME_TIME = sf::seconds(0.5f);

public:
	//////////////////////////////////////////////////////
	// \brief
	//		Creating the title screen of the app.
	// 
	//////////////////////////////////////////////////////
	TitleState(StateStack& stack, Context context);

public: // Overriding methods.
	//////////////////////////////////////////////////////
	// \brief
	//		Overriding drawing for the state of app.
	// 
	//////////////////////////////////////////////////////
	virtual void Draw() override;

	//////////////////////////////////////////////////////
	// \brief
	//		Overriding updating for the state of app.
	// 
	//////////////////////////////////////////////////////
	virtual bool Update(sf::Time deltaTime) override;

	//////////////////////////////////////////////////////
	// \brief
	//		Overriding handeling for the state of app.
	// 
	//////////////////////////////////////////////////////
	virtual bool HandleEvent(const sf::Event& event) override;
};

