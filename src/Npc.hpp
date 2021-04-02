#ifndef NPC_HPP
#define NPC_HPP

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>


class Npc : public Entity
{
	public:
		enum Type
		{
			Hero,
		};


	public:
							Npc(Type type, const TextureHolder& textures);

		virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		Type				mType;
		sf::Sprite			mSprite;
};

#endif
