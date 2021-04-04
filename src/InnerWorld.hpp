#ifndef INNER_WORLD_HPP
#define INNER_WORLD_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Npc.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>
#include <queue>


// Forward declaration
namespace sf
{
	class RenderWindow;
}

class InnerWorld : private sf::NonCopyable
{
	public:
		explicit							InnerWorld(sf::RenderWindow& window);
		void								update(sf::Time dt);
		void								draw();

        CommandQueue&                       getCommandQueue();

	private:
		void								loadTextures();
		void								buildScene();


	private:
		enum Layer
		{
			Background,
			Ground,
			LayerCount
		};


	private:
		sf::RenderWindow&					mWindow;
		sf::View							mWorldView;
		TextureHolder						mTextures;

		SceneNode							mSceneGraph;
		std::array<SceneNode*, LayerCount>	mSceneLayers;
        CommandQueue                        mCommandQueue;

		Npc*							    mPlayerHero;
};

#endif
