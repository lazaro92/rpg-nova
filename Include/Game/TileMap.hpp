#ifndef GAME_TILE_MAP_HPP
#define GAME_TILE_MAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>


class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
                            TileMap();
        void                initialize(std::vector<int>* tileset, unsigned int width, unsigned int height);
        void                setVisible(bool visible);
        void                load(const sf::Texture& tileset);
        int                 getTileId(int tileX, int tileY);
        // WIP This function is not complete and is only for drawing what is viewed
        sf::Vector2i        pointToTile(float ptX, float ptY);
        sf::Vector2f        getTileBottom(int tileX, int tileY);
        bool                isBlocked(int tileX, int tileY);

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::VertexArray     mVertices;
        sf::Texture         mTileset;

        std::vector<int>*                           mLayer;
        const unsigned int                          TILE_SIZE = 16;
        unsigned int                                mHeight;
        unsigned int                                mWidth;
        bool                                        mVisible;
};

#endif
