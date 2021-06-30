#include "Game/TileMap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>


TileMap::TileMap()
    : mVertices()
      , mVisible(true)
{
}

void TileMap::initialize(std::vector<int>* tileset, unsigned int width, unsigned int height)
{
    mLayer = tileset;
    mHeight = height;
    mWidth = width;
}

void TileMap::setVisible(bool visible)
{
    mVisible = visible;
}

void TileMap::load(const sf::Texture& tileset)
{
    mTileset = tileset;

    // resize the vertex array to fit the level size
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(mWidth * mHeight * 4);

    // populate the vertex array, with one quad per tile
    for (std::vector<int>::size_type i = 0; i < mWidth; ++i)
    {
        for (std::vector<int>::size_type j = 0; j < mHeight; ++j)
        {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &mVertices[(i + j * mWidth) * 4];
            // get the current tile number

            int tileNumber = mLayer->at(i + j * mWidth);

            if (tileNumber != -1)
            {
                // find its position in the tileset texture
                int tu = tileNumber % (mTileset.getSize().x / TILE_SIZE);
                int tv = tileNumber / (mTileset.getSize().x / TILE_SIZE);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
                quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
                quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
                quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
            }
            else {
                quad[0].color = sf::Color(0,0,0,0);
                quad[1].color = sf::Color(0,0,0,0);
                quad[2].color = sf::Color(0,0,0,0);
                quad[3].color = sf::Color(0,0,0,0);
            }

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (mVisible)
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &mTileset;

        // draw the vertex array
        target.draw(mVertices, states);
    }
}

int TileMap::getTileId(int tileX, int tileY)
{
    return mLayer->at(tileX + tileY * mWidth);
}

sf::Vector2i TileMap::pointToTile(float ptX, float ptY)
{
    int tileX = ptX / TILE_SIZE;
    int tileY = ptY / TILE_SIZE;

    return sf::Vector2i(tileX, tileY); 
}

sf::Vector2f TileMap::getTileBottom(int tileX, int tileY)
{
    int ptX = TILE_SIZE * tileX + (TILE_SIZE / 2);
    int ptY = TILE_SIZE * tileY;

    return sf::Vector2f(ptX, ptY);
}

bool TileMap::isBlocked(int tileX, int tileY)
{
    return mLayer->at(tileX + tileY * mWidth) == 1;
}
