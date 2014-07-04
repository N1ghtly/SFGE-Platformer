#ifndef LEVELSTATE_H
#define LEVELSTATE_H
#include <SFGE/Core/State.h>
#include <SFGE/Core/SpriteNode.h>
#include "pugixml.hpp"
#include "LevelButton.h"
#include "GameState.h"

class LevelState : public sfge::State
{
    public:
        LevelState();
        virtual ~LevelState();

        void onHandle(const sf::Event& event);

        void resume();

    private:
        void readLevels();
        void readWorld(pugi::xml_node level, int x);
        void loadLevel(std::string file);

};

#endif // LEVELSTATE_H
