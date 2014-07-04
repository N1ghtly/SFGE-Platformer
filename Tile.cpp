#include "Tile.h"
#include <iostream>

Tile::Tile(const sf::Sprite& sprite, std::vector<std::string> properties) : sprite(sprite), sfge::CollidableNode("Tile", false), properties(properties), friction(DEFAULT_FRICTION)
{
    shape.setPosition(sprite.getPosition());

    if(hasProperty("ice"))
    {
        friction = ICE_FRICTION;
        removeProperty("ice");
    }


    if(hasProperty("rightslope"))
    {
        shape.addPoint(-2, tileHeight);
        shape.addPoint(tileWidth, -1);
        shape.addPoint(tileWidth, tileHeight);
    }

    else if(hasProperty("leftslope"))
    {
        shape.addPoint(0, -1);
        shape.addPoint(tileWidth + 2, tileHeight);
        shape.addPoint(0, tileHeight);
    }

    else
    {
        shape.buildFromRect(sf::FloatRect(0, 0, tileWidth, tileHeight));
    }

}

Tile::~Tile()
{
    //dtor
}

float Tile::getFriction()
{
    return friction;
}

void Tile::onDraw()
{
    window->draw(sprite);
}

void Tile::removeProperty(const std::string& name)
{
    properties.erase(std::find(properties.begin(), properties.end(), name));
}

bool Tile::hasProperties()
{
    return !properties.empty();
}

bool Tile::hasProperty(const std::string& name)
{
    return std::find(properties.begin(), properties.end(), name) != properties.end();
}
