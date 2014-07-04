#include "Coin.h"

Coin::Coin(int x, int y) : taken(false), CollidableNode("coin", false)
{
    sprite.setTexture(rm->getTexture("coin.png"));
    sprite.setPosition(x-10, y-5);

    initAnimation();

    shape.setPosition(x-10, y-5);
    shape.buildFromRect(sf::FloatRect(0, 0, 14, 14));

    sound.setBuffer(rm->getSoundBuffer("pickup3.wav"));
    sound.setVolume(60);
}

Coin::~Coin()
{
    //dtor
}

void Coin::onDraw()
{
    if(!taken)
        window->draw(sprite);
}

void Coin::onUpdate(sf::Time frametime)
{
    sprite.update(frametime);
}

void Coin::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    if(obj->getName() == "player")
    {
        if(!taken)
            sound.play();
        taken = true;
    }
}

void Coin::initAnimation()
{
    sfge::Animation rotate;
    rotate.setDuration(sf::seconds(0.5));
    for(int i = 0; i < 4; i++)
        rotate.addFrame(sf::IntRect(i*14, 0, 14, 14));
    sprite.addAnimation("rotate", rotate);
    sprite.playAnimation("rotate", true);
}
