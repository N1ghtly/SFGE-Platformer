#ifndef ENTITY_H
#define ENTITY_H
#include <SFGE/Core/AnimatedSprite.h>
#include <SFGE/Core/CollidableNode.h>

class Entity : public sfge::CollidableNode
{
    public:
        Entity(const std::string& name);
        virtual ~Entity();

        virtual void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv) = 0;

        virtual void onDraw();
        void move(float x, float y);
        void move(sf::Vector2f vec);
        void setPosition(float x, float y);
        void setPosition(sf::Vector2f pos);


    protected:
        sfge::AnimatedSprite sprite;
        float velx;
        float vely;
};

#endif // ENTITY_H
