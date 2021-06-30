#include "Game/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Game/Utility.hpp"

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
    , mTileMapBgr()
    , mTileMapItZ0()
    , mTileMapItZ1()
    , mTileCollision()
    , mSpawnTile(10,2)
    , mPlayerNpc(nullptr)
{
    loadTextures();
    buildTileMaps();
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

void World::buildTileMaps()
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

        unsigned int layerCount = 0;
        unsigned int lineCount = 0;
        std::vector<int>* tiles = new std::vector<int>; 
        
        while (std::getline(in, line))
        {
            std::stringstream s(line);
            while (getline(s, val, ','))
            {
                tiles->push_back(std::stoi(val));
            }
            ++lineCount;
            if (lineCount >= height)
            {
                if (layerCount == 0)
                {
                    // add height, width and tileMap array
                    mTileMapBgr.initialize(tiles, width, height);
                }
                else if (layerCount == 1)
                {
                    // add height, width and tileMap array
                    mTileMapItZ0.initialize(tiles, width, height);
                }
                else if (layerCount == 2)
                {
                    // add height, width and tileMap array
                    mTileMapItZ1.initialize(tiles, width, height);
                }
                else if (layerCount == 3)
                {
                    // add height, width and tileMap array
                    mTileCollision.initialize(tiles, width, height);
                    mTileCollision.setVisible(false);
                }
                lineCount = 0;
                ++layerCount;
                tiles = new std::vector<int>; 
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
    mTileMapBgr.load(texture);
    std::unique_ptr<TileMapNode> TileMapNodeBgr(new TileMapNode(mTileMapBgr));
    mSceneLayers[TileBackground]->attachChild(std::move(TileMapNodeBgr));

    mTileMapItZ0.load(texture);
    std::unique_ptr<TileMapNode> TileMapNodeItZ0(new TileMapNode(mTileMapItZ0));
    mSceneLayers[TileItemsZ0]->attachChild(std::move(TileMapNodeItZ0));

    mTileMapItZ1.load(texture);
    std::unique_ptr<TileMapNode> TileMapNodeItZ1(new TileMapNode(mTileMapItZ1));
    mSceneLayers[TileItemsZ1]->attachChild(std::move(TileMapNodeItZ1));

    mTileCollision.load(texture);
    std::unique_ptr<TileMapNode> TileMapCollision(new TileMapNode(mTileCollision));
    mSceneLayers[TileItemsZ1]->attachChild(std::move(TileMapCollision));

    sf::Vector2f spawnPosition = mTileMapItZ0.getTileBottom(mSpawnTile.x, mSpawnTile.y);
    // FIXME calculate correctly the position of the npc in the tile
    spawnPosition.y += 4.0f;

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures, mTileCollision));
    mPlayerNpc = leader.get();
    mPlayerNpc->setTilePosition(mSpawnTile);
    mPlayerNpc->setPosition(spawnPosition);
    mSceneLayers[Npcs]->attachChild(std::move(leader));
}
