#pragma once

#include "../State/State.h"

#include <vector>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>


//////////////////////////////////////////////
// \brief
//	 Represents the menu state of the app.
// 
//////////////////////////////////////////////
class MenuState : public State
{
private:
	enum class Options
	{
		Play,
		Exit
	};

private:
	int32_t currentChoose;
	std::vector<sf::Text> options;
	sf::Sprite background;

public:
	//////////////////////////////////////////////
	// \brief
	//	 Create an instance of the app state.
	// 
	//////////////////////////////////////////////
	MenuState(StateStack& stack, Context context);

public: // Overriden section
	////////////////////////////////////////////////////////////////////
	// \brief
	//			Overriding drawing for the state of app.
	// 
	////////////////////////////////////////////////////////////////////
	virtual void Draw() override;

	////////////////////////////////////////////////////////////////////
	// \brief
	// 			Overriding updating for the state of app.
	// 
	////////////////////////////////////////////////////////////////////
	virtual bool Update(sf::Time deltaTime) override;


	////////////////////////////////////////////////////////////////////
	// \brief
	// 			Overriding handeling for the state of app.
	// 
	////////////////////////////////////////////////////////////////////
	virtual bool HandleEvent(const sf::Event& event) override;

private: // Init section.
	////////////////////////////////////////////////////////////////////
	// \brief
	//		    Initialize the option for the application.
	// 
	////////////////////////////////////////////////////////////////////
	void InitOptions();

	////////////////////////////////////////////////////////////////////
	// \brief
	//		    Initialize the background for the state.
	// 
	////////////////////////////////////////////////////////////////////
	void InitBackground();
};

