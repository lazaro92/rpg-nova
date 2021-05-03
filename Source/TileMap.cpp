#include "Book/TileMap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


TileMap::TileMap()
:mVertices()
{
    loadLevel();
}

// TODO move to another place
void TileMap::loadLevel()
{
    std::ifstream in("Media/Tiled/larger_map.cus");

    if (!in || in.fail())
    {
        std::cerr << "Couldn't load map" << std::endl;
    }
    else
    {
        std::string line, val, strHeight, strWidth;
        std::getline(in, strHeight);
        std::getline(in, strWidth);
        
        mHeight = std::stoi(strHeight);
        mWidth = std::stoi(strWidth);

        while (std::getline(in, line))
        {
            std::stringstream s(line);
            while (getline(s, val, ','))
            {
                mLevel.push_back(std::stoi(val));
            }
        }
    }
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
            // get the current tile number
            int tileNumber = mLevel[i + j * mWidth];

            // find its position in the tileset texture
            int tu = tileNumber % (mTileset.getSize().x / TILE_SIZE);
            int tv = tileNumber / (mTileset.getSize().x / TILE_SIZE);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &mVertices[(i + j * mWidth) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * TILE_SIZE, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = &mTileset;

    // draw the vertex array
    target.draw(mVertices, states);
}

int TileMap::getTile(int x, int y)
{
    return mLevel[x + y * mWidth];
}

sf::Vector2i TileMap::pointToTile(float x, float y)
{
    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    return sf::Vector2i(tileX, tileY); 
    
    
}
