#include "Book/World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "Book/Utility.hpp"


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
    , mTextPlayerPos()
    , mFonts()
{
    loadTextures();
    buildScene();

	mFonts.load(Fonts::Main, 	"Media/Sansation.ttf");
	mTextPlayerPos.setFont(mFonts.get(Fonts::Main));
	mTextPlayerPos.setPosition(5.f, 15.f);
	mTextPlayerPos.setCharacterSize(10u);
}

void World::update(sf::Time dt)
{
    mTextPlayerPos.setString(
        "Pos X: " + toString(mPlayerNpc->getTilePosition().x)
        + " Y: " + toString(mPlayerNpc->getTilePosition().y)
    );

    // Forward commands to scene graph
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

    teleport(mPlayerNpc);    
    mPlayerNpc->setTileMovement(0, 0);

    mWorldView.setCenter(mPlayerNpc->getPosition());

    // Regular update step
    mSceneGraph.update(dt);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);

    mWindow.draw(mTextPlayerPos);
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

void World::teleport(Npc* npc)
{
    npc->addToTilePosition(npc->getTileMovement());
    
    sf::Vector2f position = mTileMap.getTileBottom(npc->getTilePosition().x,
        npc->getTilePosition().y);
    // FIXME calculate correctly the position of the npc in the tile
    position.y += 4;
    npc->setPosition(position);
}
