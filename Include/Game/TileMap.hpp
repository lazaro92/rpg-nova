#ifndef GAME_TILE_MAP_HPP
#define GAME_TILE_MAP_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>
#include <array>


class TileMap
{
    public:
                            TileMap();
        
        void                setWidth(unsigned int width);
        unsigned int        getWidth() const;
        void                setHeight(unsigned int height);
        unsigned int        getHeight() const;
        void                setTilesAtLayer(std::vector<int>* tiles, unsigned int layer);
        std::vector<int>*   getTilesAtLayer(const unsigned int layer) const;
        

        int                 getTileId(const int tileX, const int tileY, const unsigned int layer) const;
        // WIP This function is not complete and is only for drawing what is viewed
        sf::Vector2i        pointToTile(const float ptX, const float ptY);
        sf::Vector2f        getTileBottom(const int tileX, const int tileY);
        bool                isBlocked(const int tileX, const int tileY,
                                const std::size_t layer=3) const;

    private:
        const static std::size_t                    LAYER_COUNT = 4;
        std::array<std::vector<int>*, 4>            mLayers;
        const static unsigned int                   TILE_SIZE = 16;
        unsigned int                                mHeight;
        unsigned int                                mWidth;
};

#endif
