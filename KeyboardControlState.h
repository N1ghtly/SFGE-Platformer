#ifndef KEYBOARDCONTROLSTATE_H
#define KEYBOARDCONTROLSTATE_H
#include <SFGE/Core/State.h>
#include "ElementCreator.h"


class KeyboardControlState : public sfge::State
{
    public:
        KeyboardControlState();
        virtual ~KeyboardControlState();


        void resume();

    protected:
        void onHandle(const sf::Event& event);

    private:

        void loadControls();
        void back();

        sf::Keyboard::Key right;
        sf::Keyboard::Key left;
        sf::Keyboard::Key up;
        sf::Keyboard::Key jump;
};

#endif // KEYBOARDCONTROLSTATE_H
