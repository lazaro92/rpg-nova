#include "Book/Npc.hpp"
#include "Book/ResourceHolder.hpp"
#include "Book/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Textures::ID toTextureID(Npc::Type type)
{
	switch (type)
	{
		case Npc::Hero:
			return Textures::Hero;
	}
}

Npc::Npc(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(toTextureID(type)))
{
	centerOrigin(mSprite);
}

void Npc::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Npc::getCategory() const
{
	switch (mType)
	{
		case Hero:
			return Category::PlayerNpc;

		default:
			return Category::Npc;
	}
}
