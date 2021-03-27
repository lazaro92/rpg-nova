#include <SFML/Graphics.hpp>

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
    public:
                Game();
        void    run();

    private:
        void    processEvents();
        void    update(sf::Time deltaTime);
        void    render();
        void    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    private:
        static const float		PlayerSpeed;

        sf::RenderWindow mWindow;
        sf::CircleShape mPlayer;

        bool    mIsMovingUp; 
        bool    mIsMovingDown; 
        bool    mIsMovingLeft; 
        bool    mIsMovingRight; 
};

#endif
