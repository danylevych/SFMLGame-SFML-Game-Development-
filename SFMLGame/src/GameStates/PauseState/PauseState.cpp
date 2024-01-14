#include "PauseState.h"

#include <SFML/Graphics/RectangleShape.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, currentChoose(0)
	, options()
{
	InitTitle();
	InitOptions();
	Update(sf::Time::Zero); // For set the active button.
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
	CenterOrigin(title);
	title.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 40);
}

void PauseState::InitOptions()
{
	sf::Font& font = GetContext().fonts->Get(Font::FontID::Main);
	sf::Vector2f windowSize = GetContext().window->getDefaultView().getSize();

	// Build the "resume" button.
	sf::Text resume;
	resume.setFont(font);
	resume.setFillColor(sf::Color::White);
	resume.setString("Resume");
	CenterOrigin(resume);
	resume.setPosition(windowSize / 2.f);

	// Build the "to menu" button.
	sf::Text toMenu;
	toMenu.setFont(font);
	toMenu.setFillColor(sf::Color::White);
	toMenu.setString("To Menu");
	CenterOrigin(toMenu);
	toMenu.setPosition(resume.getPosition().x, resume.getPosition().y + 40);

	options.push_back(resume);
	options.push_back(toMenu);
}

void PauseState::CenterOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.f,
				   bounds.top + bounds.height / 2.f);
}

void PauseState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	sf::RectangleShape background;
	background.setSize(window->getDefaultView().getSize());
	background.setFillColor(sf::Color(0, 0, 0, 150));

	window->draw(background);
	window->draw(title);
	
	for (auto& item : options)
	{
		window->draw(item);
	}
}

bool PauseState::Update(sf::Time deltaTime)
{
	for (auto& item : options)
	{
		item.setFillColor(sf::Color::White);
	}
	options[currentChoose].setFillColor(sf::Color::Red);

	return false;
}

bool PauseState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			currentChoose++;
			currentChoose = currentChoose % options.size();
			return false;

		case sf::Keyboard::Down:
			currentChoose--;
			currentChoose = currentChoose % options.size();
			return false;
		}

		if (event.key.code == sf::Keyboard::Enter)
		{
			Options selectedOption = static_cast<Options>(currentChoose);

			switch (selectedOption)
			{
			case PauseState::Options::Resume:
				RequestStackPop();
				break;

			case PauseState::Options::ToMain:
				RequestStackClear();
				RequestStackPush(States::ID::Menu);
				break;
			}

			return false;
		}

		if (event.key.code == sf::Keyboard::Escape)
		{
			RequestStackPop();
		}
	}

	return false;
}
