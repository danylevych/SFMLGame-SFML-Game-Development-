#pragma once

#include "../Component/Component.h"

#include <vector>


namespace GUI
{
	//////////////////////////////////////////////////////////
	// \brief
	//	   Represent the container for all GUI components.
	// 
	//////////////////////////////////////////////////////////
	class Container : public Component
	{
	public:
		using Ptr = std::shared_ptr<Container>;

	private:
		int32_t selectedChild;
		std::vector<Component::Ptr> children;

	public:
		Container();

		virtual ~Container() override = default;

	public: // Overriden methods.
		////////////////////////////////////////////////////////////
		// \brief
		//		If our component is selectable, for this one
		//		it allways returns false.
		// 
		////////////////////////////////////////////////////////////
		virtual bool IsSelectable() const override;

		////////////////////////////////////////////////////////////
		// \brief
		//		Handles events for the container.
		// 
		////////////////////////////////////////////////////////////
		virtual void HandleEvent(const sf::Event& event) override;

		////////////////////////////////////////////////////////////
		// \brief
		//		Draw the container on the application screen.
		// 
		////////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		////////////////////////////////////////////////////////////
		// \brief
		//			 Add the component to container.
		// 
		////////////////////////////////////////////////////////////
		void Pack(Component::Ptr component);

	private:
		////////////////////////////////////////////////////////////
		// \brief
		//	  Return true if selected index of child is correct
		//    it means in borders [0; children.size() - 1]
		// 
		////////////////////////////////////////////////////////////
		bool HasSelection() const;

		////////////////////////////////////////////////////////////
		// \brief
		//		Select the previous component in sequence.
		// 
		////////////////////////////////////////////////////////////
		void SelectPrevious();

		////////////////////////////////////////////////////////////
		// \brief
		//		Select the next component in sequence.
		// 
		////////////////////////////////////////////////////////////
		void SelectNext();

		////////////////////////////////////////////////////////////
		// \brief
		//	  Select the element under some index in container.
		// 
		////////////////////////////////////////////////////////////
		void SelectComponent(size_t index);
	};
}