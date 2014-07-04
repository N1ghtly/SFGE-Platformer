#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H
#include <SFGE/Core/AnimatedSprite.h>
#include <SFGE/Core/CollidableNode.h>
#include <SFGE/Core/ResourceManager.h>


class Trampoline : public sfge::CollidableNode
{
    public:
        Trampoline(int x, int y);
        virtual ~Trampoline();

        void onDraw();
        void onUpdate(sf::Time frametime);
        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);

    private:
        sfge::AnimatedSprite sprite;
};

#endif // TRAMPOLINE_H
