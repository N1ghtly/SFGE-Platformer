#include "Bullet.h"
#include <SFGE/Core/CollisionDetector.h>
#include <iostream>

Bullet::Bullet(int x, int y, DIRECTION dir)  : sfge::CollidableNode("Bullet"), accumulator(sf::Time::Zero), dir(dir), dead(false)
{
    sprite.setPosition(x, y);
    sprite.setTexture(rm->getTexture("bullet.png"));
    shape.setPosition(x, y);
    shape.buildFromRect(sprite.getLocalBounds());
}

Bullet::~Bullet()
{

}

void Bullet::onDraw()
{
    if(!dead)
        window->draw(sprite);
}

void Bullet::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    if(obj->getName() != "Cannon")
    {
        dead = true;
        this->markForRemoval();
    }
}

bool Bullet::isDead()
{
    return dead;
}

void Bullet::onUpdate(sf::Time dt)
{
    if(!dead)
    {
        accumulator += dt;

        if(dir == DIRECTION::RIGHT)
        {
            sprite.move(BULLET_SPEED, 0);
            shape.move(BULLET_SPEED, 0);
        }
        else
        {
            sprite.move(-BULLET_SPEED, 0);
            shape.move(-BULLET_SPEED, 0);
        }
    }
}
