#include "Book/Npc.hpp"
#include "Book/DataTables.hpp"
#include "Book/ResourceHolder.hpp"
#include "Book/Utility.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace
{
    const std::vector<NpcData> Table = initializeNpcData();
}

Npc::Npc(Type type, const TextureHolder& textures)
: mType(type)
, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
{
	centerOrigin(mSprite);
}

void Npc::setTileMovement(sf::Vector2i tileMovement)
{
	mTileMovement = tileMovement;
}

void Npc::setTileMovement(int tileMovX, int tileMovY)
{
	mTileMovement.x = tileMovX;
	mTileMovement.y = tileMovY;
}

sf::Vector2i Npc::getTileMovement() const
{
	return mTileMovement;
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
