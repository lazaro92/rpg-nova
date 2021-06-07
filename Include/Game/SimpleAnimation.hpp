#ifndef GAME_SIMPLEANIMATION_HPP
#define GAME_SIMPLEANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>


#include <vector>


class SimpleAnimation
{
    public:
                SimpleAnimation(std::vector<int>& frames, bool loop, float spf);
        
        void    setFrames(std::vector<int>& frames);
        void    update(sf::Time dt);
        sf::IntRect    updateRect(const sf::IntRect& rect, int textureWidth);
        bool    isFinished();


    private:
        std::vector<int>&       mFrames;
        bool                    mLoop;
        float                   mTime;
        float                   mSpf;
        int                     mIndex;
};

#endif
