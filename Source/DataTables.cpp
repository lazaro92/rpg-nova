#include "Game/DataTables.hpp"
#include "Game/Npc.hpp"

std::vector<NpcData> initializeNpcData()
{
    std::vector<NpcData> data(Npc::TypeCount);

    data[Npc::Hero].texture = Textures::NpcWalk;
    data[Npc::Hero].textureRect = sf::IntRect(128, 0, 16, 24);

    return data;
}
