#pragma once

#include "../../Holders/Holders.h"
#include "../Component/Component.h"
#include <SFML/Graphics/Text.hpp>

namespace GUI
{
	/////////////////////////////////////////////////////////
	// \brief
	//	Represent the label component for the aplication.
	// 
	/////////////////////////////////////////////////////////
	class Label : public Component
	{
	public:
		using Ptr = std::shared_ptr<Label>;

	private:
		sf::Text text;

	public:
		Label() = default;
		Label(const std::string& text, FontHolder& fonts, size_t charSize = 16);

		virtual ~Label() override = default;

	public: // Overloaded methods.
		///////////////////////////////////////////////////////////
		// \brief
		//     Return true if we can select the component, for 
		//     the Label it allways returns false.
		// 
		///////////////////////////////////////////////////////////
		virtual bool IsSelectable() const override;

		///////////////////////////////////////////////////////////
		// \brief
		//		Handles the events for the label actualy empty.
		// 
		///////////////////////////////////////////////////////////
		virtual void HandleEvent(const sf::Event& event) override;

		///////////////////////////////////////////////////////////
		// \brief
		//			Draw the label on the game screen.
		// 
		///////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public: // Set's methods.
		void SetFont(const sf::Font& font);
		void SetString(const std::string& text);
		void SetCharacterSize(size_t size);
		void SetFontColor(const sf::Color& color);
	};
}
