#include "Npc.hpp"
#include "ResourceHolder.hpp"

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
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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
