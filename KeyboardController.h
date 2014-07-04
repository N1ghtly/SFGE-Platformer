#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H
#include "pugixml.hpp"
#include "PlayerController.h"
#include <map>

class KeyboardController : public PlayerController
{
    public:
        KeyboardController(Player* player);
        virtual ~KeyboardController();

        virtual void handle(const sf::Event& event);
        virtual void update(sf::Time frametime);

    private:
        std::map<std::string, sf::Keyboard::Key> keys;

        void readKeys();
};

#endif // KEYBOARDCONTROLLER_H
