#include "MovingPlatform.h"
#include <SFGE/Core/CollisionDetector.h>

MovingPlatform::MovingPlatform(int x, int y, int dx, int dy, sf::Time duration) : originalx(x), originaly(y), sfge::CollidableNode("MovingPlatform"), goalx(dx), goaly(dy), passedTime(sf::Time::Zero), duration(duration), floatPosition(x, y), movementVector(sf::Vector2f(0, 0))
{
    sprite.setTexture(rm->getTexture("movingplatform.png"));
    sprite.setPosition(x, y);

    shape.setPosition(x, y);
    shape.buildFromRect(sf::FloatRect(0, 0, 96, 32));


}

MovingPlatform::~MovingPlatform()
{
    //dtor
}

void MovingPlatform::onUpdate(sf::Time frametime)
{
    if(movementVector.x == 0 && movementVector.y == 0)
    {
        calculateMovementVector(frametime);
    }

    passedTime += frametime;
    floatPosition += getMovementVector();
    sprite.setPosition(int(floatPosition.x+0.5), int(floatPosition.y+0.5));
    shape.setPosition(int(floatPosition.x+0.5), int(floatPosition.y+0.5));

    if(passedTime > duration)
    {
        passedTime = sf::Time::Zero;
        originalx = sprite.getPosition().x;
        originaly = sprite.getPosition().y;
        goalx = -goalx;
        goaly = -goaly;
        calculateMovementVector(frametime);
    }
}

sf::Vector2f MovingPlatform::getMovementVector()
{
    return movementVector;
}

sf::Vector2f MovingPlatform::calculateMovementVector(sf::Time timestep)
{
    float delta = timestep.asSeconds()/duration.asSeconds();
    movementVector = sf::Vector2f(delta*goalx, delta*goaly);
    return movementVector;
}

void MovingPlatform::onDraw()
{
    window->draw(sprite);
}


