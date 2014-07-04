#ifndef FALLINGTILE_H
#define FALLINGTILE_H
#include <SFGE/Core/CollidableNode.h>
#include <SFGE/Core/ResourceManager.h>
#include "Constants.h"

class FallingTile : public sfge::CollidableNode
{
    const sf::Time falltime = sf::seconds(0.25);
    const float TERMINAL_VELOCITY = 4;

    public:
        FallingTile(const sf::Sprite& sprite);
        virtual ~FallingTile();

        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);
        void move(float x, float y);
        void onUpdate(sf::Time time);
        void onDraw();

    private:
        sf::Time accumulator;
        sf::Sprite sprite;
        float vely;
        bool counting;
        bool falling;

};

#endif // FALLINGTILE_H
