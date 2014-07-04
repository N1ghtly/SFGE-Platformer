#include "FallingTile.h"

FallingTile::FallingTile(const sf::Sprite& sprite) : sfge::CollidableNode("FallingTile", true), vely(0), counting(false), falling(false), sprite(sprite)
{
    shape.setPosition(sprite.getPosition());
    shape.buildFromRect(sprite.getLocalBounds());
}

FallingTile::~FallingTile()
{
    //dtor
}

void FallingTile::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    if(obj->getName() == "player")
    {
        counting = true;
    }
    else if(obj->getName() == "FallingTile")
    {
        //we fall on top of other falling tile
        if(shape.getBounds().top + shape.getBounds().height < obj->getShape().getBounds().top + TERMINAL_VELOCITY + 6)
        {
            vely = 0;
            move(mtv.x, mtv.y);
        }
        //other falling tile fell on top of us
        else if(obj->getShape().getBounds().top + obj->getShape().getBounds().height < shape.getBounds().top + TERMINAL_VELOCITY + 3)
            falling = true;
    }
    else if(obj->getName() == "Tile")
    {
        move(0, mtv.y);
        if(mtv.y != 0)
            vely = 0;
    }
}

void FallingTile::move(float x, float y)
{
    shape.move(x, y);
    sprite.move(x, y);
}

void FallingTile::onUpdate(sf::Time time)
{
    if(falling)
    {
        if(vely < TERMINAL_VELOCITY)
            vely += acceleration;
        move(0, vely);
    }
    else if(counting)
    {
        accumulator += time;
        if(accumulator > falltime)
        {
            falling = true;
        }
        else if(accumulator > sf::seconds(5))
        {
            counting = false;
            falling = false;
            vely = 0;
        }
    }
}

void FallingTile::onDraw()
{
    window->draw(sprite);
}
