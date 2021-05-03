#include "Book/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

// TEMP
#include "Book/Utility.hpp"
#include <SFML/Window/Event.hpp>


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
    // TEMP
    , mFonts()
    , mMousePosText()
    , currentTileText()
    , idTileText()
{
    loadTextures();
    buildScene();

    // Prepare the view
    mWorldView.setCenter(mSpawnPosition);

	mFonts.load(Fonts::Main, 	"Media/Sansation.ttf");
	mMousePosText.setFont(mFonts.get(Fonts::Main));
	mMousePosText.setPosition(15.f, 15.f);
	mMousePosText.setCharacterSize(10u);

	currentTileText.setFont(mFonts.get(Fonts::Main));
	currentTileText.setPosition(15.f, 25.f);
	currentTileText.setCharacterSize(10u);

	idTileText.setFont(mFonts.get(Fonts::Main));
	idTileText.setPosition(15.f, 35.f);
	idTileText.setCharacterSize(10u);
}

void World::update(sf::Time dt)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(mWindow);    
    mMousePosText.setString("X: " + toString(mousePos.x) + " Y: " + toString(mousePos.y));

    sf::Vector2i tilePos = mTileMap.pointToTile(mousePos.x,mousePos.y);
    currentTileText.setString("Tile X: " + toString(tilePos.x) + " Y: " + toString(tilePos.y));
    
    if (tilePos.x >= 0 && tilePos.y >= 0) {   
       int tileId = mTileMap.getTile(tilePos.x, tilePos.y);
        idTileText.setString("Tile Id: " + toString(tileId));
    }

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
    mWindow.draw(mMousePosText);
    mWindow.draw(currentTileText);
    mWindow.draw(idTileText);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::loadTextures()
{
    mTextures.load(Textures::NpcWalk, "Media/Textures/walk_cycle.png");
    mTextures.load(Textures::Cave16Tileset, "Media/Textures/cave16x16.png");
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
    sf::Texture& texture = mTextures.get(Textures::Cave16Tileset);
    mTileMap.load(texture);
    std::unique_ptr<TileMapNode> backgroundTileMap(new TileMapNode(mTileMap));
    mSceneLayers[Background]->attachChild(std::move(backgroundTileMap));

    // Add player's hero
    std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
    mPlayerNpc = leader.get();
    mPlayerNpc->setPosition(mSpawnPosition);
    mSceneLayers[Air]->attachChild(std::move(leader));
}
