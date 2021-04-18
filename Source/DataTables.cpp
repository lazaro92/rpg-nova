#include "Book/DataTables.hpp"
#include "Book/Npc.hpp"

std::vector<NpcData> initializeNpcData()
{
    std::vector<NpcData> data(Npc::TypeCount);

    data[Npc::Hero].texture = Textures::Hero;

    return data;
}
