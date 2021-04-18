#ifndef BOOK_DATA_TABLES_HPP
#define BOOK_DATA_TABLES_HPP

#include "Book/ResourceIdentifiers.hpp"

#include <SFML/Graphics/Rect.hpp>

#include <vector>

class Npc;

struct NpcData
{
    Textures::ID    texture;
    sf::IntRect     textureRect;
};

std::vector<NpcData>    initializeNpcData();

#endif
