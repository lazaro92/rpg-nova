#include "Game/TileMap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>


TileMap::TileMap()
{
}

void TileMap::setWidth(unsigned int width)
{
    mWidth = width;
}

unsigned int TileMap::getWidth() const
{
    return mWidth;
}

void TileMap::setHeight(unsigned int height)
{
    mHeight = height;
}

unsigned int TileMap::getHeight() const
{
    return mHeight;
}

void TileMap::setTilesAtLayer(std::vector<int>* tiles, unsigned int layer)
{
    mLayers.at(layer) = tiles;
}

std::vector<int>* TileMap::getTilesAtLayer(const unsigned int layer) const
{
    return mLayers.at(layer);
}

int TileMap::getTileId(const int tileX, const int tileY, const unsigned int layer) const
{
    return mLayers.at(layer)->at(tileX + tileY * mWidth);
}

sf::Vector2i TileMap::pointToTile(const float ptX, const float ptY)
{
    int tileX = ptX / TILE_SIZE;
    int tileY = ptY / TILE_SIZE;

    return sf::Vector2i(tileX, tileY); 
}

sf::Vector2f TileMap::getTileBottom(const int tileX, const int tileY)
{
    int ptX = TILE_SIZE * tileX + (TILE_SIZE / 2);
    int ptY = TILE_SIZE * tileY;

    return sf::Vector2f(ptX, ptY);
}

bool TileMap::isBlocked(const int tileX, const int tileY, const std::size_t layer) const
{ 
    return mLayers.at(layer)->at(tileX + tileY * mWidth) == 1;
}
