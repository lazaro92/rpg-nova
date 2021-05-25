#ifndef GAME_COMMAND_HPP
#define GAME_COMMAND_HPP

#include "Game/Category.hpp"

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>


class SceneNode;

/**
* Commands to send to entities.
*/
struct Command
{
												Command();

	std::function<void(SceneNode&, sf::Time)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode& node, sf::Time dt)
	{
		// Check if cast is safe
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		// Downcast node and invoke function on it
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif // GAME_COMMAND_HPP
