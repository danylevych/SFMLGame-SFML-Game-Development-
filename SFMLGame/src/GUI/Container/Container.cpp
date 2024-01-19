#include "Container.h"

GUI::Container::Container()
	: Component()
	, children()
	, selectedChild(-1) // We haven't any children.
{	}

bool GUI::Container::IsSelectable() const
{
	return false;
}

void GUI::Container::HandleEvent(const sf::Event& event)
{
	// Why do we use the sf::Event::KeyReleased instand of KeyPressed? 
	if (HasSelection() && children[selectedChild]->IsActive())
	{
		children[selectedChild]->HandleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		sf::Keyboard::Key key = event.key.code;

		if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
		{
			SelectPrevious();
		}
		else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
		{
			SelectNext();
		}
		else if (key == sf::Keyboard::Return || key == sf::Keyboard::Space)
		{
			if (HasSelection())
			{
				children[selectedChild]->Activate();
			}
		}
	}
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	// Run thought all childrens and draw they.
	for (auto& component : children)
	{
		target.draw(*component, states);
	}
}

void GUI::Container::Pack(Component::Ptr component)
{
	children.push_back(component);

	// Set the selected component if we don't have one.
	if (!HasSelection() && component->IsSelectable())
	{
		SelectComponent(children.size() - 1);
	}
}

bool GUI::Container::HasSelection() const
{
	return selectedChild >= 0;
}

void GUI::Container::SelectPrevious()
{
	if (!HasSelection())
	{
		return;
	}

	// Find the previous element that we can select.
	int previous = selectedChild;
	do
	{
		previous = (previous + children.size() - 1) % children.size();
	} while (!children[previous]->IsSelectable());

	SelectComponent(previous);
}

void GUI::Container::SelectNext()
{
	if(!HasSelection())
	{
		return;
	}

	// Find the next element that we can select.
	int next = selectedChild;
	do
	{
		next = (static_cast<size_t>(next) + 1) % children.size();
	} while (!children[next]->IsSelectable());

	SelectComponent(next);
}

void GUI::Container::SelectComponent(size_t index)
{
	if (children[index]->IsSelectable())
	{
		if (HasSelection())
		{
			children[selectedChild]->Deselect();
		}

		selectedChild = index;
		children[selectedChild]->Select();
	}
}
