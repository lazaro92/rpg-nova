#ifndef GAME_TILE_MAP_NODE_HPP
#define GAME_TILE_MAP_NODE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp> 

#include "Game/SceneNode.hpp"

/**
* Node responsable for the drawing of tiled map.
*/
class TileMapNode : public SceneNode
{
	public:
		explicit			TileMapNode(sf::Texture& textTileset);
        
        void                build(const std::vector<int>* tiles, const unsigned int width,
                                const unsigned int height, const unsigned int tileSize);


		virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
        sf::Texture&        mTextTileset;
        sf::VertexArray     mVertices;
};

#endif // GAME_TILE_MAP_NODE_HPP
