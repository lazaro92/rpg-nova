#include "Book/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mTextures() 
    , mSceneGraph()
    , mSceneLayers()
    , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f)
      , mPlayerNpc(nullptr)
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
    sf::IntRect textureRect(0, 0, 16, 16);

    const int level[] = {
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
    };
    std::unique_ptr<TileMapNode> backgroundTileMap(new TiledMapNode());
    backgroundTileMap.load(texture, sf::Vector2u(16,16), level, 12, 10);
    mSceneLayers[Background]->attachChild(std::move(backgroundTileMap));

    // Add the background sprite to the scene
    //std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    //backgroundSprite->setPosition(16,16);
    //mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
    mPlayerNpc = leader.get();
    mPlayerNpc->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(leader));
}
