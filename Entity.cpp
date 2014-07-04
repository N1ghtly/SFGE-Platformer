#include "Entity.h"


Entity::Entity(const std::string& name) : sfge::CollidableNode(name), velx(0), vely(0)
{
    //ctor
}

Entity::~Entity()
{
    //dtor
}

void Entity::onDraw()
{
    window->draw(sprite);
}

void Entity::move(float x, float y)
{
    shape.move(x, y);
    sprite.move(x, y);
}
void Entity::move(sf::Vector2f vec)
{
    move(vec.x, vec.y);
}
void Entity::setPosition(float x, float y)
{
    shape.setPosition(x, y);
    sprite.setPosition(x, y);
}
void Entity::setPosition(sf::Vector2f pos)
{
    setPosition(pos.x, pos.y);
}
