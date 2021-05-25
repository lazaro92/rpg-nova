#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "Game/Command.hpp"

#include <SFML/Window/Event.hpp>

#include <map>


class CommandQueue;

/**
* Class that handles the player actions and assign its actions to the keyboard keys.
*/
class Player
{
	public:
		enum Action
		{
			MoveLeft,
			MoveRight,
			MoveUp,
			MoveDown,
			ActionCount
		};


	public:
								Player();

		void					handleEvent(const sf::Event& event, CommandQueue& commands);
		void					handleRealtimeInput(CommandQueue& commands);

		void					assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key		getAssignedKey(Action action) const;

	private:
		void					initializeActions();
		static bool				isRealtimeAction(Action action);


	private:
		std::map<sf::Keyboard::Key, Action>		mKeyBinding;
		std::map<Action, Command>				mActionBinding;
};

#endif // GAME_PLAYER_HPP
