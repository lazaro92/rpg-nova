#ifndef GAME_MENUSTATE_HPP
#define GAME_MENUSTATE_HPP

#include "Game/State.hpp"
#include "Game/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
* State that contains the menu for selecting options
*/
class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update(sf::Time dt);
		virtual bool			handleEvent(const sf::Event& event);


	private:
		sf::Sprite				mBackgroundSprite;
		GUI::Container			mGUIContainer;
};

#endif // GAME_MENUSTATE_HPP
