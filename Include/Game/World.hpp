#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include "Game/ResourceHolder.hpp"
#include "Game/ResourceIdentifiers.hpp"
#include "Game/SceneNode.hpp"
#include "Game/SpriteNode.hpp"
#include "Game/TileMapNode.hpp"
#include "Game/Npc.hpp"
#include "Game/CommandQueue.hpp"
#include "Game/Command.hpp"
#include "Game/TileMap.hpp"
#include "Game/SoundPlayer.hpp"

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

        sf::Vector2i						mSpawnTile;
        Npc*    							mPlayerNpc;

        sf::Text                            mTextPlayerPos;
	  	FontHolder				mFonts;
};

#endif // GAME_WORLD_HPP
