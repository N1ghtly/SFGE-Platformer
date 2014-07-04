#include "LevelState.h"

LevelState::LevelState()
{
    sfge::SpriteNode* background = new sfge::SpriteNode("background", "background.png");
    background->setZ(-10);
    addNode(background);
    sfge::SpriteNode* foreground = new sfge::SpriteNode("background", "foreground.png");
    foreground->setZ(10);
    addNode(foreground);

    readLevels();
}

LevelState::~LevelState()
{
    //dtor
}

void LevelState::readWorld(pugi::xml_node level, int x)
{
    int y = 128;
    for (; level; level = level.next_sibling("level"))
    {
        std::string file = level.attribute("file").as_string();
        std::string name = level.attribute("name").as_string();
        std::string diff = level.attribute("difficulty").as_string();
        bool unlocked = level.attribute("unlocked").as_bool();
        LevelButton* b = new LevelButton(file, name, diff, 120, x, y, unlocked);
        b->setZ(-1);
        b->setOnClickCallback(&LevelState::loadLevel, this);
        addNode(b);
        y += 6*32;
    }
}

void LevelState::readLevels()
{
    pugi::xml_document doc;
    doc.load_file("Data/Levels/levels.xml");
    pugi::xml_node levels = doc.child("levels");

    readWorld(levels.child("terra").child("level"), 128);
    readWorld(levels.child("desert").child("level"), 432);
    readWorld(levels.child("icy").child("level"), 688);
}

void LevelState::loadLevel(std::string file)
{
    director->replaceState(new GameState(file));
}

void LevelState::onHandle(const sf::Event& event)
{
    if(event.type == sf::Event::Closed)
        window->close();
    else if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
            director->popState();
    }
}

void LevelState::resume()
{

}
