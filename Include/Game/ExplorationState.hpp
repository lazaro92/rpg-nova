#ifndef GAME_EXPLORATIONSTATE_HPP
#define GAME_EXPLORATIONSTATE_HPP

#include "Game/State.hpp"
#include "Game/World.hpp"
#include "Game/Player.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

/**
* State that is for playing the game 
*/
class ExplorationState : public State
{
	public:
							ExplorationState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		World				mWorld;
		Player&				mPlayer;
};

#endif // GAME_GAMESTATE_HPP
