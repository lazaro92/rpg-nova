#ifndef GAME_LABEL_HPP
#define GAME_LABEL_HPP

#include "Game/GUI/Component.hpp"
#include "Game/ResourceIdentifiers.hpp"
#include "Game/ResourceHolder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

/**
* GUI component for displaying text
*/
class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            

	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
		void				setText(const std::string& text);

        virtual void		handleEvent(const sf::Event& event);


    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text			mText;
};

}

#endif // GAME_LABEL_HPP
