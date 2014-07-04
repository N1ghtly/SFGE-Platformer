#include "MenuState.h"
#include <iostream>

MenuState::MenuState()
{
    sfge::LabelButton* playButton = ElementCreator::makeButton("Play", 670, 150);
    playButton->setOnClickCallback(&MenuState::onPlay, this);

    sfge::LabelButton* controlsButton = ElementCreator::makeButton("Controls", 670, 250);
    controlsButton->setOnClickCallback(&MenuState::onControls, this);

    sfge::LabelButton* quitButton = ElementCreator::makeButton("Quit", 670, 350);
    quitButton->setOnClickCallback(&MenuState::onQuit, this);

    sfge::SpriteNode* background = new sfge::SpriteNode("background", "backgroundmenu.png");
    background->setZ(-1);

    addNode(background);
    addNode(playButton);
    addNode(controlsButton);
    addNode(quitButton);
}

MenuState::~MenuState()
{
    //dtor
}

void MenuState::onHandle(const sf::Event& event)
{
    //if(event == sf::Event::Closed)
      //  director->popState();
}

void MenuState::resume()
{
    window->setView(window->getDefaultView());
}

void MenuState::onPlay()
{
    director->pushState(new LevelState());
}

void MenuState::onControls()
{
    director->pushState(new ControlState());
}

void MenuState::onQuit()
{
    director->popState();
}
