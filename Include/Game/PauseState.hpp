#ifndef GAME_PAUSESTATE_HPP
#define GAME_PAUSESTATE_HPP

#include "Game/State.hpp"
#include "Game/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
	public:
							PauseState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mPausedText;
		GUI::Container 		mGUIContainer;
};

#endif // GAME_PAUSESTATE_HPP
