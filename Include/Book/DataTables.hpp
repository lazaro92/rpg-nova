#ifndef BOOK_DATA_TABLES_HPP
#define BOOK_DATA_TABLES_HPP

#include "Book/ResourceIdentifiers.hpp"

#include <vector>

class Npc;

struct NpcData
{
    Textures::ID    texture;

};

std::vector<NpcData>    initializeNpcData();

#endif
