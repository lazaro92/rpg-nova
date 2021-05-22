#include "Book/Npc.hpp"
#include "Book/DataTables.hpp"
#include "Book/ResourceHolder.hpp"
#include "Book/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <iostream>


namespace
{
    const std::vector<NpcData> Table = initializeNpcData();
}

Npc::Npc(Type type, const TextureHolder& textures, TileMap& tileMap)
    : mType(type)
    , mState(State::Wait)
    , mSprite(textures.get(Table[type].texture), Table[type].textureRect)
      , mTileMap(tileMap)
{
    centerOrigin(mSprite);
}

void Npc::move(Direction direction)
{
    if (mState == State::Wait)
    {
        switch(direction)
        {
            case Left:
                mNextTilePosition.x -= 1;
                break; 
            case Right:
                mNextTilePosition.x += 1;
                break; 
            case Up:
                mNextTilePosition.y -= 1;
                break; 
            case Down:
                mNextTilePosition.y += 1;
                break; 
        }
        mState = State::Move;
    }
}

void Npc::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Npc::updateCurrent(sf::Time dt)
{
    if (mState == State::Move) {
        sf::Vector2f destPosition = mTileMap.getTileBottom(
                mNextTilePosition.x, mNextTilePosition.y);
        // FIXME calculate correctly the position of the npc in the tile
        destPosition.y += 4;

        animTime += dt.asSeconds();    
        
        float x = lerp(mSprite.getPosition().x, destPosition.x, animTime);
        float y = lerp(mSprite.getPosition().y, destPosition.y, animTime);

        mSprite.setPosition(x, y);

        std::cout << "Current Pos " << mSprite.getPosition().x << " " << mSprite.getPosition().y << std::endl;
        std::cout << "Dest Pos " << destPosition.x << " " << destPosition.y << std::endl;

        if (destPosition == mSprite.getPosition())
            mState == State::Wait;            
    }
}

unsigned int Npc::getCategory() const
{
    switch (mType)
    {
        case Hero:
            return Category::PlayerNpc;

        default:
            return Category::Npc;
    }
}

float Npc::lerp(float origin, float dest, float dt)
{
    return origin + dt * (dest - origin);
}
