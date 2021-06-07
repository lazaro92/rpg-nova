#ifndef GAME_NPC_HPP
#define GAME_NPC_HPP

#include "Game/Entity.hpp"
#include "Game/TileMap.hpp"
#include "Game/ResourceIdentifiers.hpp"
#include "Game/SimpleAnimation.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>


enum Direction
{
    Left,
    Right,
    Up,
    Down
};
/**
* Entity that represents villagers, enemies or heroes
*/
class Npc : public Entity
{
	public:
		enum Type
		{
			Hero,
            TypeCount
		};
        
        enum State
        {
            Wait,
            Move
        };



	public:
								Npc(Type type, const TextureHolder& textures, TileMap& tileMap);

        void                    move(Direction direction);

		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void		    updateCurrent(sf::Time dt);
		virtual unsigned int	getCategory() const;

    // TODO functions to reorganize
    private:
        float                   lerp(float origin, float dest, float dt);

	private:
        TileMap&                mTileMap;
		Type					mType;
        State                   mState;
        Direction               mDirection;
        SimpleAnimation         mAnimation;
		sf::Sprite				mSprite;

		sf::Vector2i            mNextTilePosition;

        sf::Vector2f            mOriginPosition;
        sf::Vector2f            mDestPosition;
        float                   animTime;
        // TODO add Static
        const float             VELOCITY = 2.0f;
        
        std::vector<int>         animUp = {0,1,2,3};
        std::vector<int>         animRight = {4,5,6,7};
        std::vector<int>         animDown = {8,9,10,11};
        std::vector<int>         animLeft = {12,13,14,15};
};

#endif // GAME_NPC_HPP
