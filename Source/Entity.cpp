#include "Book/Entity.hpp"


void Entity::updateCurrent(sf::Time dt)
{	
}

void Entity::setTilePosition(sf::Vector2i tilePosition)
{
    mTilePosition = tilePosition;
}

void Entity::setTilePosition(int tileX, int tileY)
{
    mTilePosition.x = tileX;
    mTilePosition.y = tileY;
}

sf::Vector2i Entity::getTilePosition() const
{
    return mTilePosition;
}

void Entity::addToTilePosition(sf::Vector2i tileMovement)
{
    mTilePosition.x += tileMovement.x;
    mTilePosition.y += tileMovement.y;
}
