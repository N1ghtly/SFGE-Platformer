#include "GameState.h"
#include <iostream>

GameState::GameState(std::string file) : cd(new sfge::CollisionDetector(sf::FloatRect(0, 0, 0 ,0 ), 100))
{
    level = new Level(*cd, "Data/Levels/" + file);

    addNode(level);

    initBackground();
    initPlayer();
    initController();

    cd->setMTVOffset(0.05);
}

GameState::~GameState()
{
    std::cout<<"destructing gamestate";
    delete cd;
    delete controller;
}

void GameState::onHandle(const sf::Event& event)
{
    controller->handle(event);
    switch(event.type)
    {
        case sf::Event::Closed:
        {
            window->close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            if(event.key.code == sf::Keyboard::Escape)
                director->popState();
        }
    }
}

void GameState::initBackground()
{
    background = new sfge::SpriteNode("background", "background.png");
    background->setZ(-1);
    background->setOrigin(WIDTH/2, HEIGHT/2);
    addNode(background);
    backgroundmusic.openFromFile("Data/Audio/" + songs.at(rand() % songs.size()));
    //backgroundmusic.play();
}

void GameState::onWindowSet()
{
    std::cout<<"Window Set";
    sf::View view = window->getView();
    view.setCenter(WIDTH/2, level->heightInTiles*tileHeight - HEIGHT/2);
    window->setView(view);
}

void GameState::initPlayer()
{
    player = new Player;
    player->setLevel(level);
    player->setCollisionDetector(cd);
    player->setZ(1);
    addNode(player);
}

void GameState::initController()
{
    std::string inputType = getInputType();
    if(inputType == "keyboard")
        controller = new KeyboardController(player);
    else if(inputType == "joystick")
        controller = new JoystickController(player);
    else
        std::cout<<"No input type found.";
}

void GameState::onUpdate(sf::Time delta)
{
    cd->detectCollisions();
    controller->update(delta);

    background->setPosition(static_cast<int>(window->getView().getCenter().x), static_cast<int>(window->getView().getCenter().y));
}

std::string GameState::getInputType()
{
    pugi::xml_document doc;
    doc.load_file("Data/KeyBindings.xml");
    pugi::xml_node bindings = doc.child("bindings");
    return bindings.child("input_type").attribute("name").as_string();
}

void GameState::pause()
{

}

void GameState::resume()
{

}
