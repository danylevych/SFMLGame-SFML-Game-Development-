#pragma once

#include "../State/State.h"
#include "../../GUI/Container/Container.h"
#include "../../GUI/Button/Button.h"
#include "../../GUI/Label/Label.h"
#include "../../Inputs/Player/Player.h"
#include <SFML/Graphics/Sprite.hpp>

#include <array>


class SettingsState : public State
{
public:
	using Ptr = std::unique_ptr<SettingsState>;

private:
	sf::Sprite background;
	GUI::Container container;
	std::array<GUI::Button::Ptr, static_cast<size_t>(Player::Action::ActionCount)> bindedButtons;
	std::array<GUI::Label::Ptr, static_cast<size_t>(Player::Action::ActionCount)> bindedLabels;

public:
	SettingsState(StateStack& stack, Context context);
	virtual ~SettingsState() override = default;

public: // Override section.
	//////////////////////////////////////////////////////
	// \brief
	//		    Overriding the draw method.
	// 
	//////////////////////////////////////////////////////
	virtual void Draw() override;

	//////////////////////////////////////////////////////
	// \brief
	//	       Overriding the update method.
	// 
	//////////////////////////////////////////////////////
	virtual bool Update(sf::Time deltaTime) override;

	//////////////////////////////////////////////////////
	// \brief
	//  Overriding the handeling events for the state.
	// 
	//////////////////////////////////////////////////////
	virtual bool HandleEvent(const sf::Event& event) override;

private: // Init section. 
	//////////////////////////////////////////////////////
	// \brief
	// Initialize the buttons and labels for the state.
	//////////////////////////////////////////////////////
	void InitButtonsAndLabels();

private: // Helper functions.
	//////////////////////////////////////////////////////
	// \brief
	//     Add the button and label to the container.
	// 
	//////////////////////////////////////////////////////
	void AddButonAndLabel(Player::Action action, float y, const std::string& text);

	//////////////////////////////////////////////////////
	// \brief
	//		 Update the text for the labels.
	// 
	//////////////////////////////////////////////////////
	void UpdateLabels();
};

