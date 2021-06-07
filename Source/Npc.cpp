#include "Game/Npc.hpp"
#include "Game/DataTables.hpp"
#include "Game/ResourceHolder.hpp"
#include "Game/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>


namespace
{
    const std::vector<NpcData> Table = initializeNpcData();
}

Npc::Npc(Type type, const TextureHolder& textures, TileMap& tileMap)
    : mType(type)
    , mState(State::Wait)
    , mDirection(Direction::Down)
    , mSprite(textures.get(Table[type].texture), Table[type].textureRect)
    , mTileMap(tileMap)
    , mAnimation(animDown, true, sf::seconds(1.0f).asSeconds())
{
    centerOrigin(mSprite);
}

void Npc::move(Direction direction)
{
    if (mState == State::Wait)
    {
        mNextTilePosition = mTilePosition;
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
        mDirection = direction;
        mState = State::Move;

        mDestPosition = mTileMap.getTileBottom(
                mNextTilePosition.x, mNextTilePosition.y);
        // FIXME calculate correctly the position of the npc in the tile
        mDestPosition.y += 4.0f;
        mOriginPosition = getPosition();
    }
}

void Npc::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Npc::updateCurrent(sf::Time dt)
{
    if (mState == State::Move)
    {
        animTime += dt.asSeconds();

        float x, y;
        float f = fmin(animTime * VELOCITY, 1.0f);
        //float f = animTime;
        if (mDirection == Direction::Up || mDirection == Direction::Down)
        {
            x = getPosition().x;
            y = lerp(mOriginPosition.y, mDestPosition.y, f);
            setPosition(x, y);
            if (mDestPosition.y == getPosition().y)
            {
                animTime = 0.0f;
                mTilePosition = mNextTilePosition; 
                mState = State::Wait;            
            }
        }
        else
        {
            x = lerp(mOriginPosition.x, mDestPosition.x, f);
            y = getPosition().y;
            setPosition(x, y);
            if (mDestPosition.x == getPosition().x)
            {
                animTime = 0.0f;
                mTilePosition = mNextTilePosition; 
                mState = State::Wait;            
            }
        }
    }
    else {
        mAnimation.update(dt);
        
        mSprite.setTextureRect(mAnimation.updateRect(mSprite.getTextureRect(), mSprite.getTexture()->getSize().y));
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
