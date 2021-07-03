#include "Game/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Game/Utility.hpp"
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


World::World(sf::RenderWindow& window, SoundPlayer& sounds)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mSounds(sounds)
    , mTextures() 
    , mSceneGraph()
    , mSceneLayers()
    , mTileMap()
    , mSpawnTile(10,2)
    , mPlayerNpc(nullptr)
{
    loadTextures();
    buildTileMap();
    buildScene();
}

void World::update(sf::Time dt)
{
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

void World::buildTileMap()
{
    std::ifstream in("Data/Tiled/small_room.cus");

    if (!in || in.fail())
    {
        std::cerr << "Couldn't load map" << std::endl;
    }
    else
    {
        std::string line, val, strHeight, strWidth;
        std::getline(in, strHeight);
        std::getline(in, strWidth);

        unsigned int height = std::stoi(strHeight);
        unsigned int width = std::stoi(strWidth);

        mTileMap.setHeight(height);
        mTileMap.setWidth(width);

        unsigned int layerCount = 0;
        unsigned int lineCount = 0;
        std::unique_ptr<std::vector<int>> Ptiles(new std::vector<int>);
        
        while (std::getline(in, line))
        {
            std::stringstream s(line);
            while (getline(s, val, ','))
            {
                Ptiles->push_back(std::stoi(val));
            }
            ++lineCount;
            if (lineCount >= height)
            {
                mTileMap.setTilesAtLayer(Ptiles, layerCount);
                lineCount = 0;
                ++layerCount;
                Ptiles.reset(new std::vector<int>);
            }
        }
    }
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
        
    std::unique_ptr<TileMapNode> tileMapNode1(new TileMapNode(texture));
    tileMapNode1->build(mTileMap.getTilesAtLayer(0), mTileMap.getWidth(), mTileMap.getHeight(), 16);
    mSceneLayers[TileBackground]->attachChild(std::move(tileMapNode1));

    std::unique_ptr<TileMapNode> tileMapNode2(new TileMapNode(texture));
    tileMapNode2->build(mTileMap.getTilesAtLayer(1), mTileMap.getWidth(), mTileMap.getHeight(), 16);
    mSceneLayers[TileItemsZ0]->attachChild(std::move(tileMapNode2));

    std::unique_ptr<TileMapNode> tileMapNode3(new TileMapNode(texture));
    tileMapNode3->build(mTileMap.getTilesAtLayer(2), mTileMap.getWidth(), mTileMap.getHeight(), 16);
    mSceneLayers[TileItemsZ1]->attachChild(std::move(tileMapNode3));

    sf::Vector2f spawnPosition = mTileMap.getTileBottom(mSpawnTile.x, mSpawnTile.y);
    // FIXME calculate correctly the position of the npc in the tile
    spawnPosition.y += 4.0f;

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures, mTileMap));
    mPlayerNpc = leader.get();
    mPlayerNpc->setTilePosition(mSpawnTile);
    mPlayerNpc->setPosition(spawnPosition);
    mSceneLayers[Npcs]->attachChild(std::move(leader));
}
