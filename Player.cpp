#include "Player.h"
#include <iostream>

Player::Player() : Entity("player"), inAir(true), dir(LEFT), climbing(false), onLadder(false), level(NULL), timeSinceJump(sf::seconds(2)), FRICTION(0), isHoldingJump(false)
{
    initAnimations();
    buildCollisionShape();
}

Player::~Player()
{
    cd = NULL;
}

void Player::setLevel(Level* lvl)
{
    level = lvl;
    setPosition(level->getPlayerStartingPosition().x, level->getPlayerStartingPosition().y);
}

void Player::onDraw()
{
    sf::FloatRect rect = sprite.getGlobalBounds();
    if(rect.left > WIDTH/2 && rect.left + WIDTH/2 < level->widthInTiles * 32)
    {
        sf::View view = window->getView();
        view.setCenter(static_cast<int>(rect.left), view.getCenter().y);
        window->setView(view);
    }

    if(rect.top + 50 <  (level->heightInTiles * 32) - HEIGHT/2 && HEIGHT/2 < rect.top)
    {
        sf::View view = window->getView();
        view.setCenter(view.getCenter().x, static_cast<int>(rect.top + 50));
        window->setView(view);
    }
    window->draw(sprite);
}

sf::Vector2f Player::getMovedVec()
{
    return movedvec;
}

void Player::onSpecialTileCollision(Tile* tile, sf::Vector2f mtv)
{
    if(tile->hasProperty("leftslope") || tile->hasProperty("rightslope"))
    {
        move(0, mtv.y);
        vely = 3.0;
        inAir = false;
    }
    if(tile->hasProperty("platform"))
    {
        if(movedvec.y > 0 && shape.getBounds().top + shape.getBounds().height <= tile->getShape().getBounds().top  + TERMINAL_VELOCITY) //we we're going down
        {
            move(mtv);
            vely = 0;
            inAir = false;
        }
    }
    if(tile->hasProperty("ladder"))
    {
        onLadder = true;
    }
}

void Player::onObjectCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    std::string name = obj->getName();
    if(name == "MovingPlatform")
    {
        if(movedvec.y > 0 && shape.getBounds().top + shape.getBounds().height <= obj->getShape().getBounds().top  + TERMINAL_VELOCITY) // we're going down
        {
            MovingPlatform* platform = static_cast<MovingPlatform*>(obj);
            move(mtv.x, mtv.y);
            inAir = false;
            vely = 3; //make sure we touch the platform again next frame
            move(platform->getMovementVector().x, 0);
        }
    }
    else if(name == "FallingTile")
    {
        if(movedvec.x == 0 && movedvec.y > 0)
        {
            inAir = false;
            vely = 0;
        }

        move(mtv);
    }
    else if(name == "trampoline")
    {
        if(movedvec.y > 1)
        {
            inAir = true;
            vely = TRAMPOLINE_JUMP_POWER;
        }
    }
    else if(name == "skeleton" || name == "bat")
    {
        if(movedvec.y > 1 && shape.getBounds().top + shape.getBounds().height < obj->getShape().getBounds().top + movedvec.y)
        {
            FixedMovementEntity* entity = static_cast<FixedMovementEntity*>(obj);
            entity->onDead();
            vely = KILL_JUMP_POWER;
        }
    }
    else if(name == "Cannon")
    {
        move(mtv);
    }
    else if(name == "Bullet")
    {
        if(movedvec.y > 1 && shape.getBounds().top + shape.getBounds().height < obj->getShape().getBounds().top + movedvec.y)
            vely = KILL_JUMP_POWER;
    }
}

void Player::onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv)
{
    std::string name = obj->getName();
    if(name == "Tile")
    {
        Tile* tile = static_cast<Tile*>(obj);
        FRICTION = tile->getFriction();
        if(tile->hasProperties())
        {
            onSpecialTileCollision(tile, mtv);
        }
        else
        {
            onNormalTileCollision(mtv);
        }
    }
    else
    {
        onObjectCollision(obj, mtv);
    }



}

void Player::onNormalTileCollision(sf::Vector2f mtv)
{
    move(mtv);
    //if we were going down, we hit the ground!
    if(movedvec.y > 0)
    {
        inAir = false;
        vely = 0;
    }
    else if(movedvec.y < 0) //we were jumping
    {
        vely = 0;
    }
    else //going left or right
    {
        if(dir == DIRECTION::RIGHT && velx > 0)
            velx -= FRICTION;
        else if(dir == DIRECTION::LEFT && velx < 0)
            velx += FRICTION;
    }
}

void Player::jump()
{
    if(!inAir)
    {
        vely = JUMP_POWER;
        inAir = true;
        FRICTION = AIR_FRICTION;
        timeSinceJump = sf::Time::Zero;
    }
}

void Player::holdingJump()
{
    isHoldingJump = true;
}

void Player::releaseJump()
{
    isHoldingJump = false;
}

void Player::updateJump(sf::Time frametime)
{
    timeSinceJump += frametime;
    if(timeSinceJump < sf::milliseconds(JUMP_HOLD_TIME) && !isHoldingJump)
    {
        vely += acceleration*2.7;
    }
}

void Player::climb(sf::Time frametime)
{
    if(onLadder)
    {
        if(sprite.getCurrentAnimationName() != "climbing")
            sprite.playAnimation("climbing", true);
        vely = -2.f;
        inAir = false;
        climbing = true;
    }
}

void Player::goLeft(sf::Time frametime)
{
    if(sprite.getCurrentAnimationName() != "leftrunning" && !inAir)
        sprite.playAnimation("leftrunning", true);
    else if(sprite.getCurrentAnimationName() != "leftjumping" && inAir && !climbing)
        sprite.playAnimation("leftjumping", true);
    if(velx > -RUN_SPEED)
        velx -= FRICTION;
    dir = LEFT;
}

void Player::goRight(sf::Time frametime)
{
    if(sprite.getCurrentAnimationName() != "rightrunning" && !inAir)
        sprite.playAnimation("rightrunning", true);
    else if(sprite.getCurrentAnimationName() != "rightjumping" && inAir && !climbing)
        sprite.playAnimation("rightjumping", true);
    if(velx < RUN_SPEED)
        velx += FRICTION;
    dir = RIGHT;
}

void Player::idle()
{
    if(dir == RIGHT && !climbing)
        sprite.playAnimation("rightidle", true);
    else if(!climbing)
        sprite.playAnimation("leftidle", true);
    velx -= sign(velx)*FRICTION;
    if(std::abs(velx) < FRICTION*2)
        velx = 0;
}

void Player::updateCollisions()
{
    movedvec.x = 0;
    movedvec.y = vely;
    move(0, movedvec.y);
    cd->detectCollisionsWithObject(this);

    movedvec.y = 0;
    movedvec.x = velx;
    move(movedvec.x, 0);
    cd->detectCollisionsWithObject(this);
}

void Player::onUpdate(sf::Time frametime)
{
    climbing = false;

    updateJump(frametime);

    //reset ladder var again, if we're on ladder it will set it to true again on collision
    onLadder = false;

    if(vely > 1)
        inAir = true;

    if(vely <= TERMINAL_VELOCITY)
        vely += acceleration;
    else
        vely = TERMINAL_VELOCITY;

    updateCollisions();

    sprite.update(frametime);
}

void Player::initAnimations()
{
    sprite.setTexture(rm->getTexture("character.png"));
    sprite.setTextureRect(sf::IntRect(0, 0, 46, 32));

    sfge::Animation rightrunninganim;
    rightrunninganim.setDuration(sf::seconds(0.6));
    for(int i = 0; i < 6*33; i+= 33)
        rightrunninganim.addFrame(sf::IntRect(i, 46, 32, 46));
    sfge::Animation leftrunninganim;
    leftrunninganim.setDuration(sf::seconds(0.6));
    for(int i = 0; i < 6*33; i+= 33)
        leftrunninganim.addFrame(sf::IntRect(i, 0, 32, 46));
    sfge::Animation leftjumpinganim;
    leftjumpinganim.setDuration(sf::seconds(5.0));
    leftjumpinganim.addFrame(sf::IntRect(6*33, 0, 32, 46));
    sfge::Animation leftidleanim;
    leftidleanim.setDuration(sf::seconds(5.0));
    leftidleanim.addFrame(sf::IntRect(7*33, 0, 32, 46));
    sfge::Animation rightjumpinganim;
    rightjumpinganim.setDuration(sf::seconds(5.0));
    rightjumpinganim.addFrame(sf::IntRect(6*33, 46, 32, 46));
    sfge::Animation rightidleanim;
    rightidleanim.setDuration(sf::seconds(5.0));
    rightidleanim.addFrame(sf::IntRect(7*33, 46, 32, 46));
    sfge::Animation climbinganim;
    climbinganim.setDuration(sf::seconds(0.5));
    for(int i = 0; i < 6*33; i+=33)
        climbinganim.addFrame(sf::IntRect(i, 92, 32, 46));

    sprite.addAnimation("rightrunning", rightrunninganim);
    sprite.addAnimation("rightidle", rightidleanim);
    sprite.addAnimation("rightjumping", rightjumpinganim);
    sprite.addAnimation("leftidle", leftidleanim);
    sprite.addAnimation("leftrunning", leftrunninganim);
    sprite.addAnimation("leftjumping", leftjumpinganim);
    sprite.addAnimation("climbing", climbinganim);
}

void Player::buildCollisionShape()
{
    shape.setPosition(0, 0);
    shape.addPoint(1, 0);
    shape.addPoint(31, 0);
    shape.addPoint(31, 46);
    shape.addPoint(1, 46);
}
