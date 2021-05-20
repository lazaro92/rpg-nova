#ifndef BOOK_NPC_HPP
#define BOOK_NPC_HPP

#include "Book/Entity.hpp"
#include "Book/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>

/**
* Entity that represents villagers, enemies or heroes
*/
class Npc : public Entity
{
	public:
		enum Type
		{
			Hero,
            TypeCount
		};


	public:
								Npc(Type type, const TextureHolder& textures);

		void				setTileMovement(sf::Vector2i tileMovement);
		void				setTileMovement(int tileMovX, int tileMovY);
		sf::Vector2i		getTileMovement() const;

		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual unsigned int	getCategory() const;

	private:
		Type					mType;
		sf::Sprite				mSprite;

		sf::Vector2i		mTileMovement;
};

#endif // BOOK_NPC_HPP
