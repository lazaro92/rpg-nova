#ifndef GAME_TILE_MAP_NODE_HPP
#define GAME_TILE_MAP_NODE_HPP

#include "Game/SceneNode.hpp"
#include "Game/TileMap.hpp"


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

#endif // GAME_TILE_MAP_NODE_HPP
