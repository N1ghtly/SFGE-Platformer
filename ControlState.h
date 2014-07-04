#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H
#include <SFGE/Gui/LabelButton.h>
#include <SFGE/Core/SpriteNode.h>
#include <SFGE/Core/State.h>
#include "ElementCreator.h"
#include "KeyboardControlState.h"
#include "JoystickControlState.h"

static const sf::Color pickedColor = sf::Color(0, 0, 0);
static const sf::Color notPickedColor = sf::Color(50, 50, 50);

class ControlState : public sfge::State
{

    public:
        ControlState();
        virtual ~ControlState();

        void onHandle(const sf::Event& event);
        void update();
        void draw();

        void resume();

    private:
        std::string inputType;

        sfge::LabelButton* keyboardButton;
        sfge::LabelButton* joystickButton;

        void back();

        void onKeyboard();
        void onKeyboardConfig();
        void onJoystick();
        void onJoystickConfig();

        void setInputMethod(std::string input);
        std::string readInputMethod();


};

#endif // CONTROLSTATE_H
