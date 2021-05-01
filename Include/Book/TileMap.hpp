#ifndef BOOK_TILE_MAP_HPP
#define BOOK_TILE_MAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>


class TileMap : public sf::Drawable, public sf::Transformable
{
    public:
                        TileMap();
        void            load(const sf::Texture& tileset);

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int             getTile(int x, int y);
        void            loadLevel();

    private:
        sf::VertexArray mVertices;
        sf::Texture     mTileset;

        std::vector<int>              mLevel;
        const unsigned int            TILE_SIZE = 16;
        unsigned int                  mHeight = 10;
        unsigned int                  mWidth  = 12;
};

#endif
