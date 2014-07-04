#include "Trampoline.h"
#include "Player.h"

Trampoline::Trampoline(int x, int y) : sfge::CollidableNode("trampoline", false)
{
    sprite.setPosition(x, y);
    sprite.setTexture(rm->getTexture("tramp.png"));
    sprite.setTextureRect(sf::IntRect(68, 0, 32, 32));

    sfge::Animation jump;
    jump.setDuration(sf::seconds(0.2));
    jump.addFrame(sf::IntRect(68, 0, 32, 32));
    jump.addFrame(sf::IntRect(34, 0, 32, 32));
    jump.addFrame(sf::IntRect(0, 0, 32, 32));
    jump.addFrame(sf::IntRect(68, 0, 32, 32));
    sprite.addAnimation("jump", jump);
    shape.setPosition(x, y);
    shape.buildFromRect(sprite.getLocalBounds());
}

Trampoline::~Trampoline()
{
    //dtor
}

void Trampoline::onDraw()
{
    window->draw(sprite);
}

void Trampoline::onUpdate(sf::Time frametime)
{
    sprite.update(frametime);
}

void Trampoline::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    //if we're jumping on top of it only
    if(obj->getName() == "player")
    {
        Player* player = static_cast<Player*>(obj);
        if(player->getMovedVec().y > 1)
            sprite.playAnimation("jump");
    }
}
