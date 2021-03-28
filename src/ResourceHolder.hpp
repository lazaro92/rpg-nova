#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <SFML/Graphics.hpp>
#include "EnumTextures.hpp"

#include <memory>
#include <map>

// WARN: it does implement the other load methods for shaders in page 45

template<typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void             load(Identifier id, const std::string& filename);     
        Resource&        get(Identifier id);
        const Resource&  get(Identifier id) const;

    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#endif
