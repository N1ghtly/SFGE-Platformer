#ifndef CANNON_H
#define CANNON_H
#include <SFGE/Core/CollidableNode.h>
#include "Bullet.h"
#include "Constants.h"

const float BULLET_INTERVAL = 1.5;

class Cannon : public sfge::CollidableNode
{
    public:
        Cannon(int x, int y, DIRECTION dir);
        virtual ~Cannon();
        void onDraw();
        void onUpdate(sf::Time dt);

    private:
        sf::Sprite sprite;
        sf::Time accumulator;
        DIRECTION dir;
};

#endif // CANNON_H
