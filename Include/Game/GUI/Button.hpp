
#ifndef GAME_BUTTON_HPP
#define GAME_BUTTON_HPP

#include "Game/GUI/Component.hpp"
#include "Game/ResourceIdentifiers.hpp"
#include "Game/ResourceHolder.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

/**
* Button for the GUI
*/
class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;


	public:
								Button(const FontHolder& fonts, const TextureHolder& textures);

        void					setCallback(Callback callback);
        void					setText(const std::string& text);
        void					setToggle(bool flag);

        virtual bool			isSelectable() const;
        virtual void			select();
        virtual void			deselect();

        virtual void			activate();
        virtual void			deactivate();

        virtual void			handleEvent(const sf::Event& event);


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback				mCallback;
        const sf::Texture&		mNormalTexture;
        const sf::Texture&		mSelectedTexture;
        const sf::Texture&		mPressedTexture;
        sf::Sprite				mSprite;
        sf::Text				mText;
        bool					mIsToggle;
};

}

#endif // GAME_BUTTON_HPP
