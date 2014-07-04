#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <SFGE/Core/CollidableNode.h>
#include "Constants.h"

class Tile : public sfge::CollidableNode
{
    const float DEFAULT_FRICTION = 0.15f;
    const float ICE_FRICTION = 0.04f;

    public:
        Tile(const sf::Sprite& sprite, std::vector<std::string> properties);
        virtual ~Tile();

        void onDraw();
        bool hasProperty(const std::string& name);
        void removeProperty(const std::string& name);
        bool hasProperties();
        float getFriction();

    protected:
        sf::Sprite sprite;
        std::vector<std::string> properties;
        float friction;
};

#endif // TILE_H
