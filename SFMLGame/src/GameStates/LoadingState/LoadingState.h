#pragma once

#include "../State/State.h"
#include "../../Tools/ParalelTask/ParalelTask.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class LoadingState : public State
{
private:
	sf::Text loadingText;
	sf::RectangleShape progressBarBackground;
	sf::RectangleShape progressBar;

	ParalelTask loadingTask;

public:
	LoadingState(StateStack& stack, Context context);

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

public:
	////////////////////////////////////////////////////////////////////
	// \brief
	//			Set the percent of complation of the task.
	// 
	////////////////////////////////////////////////////////////////////
	void SetComplation(float percent);

public: // Init section.
	////////////////////////////////////////////////////////////////////
	// \brief
	//		Initialize the progress bar for the loading state.
	// 
	////////////////////////////////////////////////////////////////////
	void InitProgressBar();

	////////////////////////////////////////////////////////////////////
	// \brief
	//			Initialize the label for the loading state.
	// 
	////////////////////////////////////////////////////////////////////
	void InitLoadingText();
};

