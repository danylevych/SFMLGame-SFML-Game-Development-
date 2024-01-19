#pragma once

#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{
	class Component : public sf::Drawable
					, public sf::Transformable
					, private sf::NonCopyable
	{
	public:
		using Ptr = std::shared_ptr<Component>;

	private:
		bool isActive;
		bool isSelected;
		
	public:
		Component() = default;
		virtual ~Component() = default;

	public: // Need to be overriden.
		//////////////////////////////////////////////////////////
		// \brief
		//	     Returns true in case when the conponent is
		//       selectable, otherwise returns false.
		// 
		//////////////////////////////////////////////////////////
		virtual bool IsSelectable() const = 0;

		//////////////////////////////////////////////////////////
		// \brief
		//		   Handles the event for the component.
		// 
		//////////////////////////////////////////////////////////
		virtual void HandleEvent(const sf::Event& event) = 0;

		//////////////////////////////////////////////////////////
		// \brief
		//			Draw the component on the screen.
		// 
		//////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates dtates) const override = 0;

	public:
		//////////////////////////////////////////////////////////
		// \brief
		//		Returns the state of the isSelected flag. 
		// 
		//////////////////////////////////////////////////////////
		bool IsSelected() const;

		//////////////////////////////////////////////////////////
		// \brief
		//		Set the isSelected flag into true state.
		// 
		//////////////////////////////////////////////////////////
		virtual void Select();

		//////////////////////////////////////////////////////////
		// \brief
		//		Set the isSelected flag into false state.
		// 
		//////////////////////////////////////////////////////////
		virtual void Deselect();

		//////////////////////////////////////////////////////////
		// \brief
		//    Returns the state, that define is the element is
		//    active.
		// 
		//////////////////////////////////////////////////////////
		virtual bool IsActive() const;

		//////////////////////////////////////////////////////////
		// \brief
		//	        Sets the active state into true.
		// 
		//////////////////////////////////////////////////////////
		virtual void Activate();

		//////////////////////////////////////////////////////////
		// \brief
		//           Sets the active state into false.
		// 
		//////////////////////////////////////////////////////////
		virtual void Deactivate();
	};
}