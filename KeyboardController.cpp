#include "KeyboardController.h"
#include <iostream>

KeyboardController::KeyboardController(Player* player) : PlayerController(player)
{
    readKeys();
}

KeyboardController::~KeyboardController()
{
    //dtor
}

void KeyboardController::update(sf::Time frametime)
{
    if(sf::Keyboard::isKeyPressed(keys["up"]))
    {
        player->climb(frametime);
    }

    if(sf::Keyboard::isKeyPressed(keys["right"]))
    {
        player->goRight(frametime);
    }

    else if(sf::Keyboard::isKeyPressed(keys["left"]))
    {
        player->goLeft(frametime);
    }
    else
    {
        player->idle();
    }
}

void KeyboardController::handle(const sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == keys["jump"])
        {
            player->jump();
            player->holdingJump();
        }
    }

    else if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == keys["jump"])
        {
            player->releaseJump();
        }
    }
}

void KeyboardController::readKeys()
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");

    pugi::xml_node bindings = doc.child("bindings");
    for(pugi::xml_node key = bindings.child("key"); key; key = key.next_sibling("key"))
    {
        keys[key.attribute("name").as_string()] = static_cast<sf::Keyboard::Key>(key.attribute("code").as_int());
    }
}
