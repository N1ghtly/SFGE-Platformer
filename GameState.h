#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Level.h"
#include "Player.h"
#include "pugixml.hpp"
#include <SFGE/Core/State.h>
#include <SFGE/Core/SpriteNode.h>
#include <SFGE/Core/CollisionDetector.h>
#include "KeyboardController.h"
#include "JoystickController.h"

const std::map<int, std::string> songs( {{0, "background2.ogg"}, {1, "background3.ogg"}, {2, "background.ogg"}, {3, "background4.ogg"}} );

class GameState : public sfge::State
{
    public:
        GameState(std::string file);
        virtual ~GameState();

        void pause();
        void resume();

    protected:
        void onHandle(const sf::Event& event);
        void onUpdate(sf::Time delta);
        void onWindowSet();

    private:
        Level* level;
        PlayerController* controller;
        Player* player;
        sfge::SpriteNode* background;

        sfge::CollisionDetector* cd;
        sf::Music backgroundmusic;

        void initBackground();
        void initPlayer();
        void initController();
        std::string getInputType();
};

#endif // GAMESTATE_H
