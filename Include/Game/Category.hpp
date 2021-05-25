#ifndef GAME_CATEGORY_HPP
#define GAME_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		PlayerNpc   		= 1 << 1,
		Npc         		= 1 << 2,
		//EnemyAircraft		= 1 << 3,
	};
}

#endif // GAME_CATEGORY_HPP
