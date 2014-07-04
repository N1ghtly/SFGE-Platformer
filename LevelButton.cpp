#include "LevelButton.h"
#include <string>


LevelButton::LevelButton(const std::string& file, const std::string& name, const std::string& difficulty, int bestTime, int x, int y, bool unlocked) : file(file), unlocked(unlocked)
{
    nameLabel = new sfge::Label(name, x, y);
    nameLabel->setFontSize(17);
    nameLabel->setFont(rm->getFont("scribble.ttf"));
    nameLabel->setCenterAsOrigin();
    difficultyLabel = new sfge::Label(difficulty, x, y-30);
    difficultyLabel->setFontSize(17);
    difficultyLabel->setFont(rm->getFont("scribble.ttf"));
    difficultyLabel->setCenterAsOrigin();
    bestTimeLabel = new sfge::Label("test", x, y+30);
    bestTimeLabel->setFontSize(17);
    bestTimeLabel->setFont(rm->getFont("scribble.ttf"));
    bestTimeLabel->setCenterAsOrigin();

    sf::RectangleShape* f = new sf::RectangleShape(sf::Vector2f(200, 200));
    f->setPosition(x, y);
    f->setOrigin(f->getLocalBounds().width/2,f->getLocalBounds().height/2 );
    if(!unlocked)
        f->setFillColor(sf::Color(0, 0, 0, 200));
    else
        f->setFillColor(sf::Color(0, 0, 0, 0));
    frame = new sfge::ShapeNode(f);
    frame->setZ(1);

    addNode(nameLabel);
    addNode(difficultyLabel);
    addNode(bestTimeLabel);
    addNode(frame);
}

LevelButton::~LevelButton()
{
    //dtor
}

void LevelButton::onHandle(const sf::Event& event)
{
    if(event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f pos(window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)));
            if(frame->getShape()->getGlobalBounds().contains(pos) && unlocked)
            {
                nameLabel->setScale(1.1, 1.1);
                difficultyLabel->setScale(1.1, 1.1);
                bestTimeLabel->setScale(1.1, 1.1);
            }
            else
            {
                nameLabel->setScale(1.0, 1.0);
                difficultyLabel->setScale(1.0, 1.0);
                bestTimeLabel->setScale(1.0, 1.0);
            }

    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f pos(window->mapPixelToCoords(sf::Vector2i(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)));
            if(frame->getShape()->getGlobalBounds().contains(pos))
                if(onClickCallback && unlocked)
                    onClickCallback(file);
    }
}
