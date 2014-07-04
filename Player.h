#ifndef PLAYER_H
#define PLAYER_H
#include <SFGE/Core/AnimatedSprite.h>
#include <SFGE/Core/CollidableNode.h>
#include <SFGE/Core/CollisionDetector.h>
#include <SFGE/Core/ResourceManager.h>
#include "Tile.h"
#include "Level.h"
#include "Constants.h"
#include "util.h"

class Player : public Entity
{
    const float JUMP_POWER = -6.5f;
    const int   JUMP_HOLD_TIME = 125;
    const float KILL_JUMP_POWER = -3.5f;
    const float TRAMPOLINE_JUMP_POWER  = -10.f;
    const float RUN_SPEED = 2.5f;
    const float TERMINAL_VELOCITY = 6.5f;
    const float AIR_FRICTION = 0.075f;

    friend class GameState;

    public:
        Player();
        virtual ~Player();

        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);

        void setLevel(Level* level);
        sf::Vector2f getMovedVec();

        //interaction
        void jump();
        void holdingJump();
        void releaseJump();
        void goLeft(sf::Time frametime);
        void goRight(sf::Time frametime);
        void climb(sf::Time frametime);
        void idle();

    protected:
        void onDraw();
        void onUpdate(sf::Time frametime);

    private:
        Level* level;
        float FRICTION;
        sf::Vector2f movedvec;
        bool inAir;
        bool onLadder;
        bool climbing;
        bool isHoldingJump;
        DIRECTION dir;
        sf::Time timeSinceJump;

        void initAnimations();
        void updateJump(sf::Time frametime);
        void updateCollisions();
        void onSpecialTileCollision(Tile* tile, sf::Vector2f mtv);
        void onObjectCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);
        void onNormalTileCollision(sf::Vector2f mtv);
        void buildCollisionShape();
};

#endif // PLAYER_H
