#include "JoystickController.h"

JoystickController::JoystickController(Player* player) : PlayerController(player)
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");

    pugi::xml_node button = bindings.child("button");
    jumpButton = button.attribute("code").as_int();

}

JoystickController::~JoystickController()
{
    //dtor
}

void JoystickController::update(sf::Time frametime)
{
    if(sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 40)
    {
        player->climb(frametime);
    }

    if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 40)
    {
        player->goRight(frametime);
    }

    else if(sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -40)
    {
        player->goLeft(frametime);
    }
    else
    {
        player->idle();
    }
}

void JoystickController::handle(const sf::Event& event)
{
    if(event.type == sf::Event::JoystickButtonPressed)
    {
        if(event.joystickButton.button == jumpButton)//A button
        {
            player->jump();
            player->holdingJump();
        }
    }

    else if(event.type == sf::Event::JoystickButtonReleased)
    {
        if(event.joystickButton.button == jumpButton)
        {
            player->releaseJump();
        }
    }
}
