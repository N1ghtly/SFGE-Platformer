#include "JoystickControlState.h"
#include "util.h"

JoystickControlState::JoystickControlState() : jumpActivated(false)
{
    loadControls();

    sfge::Label* title = ElementCreator::makeTitle("Joystick Controls", 400, 100);
    sfge::Label* jumpLabel = ElementCreator::makeLabel("Jump", 100, 350);
    jumpButton = ElementCreator::makeButton(to_string(jumpCode), 300, 350, true, 35);
    jumpButton->setOnClickCallback(&JoystickControlState::activateJumpButton, this);
    sfge::LabelButton* backButton = ElementCreator::makeButton("Back", 75, 560, true, 30);
    backButton->setOnClickCallback(&JoystickControlState::back, this);

    addNode(title);
    addNode(jumpLabel);
    addNode(jumpButton);
    addNode(backButton);
}

JoystickControlState::~JoystickControlState()
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");

    pugi::xml_node button = bindings.child("button");
    pugi::xml_attribute jumpAttr = button.attribute("code");
    jumpAttr.set_value(jumpCode);

    doc.save_file("Data/KeyBindings.xml");
}

void JoystickControlState::onHandle(const sf::Event& event)
{
    if(event.type == sf::Event::Closed)
        window->close();
    else if(event.type == sf::Event::JoystickButtonPressed && jumpActivated)
    {
        jumpActivated = false;
        jumpButton->setText(to_string(event.joystickButton.button));
        jumpCode = event.joystickButton.button;
    }
}

void JoystickControlState::activateJumpButton()
{
    jumpActivated = true;
}

void JoystickControlState::back()
{
    director->popState();
}

void JoystickControlState::loadControls()
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");

    pugi::xml_node button = bindings.child("button");
    jumpCode = button.attribute("code").as_int();
}

void JoystickControlState::resume()
{
    window->setView(window->getDefaultView());
}
