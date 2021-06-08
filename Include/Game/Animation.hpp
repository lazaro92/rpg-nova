#ifndef GAME_ANIMATION_HPP
#define GAME_ANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>


#include <vector>


class Animation
{
    public:
                Animation(bool loop, float spf);
        
        void    setFrames(std::vector<int>& frames);
        void    update(sf::Time dt);
        sf::IntRect    updateRect(const sf::IntRect& rect, int textureWidth);
        bool    isFinished();


    private:
        std::vector<int>        mFrames;
        bool                    mLoop;
        float                   mTime;
        float                   mSpf;
        int                     mIndex;
};

#endif
