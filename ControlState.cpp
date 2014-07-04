#include "ControlState.h"

ControlState::ControlState()
{
    sfge::Label* titleLabel = ElementCreator::makeTitle("Choose Input Method", 400, 100);
    keyboardButton = ElementCreator::makeButton("keyboard", 240, 390);
    keyboardButton->setOnClickCallback(&ControlState::onKeyboard, this);
    joystickButton = ElementCreator::makeButton("joystick", 560, 390);
    joystickButton->setOnClickCallback(&ControlState::onJoystick, this);

    sfge::LabelButton* backButton = ElementCreator::makeButton("back", 400, 570, true, 30);
    backButton->setOnClickCallback(&ControlState::back, this);

    addNode(titleLabel);
    addNode(keyboardButton);
    addNode(joystickButton);
    addNode(backButton);

    sfge::SpriteNode* background = new sfge::SpriteNode("background", "consolebackground.png");
    background->setZ(-1);
    addNode(background);

    inputType = readInputMethod();
    keyboardButton->setColor(notPickedColor);
    joystickButton->setColor(notPickedColor);
    if(inputType == "keyboard")
        keyboardButton->setColor(pickedColor);
    else if(inputType == "joystick")
        joystickButton->setColor(pickedColor);
}

ControlState::~ControlState()
{
    //dtor
}

void ControlState::onHandle(const sf::Event& event)
{
    if(event.type == sf::Event::Closed)
        window->close();
}

void ControlState::onKeyboard()
{
    inputType = "keyboard";
    setInputMethod(inputType);
    keyboardButton->setColor(pickedColor);
    joystickButton->setColor(notPickedColor);
}

void ControlState::onJoystick()
{
    inputType = "joystick";
    setInputMethod(inputType);
    joystickButton->setColor(pickedColor);
    keyboardButton->setColor(notPickedColor);
}

void ControlState::onKeyboardConfig()
{
    director->pushState(new KeyboardControlState());
}

void ControlState::onJoystickConfig()
{
    director->pushState(new JoystickControlState());
}

void ControlState::resume()
{
    window->setView(window->getDefaultView());
}

void ControlState::back()
{
    director->popState();
}

std::string ControlState::readInputMethod()
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");

    pugi::xml_node inputType = bindings.child("input_type");
    pugi::xml_attribute nameAttr = inputType.attribute("name");

    return nameAttr.as_string();
}

void ControlState::setInputMethod(std::string input)
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");

    pugi::xml_node inputType = bindings.child("input_type");
    pugi::xml_attribute nameAttr = inputType.attribute("name");
    nameAttr.set_value(input.c_str());

    doc.save_file("Data/KeyBindings.xml");
}
