#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <SFGE/Gui/LabelButton.h>
#include <SFGE/Core/State.h>
#include "GameState.h"
#include "ControlState.h"
#include "ElementCreator.h"
#include "SFGE/Core/SpriteNode.h"
#include "LevelState.h"

class MenuState : public sfge::State
{
    public:
        MenuState();
        virtual ~MenuState();

        void resume();

    protected:
        void onHandle(const sf::Event& event);

    private:

        void onPlay();
        void onControls();
        void onQuit();

        sfge::LabelButton* makeButton(const std::string& label, int x, int y);
};

#endif // MENUSTATE_H
