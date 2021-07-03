#include "Game/TileMapNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>


TileMapNode::TileMapNode(sf::Texture& textTileset)
: mTextTileset(textTileset)
{
}

void TileMapNode::build(const std::vector<int>* tiles, const unsigned int width,
        const unsigned int height, const unsigned int tileSize)
{
    // resize the vertex array to fit the level size
    mVertices.setPrimitiveType(sf::Quads);
    mVertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (std::vector<int>::size_type i = 0; i < width; ++i)
    {
        for (std::vector<int>::size_type j = 0; j < height; ++j)
        {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &mVertices[(i + j * width) * 4];
            // get the current tile number

            int tileNumber = tiles->at(i + j * width);

            if (tileNumber != -1)
            {
                // find its position in the tileset texture
                int tu = tileNumber % (mTextTileset.getSize().x / tileSize);
                int tv = tileNumber / (mTextTileset.getSize().x / tileSize);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
                quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
            }
            else {
                quad[0].color = sf::Color(0,0,0,0);
                quad[1].color = sf::Color(0,0,0,0);
                quad[2].color = sf::Color(0,0,0,0);
                quad[3].color = sf::Color(0,0,0,0);
            }

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);
        }
    }
}

void TileMapNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = &mTextTileset;

    target.draw(mVertices, states);
}
