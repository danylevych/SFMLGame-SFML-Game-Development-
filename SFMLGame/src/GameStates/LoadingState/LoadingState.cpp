#include "LoadingState.h"

LoadingState::LoadingState(StateStack& stack, Context context)
	: State(stack, context)
{
	InitLoadingText();
	InitProgressBar();

	SetComplation(0.f);

	loadingTask.Execute();
}

void LoadingState::InitLoadingText()
{
	// Function centrate the origin of the text.
	auto centerOrigin = [](sf::Text& text) {
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(bounds.left + bounds.width / 2.f,
			bounds.top + bounds.height / 2.f);
	};

	sf::Vector2f sizeOfView = GetContext().window->getDefaultView().getSize();
	sf::Font font = GetContext().fonts->Get(Font::FontID::Main);

	loadingText.setFont(font);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setString("Loading Resources");
	centerOrigin(loadingText);
	loadingText.setPosition(sizeOfView.x / 2.f, sizeOfView.y / 2.f + 50.f);
}

void LoadingState::InitProgressBar()
{
	sf::Vector2f sizeOfView = GetContext().window->getDefaultView().getSize();

	// Init the background part.
	progressBarBackground.setFillColor(sf::Color::White);
	progressBarBackground.setSize(sf::Vector2f(sizeOfView.x - 20, 10));
	progressBarBackground.setPosition(10, loadingText.getPosition().y + 40.f);

	// Init the front part.
	progressBar.setFillColor(sf::Color(100, 100, 100));
	progressBar.setSize(progressBarBackground.getSize());
	progressBar.setPosition(progressBarBackground.getPosition());
}

void LoadingState::Draw()
{
	sf::RenderWindow* window = GetContext().window;

	//window.setView(window.getDefaultView());

	window->draw(loadingText);
	//window.draw(progressBarBackground);
	//window.draw(progressBar);
}

bool LoadingState::Update(sf::Time deltaTime)
{
	if (loadingTask.IsFinished())
	{
		RequestStackPop();
		RequestStackPush(States::ID::Game);
	}
	else
	{
		SetComplation(loadingTask.GetCompletion());
	}

	return true;
}

bool LoadingState::HandleEvent(const sf::Event& event)
{
	return true;
}


void LoadingState::SetComplation(float percent)
{
	if (percent > 1.f)
	{
		percent = 1.f;
	}

	sf::Vector2f currentSize = progressBar.getSize();
	currentSize.x = progressBarBackground.getSize().x * percent;

	progressBar.setSize(currentSize);
}