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
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
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
	mTextures.load(Textures::Hero, "Media/Textures/hero.png");
	//mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
	//mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
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
	// sf::Texture& texture = mTextures.get(Textures::Desert);
	// sf::IntRect textureRect(mWorldBounds);
	// texture.setRepeated(true);

	// Add the background sprite to the scene
	// std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	// backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
	// mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	// Add player's hero
	std::unique_ptr<Npc> leader(new Npc(Npc::Hero, mTextures));
	mPlayerNpc = leader.get();
	mPlayerNpc->setPosition(mSpawnPosition);
	mSceneLayers[Air]->attachChild(std::move(leader));
}
