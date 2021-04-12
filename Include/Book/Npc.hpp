#ifndef BOOK_NPC_HPP
#define BOOK_NPC_HPP

#include <Book/Entity.hpp>
#include <Book/ResourceIdentifiers.hpp>

#include <SFML/Graphics/Sprite.hpp>


class Npc : public Entity
{
	public:
		enum Type
		{
			Eagle,
			Raptor,
		};


	public:
								Npc(Type type, const TextureHolder& textures);

		virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual unsigned int	getCategory() const;

	private:
		Type					mType;
		sf::Sprite				mSprite;
};

#endif // BOOK_NPC_HPP
