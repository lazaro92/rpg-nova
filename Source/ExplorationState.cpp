#include "Game/ExplorationState.hpp"

ExplorationState::ExplorationState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.sounds)
, mPlayer(*context.player)
{
}

void ExplorationState::draw()
{
	mWorld.draw();
}

bool ExplorationState::update(sf::Time dt)
{
	mWorld.update(dt);

	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool ExplorationState::handleEvent(const sf::Event& event)
{
	// Game input handling
	CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		requestStackPush(States::Pause);

	return true;
}
