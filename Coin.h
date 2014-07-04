#ifndef COIN_H
#define COIN_H
#include <SFGE/Core/AnimatedSprite.h>
#include <SFGE/Core/CollidableNode.h>
#include <SFGE/Core/ResourceManager.h>


class Coin : public sfge::CollidableNode
{
    public:
        Coin(int x, int y);
        virtual ~Coin();

        void onDraw();
        void onUpdate(sf::Time frametime);
        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);

    private:
        sfge::AnimatedSprite sprite;
        sf::Sound sound;
        bool taken;

        void initAnimation();
};

#endif // COIN_H
