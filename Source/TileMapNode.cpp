#include "Book/TileMapNode.hpp"

#include <SFML/Graphics/RenderTarget.hpp>


TileMapNode::TileMapNode(TileMap& tileMap)
: mTileMap(tileMap)
{
}

//void TileMapNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
//{
//	target.draw(mTileMap, states);
//}
