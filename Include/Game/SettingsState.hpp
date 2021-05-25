#ifndef GAME_SETTINGSSTATE_HPP
#define GAME_SETTINGSSTATE_HPP

#include "Game/State.hpp"
#include "Game/Player.hpp"
#include "Game/Container.hpp"
#include "Game/Button.hpp"
#include "Game/Label.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context context);

		virtual void					draw();
		virtual bool					update(sf::Time dt);
		virtual bool					handleEvent(const sf::Event& event);


	private:
		void							updateLabels();
		void							addButtonLabel(Player::Action action, float y, const std::string& text, Context context);


	private:
		sf::Sprite											mBackgroundSprite;
		GUI::Container										mGUIContainer;
		std::array<GUI::Button::Ptr, Player::ActionCount>	mBindingButtons;
		std::array<GUI::Label::Ptr, Player::ActionCount> 	mBindingLabels;
};

#endif // GAME_SETTINGSSTATE_HPP
