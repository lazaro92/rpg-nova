#ifndef BOOK_TILE_MAP_NODE_HPP
#define BOOK_TILE_MAP_NODE_HPP

#include "Book/SceneNode.hpp"

class TileMap;

/**
* Node responsable for the drawing of tiled map.
*/
class TileMapNode : public SceneNode
{
	public:
		explicit			TileMapNode(TileMap& tileMap);

		//virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		TileMap&			mTileMap;
};

#endif // BOOK_TILE_MAP_NODE_HPP
