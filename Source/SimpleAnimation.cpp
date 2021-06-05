#include "Game/SimpleAnimation.hpp"

#include <cmath>


SimpleAnimation::SimpleAnimation(std::vector<int>& frames, bool loop, float spf): mFrames(frames)
, mLoop(loop)
, mSpf(spf)
{
}

void SimpleAnimation::update(sf::Time dt)
{
    mTime +=  dt.asSeconds();
    if (mTime >= mSpf)
    {
        ++mIndex;
        mTime = 0;
        if (mIndex > mFrames.size())
        {
            mIndex = mLoop ? 1: mFrames.size();
        }
    }
}

void SimpleAnimation::setFrames(std::vector<int>& frames)
{
    mFrames = frames;
    mIndex = fmin(mIndex, frames.size());
}

bool SimpleAnimation::isFinished()
{
    return !mLoop && (mIndex == mFrames.size());
}
