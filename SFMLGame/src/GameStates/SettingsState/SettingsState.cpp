#include "SettingsState.h"
#include "../../Tools/Utility.h"


SettingsState::SettingsState(StateStack& stack, Context context)
	: State(stack, context)
	, background()
	, container()
{
	background.setTexture(context.textures->Get(Textures::TextureID::TitleScreen));
	InitButtonsAndLabels();
	UpdateLabels();
}

void SettingsState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	window->draw(background);
	window->draw(container);
}

bool SettingsState::Update(sf::Time deltaTime)
{
	return true;
}

bool SettingsState::HandleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;

	for (size_t action = 0; action < static_cast<size_t>(Player::Action::ActionCount); action++)
	{
		if (bindedButtons[action]->IsActive()) // User selects the key he wants to change.
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				GetContext().player->BindKey(event.key.code, static_cast<Player::Action>(action));
				bindedButtons[action]->Deactivate();
			}
		}
	}

	if (isKeyBinding)
	{
		UpdateLabels();
	}
	else
	{
		container.HandleEvent(event);
	}

	return false;
}

void SettingsState::InitButtonsAndLabels()
{
	AddButonAndLabel(Player::Action::MoveUp,    150.f, "Move Up");
	AddButonAndLabel(Player::Action::MoveDown,  200.f, "Move Down");
	AddButonAndLabel(Player::Action::MoveLeft,  250.f, "Move Left");
	AddButonAndLabel(Player::Action::MoveRight, 300.f, "Move Right");

	auto backButton = std::make_shared<GUI::Button>(*GetContext().textures, *GetContext().fonts);
	backButton->setPosition(80.f, 375.f);
	backButton->SetText("Back");
	backButton->SetCallBack(std::bind(&SettingsState::RequestStackPop, this));

	container.Pack(backButton);
}

void SettingsState::AddButonAndLabel(Player::Action action, float y, const std::string& text)
{
	size_t index = static_cast<size_t>(action);

	FontHolder& fonts = *GetContext().fonts;
	TextureHolder& textures = *GetContext().textures;


	// Init a button.
	bindedButtons[index] = std::make_shared<GUI::Button>(textures, fonts);
	bindedButtons[index]->setPosition(80.f, y);
	bindedButtons[index]->SetText(text);
	bindedButtons[index]->SetToggle(true);

	// Init a label.
	bindedLabels[index] = std::make_shared<GUI::Label>("", fonts);
	bindedLabels[index]->setPosition(300.f, y + 15.f);

	// Pack them.
	container.Pack(bindedButtons[index]);
	container.Pack(bindedLabels[index]);
}

void SettingsState::UpdateLabels()
{
	Player& player = *GetContext().player;

	for (size_t i = 0; i < static_cast<size_t>(Player::Action::ActionCount); i++)
	{
		sf::Keyboard::Key key = player.GetBindedKey(static_cast<Player::Action>(i));
		bindedLabels[i]->SetString(toString(key));
	}
}
