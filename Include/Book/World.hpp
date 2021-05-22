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

#include <SFML/Graphics/Text.hpp>


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

        sf::Vector2f						mSpawnTile;
        Npc*    							mPlayerNpc;

        sf::Text                            mTextPlayerPos;
	  	FontHolder				mFonts;
};

#endif // BOOK_WORLD_HPP
