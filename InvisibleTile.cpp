#include "InvisibleTile.h"

InvisibleTile::InvisibleTile(const sf::Sprite& sprite, std::vector<std::string> properties) : Tile(sprite, properties), visible(false)
{
    //ctor
}

void InvisibleTile::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    if(obj->getName() == "player")
    {
        visible = true;
    }
}

void InvisibleTile::onDraw()
{
    if(visible)
        window->draw(sprite);
}


InvisibleTile::~InvisibleTile()
{
    //dtor
}
