#include "Game/SimpleAnimation.hpp"

#include <cmath>


SimpleAnimation::SimpleAnimation(std::vector<int>& frames, bool loop, float spf): mFrames(frames)
, mLoop(loop)
, mSpf(spf)
{
}

void SimpleAnimation::update(sf::Time dt)
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

void SimpleAnimation::setFrames(std::vector<int>& frames)
{
    mFrames = frames;
    mIndex = fmin(mIndex, frames.size() - 1);
}

sf::IntRect SimpleAnimation::updateRect(const sf::IntRect& rect, int textureWidth)
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

bool SimpleAnimation::isFinished()
{
    return !mLoop && (mIndex == mFrames.size());
}
