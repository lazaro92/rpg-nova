#ifndef BOOK_TILE_MAP_NODE_HPP
#define BOOK_TILE_MAP_NODE_HPP

#include "Book/SceneNode.hpp"
#include "Book/TileMap.hpp"


/**
* Node responsable for the drawing of tiled map.
*/
class TileMapNode : public SceneNode
{
	public:
		explicit			TileMapNode(TileMap& tileMap);

		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		TileMap&			mTileMap;
};

#endif // BOOK_TILE_MAP_NODE_HPP
