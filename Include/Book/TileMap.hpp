#ifndef BOOK_TILE_MAP_HPP
#define BOOK_TILE_MAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>


class TileMap :  public sf::Drawable, public sf::Transformable
{
    public:
        void            load(const sf::Texture& tileset, sf::Vector2u tileSize,
                            const int* tiles,
                            unsigned int width, unsigned int height);

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::VertexArray m_vertices;
        sf::Texture     m_tileset;
};

#endif
