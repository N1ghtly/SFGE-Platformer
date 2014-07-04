#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "Player.h"

class PlayerController
{
    public:
        PlayerController(Player* player);
        virtual ~PlayerController();

        virtual void update(sf::Time frametime) = 0;
        virtual void handle(const sf::Event& event) = 0;

    protected:
        Player* player;
};

#endif // PLAYERCONTROLLER_H
