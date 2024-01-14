#include "Application.h"

#include "GameStates/States.h"

Application::Application()
	: window(sf::VideoMode(640, 480), "Game", sf::Style::Close)
	, textures()
	, fonts()
	, player()
	, stateStack(State::Context(window, textures, fonts, player))
{
	window.setKeyRepeatEnabled(false);

	InitResources();
	InitStates();

	stateStack.PushState(States::ID::Title);
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time lastUpdateTime = sf::Time::Zero; // Last update.

	// A main or a game loop.
	while (window.isOpen())
	{
		ProcessInput();

		lastUpdateTime += clock.restart(); // Get the delta time.

		// Here we look if our time is more than setted time for
		// each frame, if it is true we need to update the user
		// screen. This way is most common in game developing, 
		// because it give the update method a consatnt value of
		// delta time, that means we haven't any problems with 
		// the problem of huge differece between two values.
		while (lastUpdateTime > TIME_PER_FRAME)
		{
			lastUpdateTime -= TIME_PER_FRAME; // We substract the constant time in each iteration.
			ProcessInput();

			Update(TIME_PER_FRAME);

			// Check inside the loop, because stack might be empty.
			if (stateStack.IsEmpty())
			{
				window.close();
			}
		}

		// Fast computers will skip the above loop
		// and call the Render() a lot, but opposite
		// when the computer is slow the Render() will
		// be called fewer times.
		Render();
	}
}

void Application::InitStates()
{
	stateStack.RegistrState<TitleState>(States::ID::Title);
	stateStack.RegistrState<MenuState>(States::ID::Menu);
	stateStack.RegistrState<LoadingState>(States::ID::Loading);
	stateStack.RegistrState<GameState>(States::ID::Game);
	stateStack.RegistrState<PauseState>(States::ID::Pause);
}

void Application::InitResources()
{
	textures.Load(Textures::TextureID::TitleScreen, "data/Textures/TitleScreen.png");
	fonts.Load(Font::FontID::Main, "data/Fonts/Sansation.ttf");
}


void Application::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		stateStack.HandleEvent(event); // Handeling events for current state.

		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void Application::Update(sf::Time delta)
{
	stateStack.Update(delta);
}

void Application::Render()
{
	window.clear(sf::Color::Black); // We need to clear window for the first time.
	stateStack.Draw();
	window.display();
}