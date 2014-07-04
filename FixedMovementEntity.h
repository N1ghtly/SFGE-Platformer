#ifndef FIXEDMOVEMENTENTITY_H
#define FIXEDMOVEMENTENTITY_H
#include "Entity.h"
#include "SFGE/Core/Animation.h"
#include "pugixml.hpp"
#include "SFGE/Core/CollisionDetector.h"
#include "SFGE/Core/ResourceManager.h"
#include "Constants.h"

class FixedMovementEntity : public Entity
{
    const float TERMINAL_VELOCITY = 5;

    public:
        FixedMovementEntity(std::string name, int x, int y);
        virtual ~FixedMovementEntity();

        virtual void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);

        void onDead();

    protected:
        void changeDirection();
        void onUpdate(sf::Time frametime);
        void parseXmlFile(std::string path);
        void initAnimations(pugi::xml_node entity);
        sfge::Animation parseAnimation(pugi::xml_node animation);
        void initSprite(std::string path);
        void initShape(pugi::xml_node entity);
        bool dead;

    private:


};

#endif // FIXEDMOVEMENTENTITY_H
