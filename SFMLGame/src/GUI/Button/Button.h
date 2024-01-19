#pragma once

#include "../Component/Component.h"
#include "../../Holders/Holders.h"

#include <functional>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace GUI
{
	class Button : public Component
	{
	public:
		using Ptr = std::shared_ptr<Button>;
		using Callback = std::function<void()>;

	private:
		//========= Additional settings ==========
		Callback callback;
		sf::Text text;
		bool isToggle;

		//========== Texture ===========
		sf::Texture normalTesxture;
		sf::Texture selectedTexture;
		sf::Texture pressedTexture;

		//========== Sprite ===========
		sf::Sprite sprite;

	public:
		Button(TextureHolder& textures, FontHolder& fonts);

		virtual ~Button() override = default;

	public: // Overloaded methods.
		///////////////////////////////////////////////////////////
		// \brief
		//     Return true if we can select the component, for 
		//     the Button it allways returns true.
		// 
		///////////////////////////////////////////////////////////
		virtual bool IsSelectable() const override;

		///////////////////////////////////////////////////////////
		// \brief
		//	  Handles the events for the button actualy empty.
		// 
		///////////////////////////////////////////////////////////
		virtual void HandleEvent(const sf::Event& event) override;

		///////////////////////////////////////////////////////////
		// \brief
		//			Draw the button on the game screen.
		// 
		///////////////////////////////////////////////////////////
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		///////////////////////////////////////////////////////////
		// \brief
		//    We override the method because the button's texture 
		//    have to change if it is selected.
		// 
		///////////////////////////////////////////////////////////
		virtual void Select() override;

		///////////////////////////////////////////////////////////
		// \brief
		// 	  We override the method because the button's texture 
		//    have to change if it is deselected.
		// 
		///////////////////////////////////////////////////////////
		virtual void Deselect() override;

		///////////////////////////////////////////////////////////
		// \brief
		//    We override the method because the button's texture 
		//    have to change if it is active.
		// 
		///////////////////////////////////////////////////////////
		virtual void Activate() override;

		///////////////////////////////////////////////////////////
		// \brief
		// 	  We override the method because the button's texture 
		//    have to change if it is deactive.
		// 
		///////////////////////////////////////////////////////////
		virtual void Deactivate() override;

	public: // Setters section.
		void SetCallBack(Callback callback);
		void SetText(const std::string& text);
		void SetToggle(bool flag);

	};
}
