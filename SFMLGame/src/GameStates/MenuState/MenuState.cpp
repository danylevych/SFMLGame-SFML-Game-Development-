#include "MenuState.h"
#include "../../GUI/Button/Button.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
{	
	InitBackground();
	InitOptions();
	Update(sf::Time::Zero); // For set the right menu option.
}

void MenuState::InitOptions()
{
	FontHolder& fonts = *GetContext().fonts;
	TextureHolder& textures = *GetContext().textures;

	auto playeButton = std::make_shared<GUI::Button>(textures, fonts);
	playeButton->setPosition(100, 250); 
	playeButton->SetText("Play");
	playeButton->SetCallBack([this]() {
		RequestStackPop();
		RequestStackPush(States::ID::Game);
	});
	
	auto settingsButton = std::make_shared<GUI::Button>(textures, fonts);
	settingsButton->setPosition(100, 300);
	settingsButton->SetText("Settings");
	settingsButton->SetCallBack([this]() {
		RequestStackPush(States::ID::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(textures, fonts);
	exitButton->setPosition(100, 350);
	exitButton->SetText("Exit");
	exitButton->SetCallBack([this]() {
		RequestStackPop();
	});

	optionsContainer.Pack(playeButton);
	optionsContainer.Pack(settingsButton);
	optionsContainer.Pack(exitButton);
}

void MenuState::InitBackground()
{
	background.setTexture(GetContext().textures->Get(Textures::TextureID::TitleScreen));
}

void MenuState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	window->draw(background);
	window->draw(optionsContainer);
}

bool MenuState::Update(sf::Time deltaTime)
{
	return true;
}

bool MenuState::HandleEvent(const sf::Event& event)
{
	optionsContainer.HandleEvent(event);

	return false;
}
