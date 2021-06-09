#include "Game/Npc.hpp"
#include "Game/DataTables.hpp"
#include "Game/ResourceHolder.hpp"
#include "Game/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <iostream>


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
    , mAnimation(true, 0.2f)
{
    centerOrigin(mSprite);
    mAnimation.setUniqueFrame(animDown[0]);
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
                mAnimation.setFrames(animLeft);
                break; 
            case Right:
                mNextTilePosition.x += 1;
                mAnimation.setFrames(animRight);
                break; 
            case Up:
                mNextTilePosition.y -= 1;
                mAnimation.setFrames(animUp);
                break; 
            case Down:
                mNextTilePosition.y += 1;
                mAnimation.setFrames(animDown);
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
        moveTime += dt.asSeconds();

        float x, y;
        float f = fmin(moveTime * VELOCITY, 1.0f);
        if (mDirection == Direction::Up || mDirection == Direction::Down)
        {
            x = getPosition().x;
            y = lerp(mOriginPosition.y, mDestPosition.y, f);
            setPosition(x, y);
            if (mDestPosition.y == getPosition().y)
            {
                moveTime = 0.0f;
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
                moveTime = 0.0f;
                mTilePosition = mNextTilePosition; 
                mState = State::Wait;            
            }
        }
    }
    else {
        switch (mDirection) {
            case Up:
                mAnimation.setUniqueFrame(animUp[0]); 
                break;
            case Right:
                mAnimation.setUniqueFrame(animRight[0]); 
                break;
            case Down:
                mAnimation.setUniqueFrame(animDown[0]); 
                break;
            case Left:
                mAnimation.setUniqueFrame(animLeft[0]); 
                break;
        }
    }
    mAnimation.update(dt);
    mSprite.setTextureRect(mAnimation.updateRect(mSprite.getTextureRect(), mSprite.getTexture()->getSize().x));
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
