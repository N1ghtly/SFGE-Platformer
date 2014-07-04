#include "Cannon.h"
#include "Level.h"

Cannon::Cannon(int x, int y, DIRECTION dir) : accumulator(sf::Time::Zero), sfge::CollidableNode("Cannon", false), dir(dir)
{
    if(dir == DIRECTION::LEFT)
    {
        sprite.setTexture(rm->getTexture("leftcannon.png"));
    }
    else
    {
        sprite.setTexture(rm->getTexture("rightcannon.png"));
    }
    shape.setPosition(x, y-7);
    sprite.setPosition(x, y-7);
    shape.buildFromRect(sprite.getLocalBounds());
}

void Cannon::onDraw()
{
    window->draw(sprite);
}

void Cannon::onUpdate(sf::Time dt)
{
    accumulator += dt;
    if(accumulator > sf::seconds(BULLET_INTERVAL))
    {
        //if we have more than 5 bullets in the air, delete the furthest one.
        if(getChildren().size() > 5)
        {
            delete getChildren()[0];
            getChildren().erase(getChildren().begin());
        }

        Bullet* bullet = new Bullet(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top, dir);
        addNode(bullet);
        cd->add(bullet);
        accumulator -= sf::seconds(1.5);
    }
}

Cannon::~Cannon()
{

}
