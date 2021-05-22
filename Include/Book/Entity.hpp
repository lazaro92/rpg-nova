#ifndef BOOK_ENTITY_HPP
#define BOOK_ENTITY_HPP

#include "Book/SceneNode.hpp"

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


	private:
		sf::Vector2i		mTilePosition;
};

#endif // BOOK_ENTITY_HPP
