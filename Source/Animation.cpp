#include "Game/Animation.hpp"

#include <cmath>


Animation::Animation(bool loop, float spf):
mFrames({})
, mLoop(loop)
, mSpf(spf)
{
}

void Animation::update(sf::Time dt)
{
    mTime += dt.asSeconds();
    if (mTime >= mSpf)
    {
        ++mIndex;
        mTime = 0;
        if (mIndex >= mFrames.size())
        {
            mIndex = mLoop ? 0: mFrames.size() - 1;
        }
    }
}

void Animation::setUniqueFrame(int frame)
{
    mIndex = 0;
    mFrames.clear();
    mFrames.push_back(frame);
}

void Animation::setFrames(std::vector<int>& frames)
{
    mFrames = frames;
    mIndex = fmin(mIndex, frames.size() - 1);
}

sf::IntRect Animation::updateRect(const sf::IntRect& rect, int textureWidth)
{
    sf::IntRect newRect(rect);
    int x = mFrames[mIndex] * rect.width;
    if (x < textureWidth)
    {
        newRect.left = x;
        newRect.top = 0;
    }
    else
    {
        newRect.top = x % textureWidth;
        newRect.left = (x / textureWidth) * rect.height;
    }
    return newRect;
}

bool Animation::isFinished()
{
    return !mLoop && (mIndex == mFrames.size());
}
