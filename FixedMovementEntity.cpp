#include "FixedMovementEntity.h"
#include <iostream>

FixedMovementEntity::FixedMovementEntity(std::string path, int x, int y) : Entity("FixedMovementEntity"), dead(false)
{
    setPosition(x, y);
    parseXmlFile(path);
    sprite.playAnimation("right", true);
}

FixedMovementEntity::~FixedMovementEntity()
{
    //dtor
}

void FixedMovementEntity::parseXmlFile(std::string path)
{
    pugi::xml_document doc;
    doc.load_file(("Data/Monsters/" + path).c_str());

    pugi::xml_node entity = doc.child("entity");

    //read attributes
    velx = entity.attribute("speed").as_float();
    std::string spriteFile = entity.attribute("sprite").as_string();
    std::string name = entity.attribute("name").as_string();

    this->setName(name);

    initShape(entity);
    initAnimations(entity);
    initSprite(spriteFile);
}

void FixedMovementEntity::onDead()
{
    dead = true;
    this->markForRemoval();
    vely = -1;
}

void FixedMovementEntity::changeDirection()
{
    velx = -velx;
    if(sprite.getCurrentAnimationName() == "left")
        sprite.playAnimation("right", true);
    else
        sprite.playAnimation("left", true);
}

void FixedMovementEntity::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    if(obj->getName() == "Tile")
    {
        vely = 0;
        move(mtv);
        if(obj->getShape().getCenter().y < sprite.getGlobalBounds().top + sprite.getGlobalBounds().height)
            changeDirection();
    }
}

void FixedMovementEntity::onUpdate(sf::Time frametime)
{
    if(vely < TERMINAL_VELOCITY)
        vely += acceleration;

    if(!dead)
    {
        if(sprite.isAnimationPlaying())
            sprite.update(frametime);

        move(velx, vely);

        sf::Vector2f vacuumpoint;
        vacuumpoint.x = shape.getBounds().left + shape.getBounds().width/2 + velx*20;
        vacuumpoint.y = shape.getBounds().top + shape.getBounds().height + 5;

        if(!cd->detectCollisionsWithPoint(vacuumpoint))
            changeDirection();
    }

    else
        move(0, vely);
}

void FixedMovementEntity::initSprite(std::string path)
{
    sprite.setTexture(rm->getTexture(path));
    sprite.setTextureRect(sf::IntRect(0, 0, shape.getBounds().width, shape.getBounds().height));
}

void  FixedMovementEntity::initAnimations(pugi::xml_node entity)
{
    sprite.addAnimation("right", parseAnimation(entity.child("rightanimation")));
    sprite.addAnimation("left", parseAnimation(entity.child("leftanimation")));
}

sfge::Animation FixedMovementEntity::parseAnimation(pugi::xml_node animation)
{
    sfge::Animation anim;
    anim.setDuration(sf::seconds(animation.attribute("duration").as_float()));

    for(pugi::xml_node frame = animation.child("frame"); frame; frame = frame.next_sibling("frame"))
    {
        anim.addFrame(sf::IntRect(
                      frame.attribute("left").as_int(),
                      frame.attribute("top").as_int(),
                      int(shape.getBounds().width),
                      int(shape.getBounds().height)));
    }

    return anim;
}

void FixedMovementEntity::initShape(pugi::xml_node entity)
{
    pugi::xml_node size = entity.child("size");
    int width = size.attribute("width").as_int();
    int height = size.attribute("height").as_int();
    shape.buildFromRect(sf::FloatRect(0, 0, width, height));
}


