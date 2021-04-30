#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include "Book/ResourceHolder.hpp"
#include "Book/ResourceIdentifiers.hpp"
#include "Book/SceneNode.hpp"
#include "Book/SpriteNode.hpp"
#include "Book/TileMapNode.hpp"
#include "Book/Npc.hpp"
#include "Book/CommandQueue.hpp"
#include "Book/Command.hpp"
#include "Book/TileMap.hpp"
#include "Book/SoundPlayer.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
    class RenderWindow;
}

/**
 * Class that represents the world
 */
class World : private sf::NonCopyable
{
    public:
        explicit							World(sf::RenderWindow& window, SoundPlayer& sounds);
        void								update(sf::Time dt);
        void								draw();

        CommandQueue&						getCommandQueue();


    private:
        void								loadTextures();
        void								buildScene();

        // TODO This can go to TileMap class, but I will decide later
        int                                 getTile(int x, int y):

    private:
        enum Layer
        {
            Background,
            Air,
            LayerCount
        };

    private:
        sf::RenderWindow&					mWindow;
        sf::View							mWorldView;
        TextureHolder						mTextures;
        SoundPlayer&                        mSounds;
        TileMap                             mTileMap;

        SceneNode							mSceneGraph;
        std::array<SceneNode*, LayerCount>	mSceneLayers;
        CommandQueue						mCommandQueue;

        sf::Vector2f						mSpawnPosition;
        Npc*    							mPlayerNpc;

        // map data, should go in a file or another system
        const std::vector<int>              mLevel;
        const unsigned int                  TILE_SIZE = 16;
        const unsigned int                  tileMapHeight = 10;
        const unsigned int                  tileMapWidth  = 12;
};

#endif // BOOK_WORLD_HPP
