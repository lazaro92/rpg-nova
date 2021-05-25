#ifndef GAME_TITLESTATE_HPP
#define GAME_TITLESTATE_HPP

#include "Game/State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
* First state to execute. Shows the gmae title and the options to start the game
*/
class TitleState : public State
{
	public:
							TitleState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mText;

		bool				mShowText;
		sf::Time			mTextEffectTime;
};

#endif // GAME_TITLESTATE_HPP
