#ifndef JOYSTICKCONTROLSTATE_H
#define JOYSTICKCONTROLSTATE_H
#include <SFGE/Core/State.h>
#include "ElementCreator.h"
#include "pugixml.hpp"
#include <string>

class JoystickControlState : public sfge::State
{
    public:
        JoystickControlState();
        virtual ~JoystickControlState();

        void resume();

    protected:
        void onHandle(const sf::Event& event);

    private:

        void loadControls();
        void activateJumpButton();
        void back();

        int jumpCode;
        sfge::LabelButton* jumpButton;
        bool jumpActivated;
};

#endif // KEYBOARDCONTROLSTATE_H
