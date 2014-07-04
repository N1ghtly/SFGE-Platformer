#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H
#include <SFGE/Core/CollidableNode.h>
#include <SFGE/Core/ResourceManager.h>
#include "Constants.h"


class MovingPlatform : public sfge::CollidableNode
{
    public:
        MovingPlatform(int x, int y, int dx, int dy, sf::Time duration);
        virtual ~MovingPlatform();

        void onUpdate(sf::Time frametime);
        void onDraw();
        sf::FloatRect getRect();
        sf::Vector2f getMovementVector();
        sf::Vector2f calculateMovementVector(sf::Time timestep);

    private:
        int originalx;
        int originaly;
        int goalx;
        int goaly;
        sf::Vector2f floatPosition;
        sf::Vector2f movementVector;
        sf::Time duration;
        sf::Time passedTime;
        sf::Sprite sprite;
};

#endif // MOVINGPLATFORM_H
