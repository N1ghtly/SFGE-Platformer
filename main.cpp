#include <SFML/Graphics.hpp>
#include <SFGE/Core/Director.h>
#include "MenuState.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Platformer");
    window.setFramerateLimit(100);
    srand(time(NULL));

    rm->setTextureDir("Data/Images/");
    rm->setAudioDir("Data/Audio/");
    rm->setFontDir("Data/Fonts/");

    sfge::Director director(window);
    director.setTimestep(sf::milliseconds(10));
    director.run(new MenuState());
}
