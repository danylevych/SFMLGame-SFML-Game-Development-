#include "PauseState.h"

#include "../../GUI/Button/Button.h"
#include <SFML/Graphics/RectangleShape.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{
	InitTitle();
	InitOptions();
	//Update(sf::Time::Zero); // For set the active button.
}

void PauseState::InitTitle()
{
	sf::Font& font = GetContext().fonts->Get(Font::FontID::Main);
	sf::Vector2f windowSize = GetContext().window->getDefaultView().getSize();

	// Init configs for the title label.
	title.setFont(font);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(45);
	title.setString("PAUSE MENU");
	title.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 40);
}

void PauseState::InitOptions()
{
	FontHolder& fonts = *GetContext().fonts;
	TextureHolder& textures = *GetContext().textures;
	sf::Vector2f windowSize = GetContext().window->getDefaultView().getSize();

	// Build the "resume" button.
	auto resumeButton = std::make_shared<GUI::Button>(textures, fonts);
	resumeButton->SetText("Resume");
	resumeButton->SetCallBack([this]() {
		RequestStackPop();
	});
	resumeButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);

	// Build the "to menu" button.
	auto toMenuButton = std::make_shared<GUI::Button>(textures, fonts);
	toMenuButton->SetText("To Menu");
	toMenuButton->SetCallBack([this]() {
		RequestStackClear();
		RequestStackPush(States::ID::Menu);
	});

	toMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);

	options.Pack(resumeButton);
	options.Pack(toMenuButton);
}

void PauseState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	sf::RectangleShape background;
	background.setFillColor(sf::Color(0, 0, 0, 150));
	background.setSize(window->getDefaultView().getSize());

	window->draw(background);
	window->draw(title);
	window->draw(options);
}

bool PauseState::Update(sf::Time deltaTime)
{
	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	/*if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			RequestStackPop();
		}
	}*/
	options.HandleEvent(event);
	return false;
}
