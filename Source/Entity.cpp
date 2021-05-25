#include "Game/Entity.hpp"


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

