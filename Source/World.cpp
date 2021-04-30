#include "Book/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window, SoundPlayer& sounds)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mSounds(sounds)
    , mTextures() 
    , mSceneGraph()
    , mSceneLayers()
    , mTileMap()
    , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
    , mPlayerNpc(nullptr)
    , mLevel({
            1,1,1,1,1,1,1,1,1,1,1,1,
            1,33,33,291,1,1,1,1,1,1,1,1,
            1,65,101,99,1,1,32,1,289,1,1,1,
            1,65,67,1,1,1,1,1,1,1,1,1,
            0,65,67,1,1,32,32,32,32,1,1,1,
            1,65,67,1,1,32,1,1,10,11,1,1,
            1,97,99,1,1,32,32,1,42,43,1,1,
            1,1,1,1,1,230,231,32,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1
        })
{
    loadTextures();
    buildScene();

    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    // reset player velocity
    mPlayerNpc->setVelocity(0.f, 0.f);

    // Forward commands to scene graph
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    // Regular update step
    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::NpcWalk, "Media/Textures/walk_cycle.png");
    mTextures.load(Textures::ArenaTileset, "Media/Textures/tileset_arena.png");
}

void World::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::ArenaTileset);
    mTileMap.load(texture, TILE_SIZE, mLevel, tileMapWidth, tileMapHeight);
    std::unique_ptr<TileMapNode> backgroundTileMap(new TileMapNode(mTileMap));
    mSceneLayers[Background]->attachChild(std::move(backgroundTileMap));

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
    mPlayerNpc = leader.get();
    mPlayerNpc->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(leader));
}

// TODO This can go to TileMap class, but I will decide later
int World::getTile(int x, int y)
{
    x = x + 1;
    return mLevel[x + y * rowSize];
}


