#ifndef JOYSTICKCONTROLLER_H
#define JOYSTICKCONTROLLER_H
#include "pugixml.hpp"
#include "PlayerController.h"


class JoystickController : public PlayerController
{
    public:
        JoystickController(Player* player);
        virtual ~JoystickController();

        virtual void handle(const sf::Event& event);
        virtual void update(sf::Time frametime);

    private:
        int jumpButton;
};

#endif // JOYSTICKCONTROLLER_H
