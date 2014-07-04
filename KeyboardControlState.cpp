#include "KeyboardControlState.h"

KeyboardControlState::KeyboardControlState()
{
    sfge::Label* leftLabel = ElementCreator::makeLabel("left", 100, 200, false);
    sfge::Label* rightLabel = ElementCreator::makeLabel("right", 100, 275, false);
    sfge::Label* upLabel = ElementCreator::makeLabel("up", 100, 350, false);
    sfge::Label* jumpLabel = ElementCreator::makeLabel("jump", 100, 425, false);

    sfge::LabelButton* backButton = ElementCreator::makeButton("Back", 75, 560, true, 30);
    backButton->setOnClickCallback(&KeyboardControlState::back, this);

    addNode(leftLabel);
    addNode(rightLabel);
    addNode(upLabel);
    addNode(jumpLabel);
    addNode(backButton);
}

KeyboardControlState::~KeyboardControlState()
{
    //dtor
}

void KeyboardControlState::onHandle(const sf::Event& event)
{
    if(event.type == sf::Event::Closed)
        window->close();
}

void KeyboardControlState::back()
{
    director->popState();
}

void KeyboardControlState::resume()
{
    window->setView(window->getDefaultView());
}

