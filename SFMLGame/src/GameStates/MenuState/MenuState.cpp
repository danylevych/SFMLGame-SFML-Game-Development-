#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, currentChoose(0)
	, options()
{	
	InitBackground();
	InitOptions();
	Update(sf::Time::Zero); // For set the right menu option.
}

void MenuState::InitOptions()
{
	// Function centrate the origin of the text.
	auto centerOrigin = [](sf::Text& text) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.f,
					   bounds.top + bounds.height / 2.f);
	};

	Context context = GetContext();

	// Build the "play" option.
	sf::Text play;
	play.setFont(context.fonts->Get(Font::FontID::Main));
	play.setString("Play");
	centerOrigin(play);
	play.setPosition(context.window->getDefaultView().getSize() / 2.f);
	play.setFillColor(sf::Color::White);
	
	// Build the "exit" option.
	sf::Text exit;
	exit.setFont(context.fonts->Get(Font::FontID::Main));
	exit.setString("Exit");
	centerOrigin(exit);
	exit.setPosition(play.getPosition() + sf::Vector2f(0.f, 30.f));
	exit.setFillColor(sf::Color::White);

	options.push_back(play);
	options.push_back(exit);
}

void MenuState::InitBackground()
{
	background.setTexture(GetContext().textures->Get(Textures::TextureID::TitleScreen));
}

void MenuState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	window->draw(background);

	for (auto& item : options)
	{
		window->draw(item);
	}
}

bool MenuState::Update(sf::Time deltaTime)
{
	for (auto& item : options)
	{
		item.setFillColor(sf::Color::White);
	}

	options[currentChoose].setFillColor(sf::Color::Red);

	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Handle user movement through the options.
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			currentChoose++;
			currentChoose = currentChoose % options.size();
			return true;

		case sf::Keyboard::Down:
			currentChoose--;
			currentChoose = currentChoose % options.size();
			return true;
		}

		// Handle sutuation when user pressed the Enter key.
		if (event.key.code == sf::Keyboard::Enter)
		{
			Options selectedOption = static_cast<Options>(currentChoose);

			switch (selectedOption)
			{
			case MenuState::Options::Play:
				RequestStackPop();
				RequestStackPush(States::ID::Loading);
				break;

			case MenuState::Options::Exit:
				RequestStackPop();
				break;
			}
		}
	}

	return true;
}
