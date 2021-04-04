#include "InnerWorld.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


InnerWorld::InnerWorld(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures() 
, mSceneGraph()
, mSceneLayers()
, mPlayerHero(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	// mWorldView.setCenter(mSpawnPosition);
}

void InnerWorld::update(sf::Time dt)
{
    // Forward  commands to scene graph
    while (!mCommandQueue.isEmpty())
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);

	// Apply scene graph updates
	mSceneGraph.update(dt);
}

void InnerWorld::draw()
{
	mWindow.setView(mWorldView);
	mWindow.draw(mSceneGraph);
}

CommandQueue& InnerWorld::getCommandQueue()
{
    return mCommandQueue;
}

void InnerWorld::loadTextures()
{
	mTextures.load(Textures::Hero, "Media/Textures/hero.png");
	mTextures.load(Textures::Tile, "Media/Textures/grass_tile.png");
}

void InnerWorld::buildScene()
{
	// Initialize the different layers
	for (std::size_t i = 0; i < LayerCount; ++i)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();

		mSceneGraph.attachChild(std::move(layer));
	}

	// Prepare the tiled background
	sf::Texture& texture = mTextures.get(Textures::Tile);
	sf::IntRect textureRect(0, 0, 16, 16);
	texture.setRepeated(true);

	// Add the background sprite to the scene
	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(0.0f, 0.0f);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's  hero
	std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
    mPlayerHero = leader.get();
    mPlayerHero->setPosition(0.0f, 0.0f);
	mSceneLayers[Ground]->attachChild(std::move(leader));
}
