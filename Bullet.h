#ifndef BULLET_H
#define BULLET_H
#include <SFGE/Core/ResourceManager.h>
#include <SFGE/Core/CollidableNode.h>
#include "Constants.h"

const float BULLET_SPEED = 2;

class Bullet : public sfge::CollidableNode
{
    friend class Cannon;

    public:
        Bullet(int x, int y, DIRECTION dir);
        virtual ~Bullet();

        void onDraw();
        void onUpdate(sf::Time dt);
        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);

        bool isDead();

    private:
        sf::Sprite sprite;
        sf::Time accumulator;
        DIRECTION dir;
        bool dead;
};

#endif // BULLET_H
