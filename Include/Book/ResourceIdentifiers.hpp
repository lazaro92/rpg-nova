#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
    class SoundBuffer;
}

namespace Textures
{
	enum ID
	{
		NpcWalk,
		TitleScreen,
        ArenaTileset,
        
        // temporal
        ButtonNormal,
        ButtonSelected,
        ButtonPressed
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

namespace Music
{
    enum ID
    {
        MenuTheme,
        MissionTheme
    };
}

namespace SoundEffect
{
    enum ID
    {
        AlliedGunfire,
        EnemyGunfire
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>	TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
