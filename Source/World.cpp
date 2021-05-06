#include "Book/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>


World::World(sf::RenderWindow& window, SoundPlayer& sounds)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mSounds(sounds)
    , mTextures() 
    , mSceneGraph()
    , mSceneLayers()
    , mTileMap()
    , mSpawnTile(9,9)
    , mPlayerNpc(nullptr)
{
    loadTextures();
    buildScene();

    // Prepare the view
    //   mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    // reset player velocity
    mPlayerNpc->setVelocity(0.f, 0.f);

    // Forward commands to scene graph
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    mWorldView.setCenter(mPlayerNpc->getPosition());

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
    mTextures.load(Textures::SmallRoomTileset, "Media/Textures/rpg_indoor.png");
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
    sf::Texture& texture = mTextures.get(Textures::SmallRoomTileset);
    mTileMap.load(texture);
    std::unique_ptr<TileMapNode> backgroundTileMap(new TileMapNode(mTileMap));
    mSceneLayers[Background]->attachChild(std::move(backgroundTileMap));

    sf::Vector2f spawnPosition = mTileMap.getTileBottom(mSpawnTile.x, mSpawnTile.y);
    // FIXME calculate correctly the position of the npc in the tile
    spawnPosition.y += 4;

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
    mPlayerNpc = leader.get();
    mPlayerNpc->setPosition(spawnPosition);
    mSceneLayers[Air]->attachChild(std::move(leader));
}
