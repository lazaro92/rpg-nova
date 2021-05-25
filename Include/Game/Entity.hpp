#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "Game/SceneNode.hpp"

/**
* Game object entity
*/
class Entity : public SceneNode
{
	public:
		void				setTilePosition(sf::Vector2i tilePosition);
		void				setTilePosition(int tileX, int tileY);
		sf::Vector2i		getTilePosition() const;

	private:
		virtual void		updateCurrent(sf::Time dt);


	protected:
		sf::Vector2i		mTilePosition;
};

#endif // GAME_ENTITY_HPP
