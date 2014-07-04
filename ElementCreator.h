#ifndef BUTTONCREATOR_H_INCLUDED
#define BUTTONCREATOR_H_INCLUDED
#include <SFGE/Gui/LabelButton.h>

namespace ElementCreator
{
    static sfge::LabelButton* makeButton(const std::string& label, int x, int y, bool center = true, int fontSize = 35)
    {
        sfge::LabelButton* button = new sfge::LabelButton(label, x, y);
        button->setFont(rm->getFont("scribble.TTF"));
        button->setFontSize(fontSize);
        if(center)
            button->setCenterAsOrigin();        button->setColor(sf::Color::Black);
        return button;
    }

    static sfge::Label* makeTitle(const std::string& label, int x, int y, bool center = true)
    {
        sfge::Label* button = new sfge::Label(label, x, y);
        button->setFont(rm->getFont("scribble.TTF"));
        button->setFontSize(55);
        if(center)
            button->setCenterAsOrigin();        button->setColor(sf::Color::Black);
        return button;
    }

    static sfge::Label* makeLabel(const std::string& label, int x, int y, bool center = true)
    {
        sfge::Label* button = new sfge::Label(label, x, y);
        button->setFont(rm->getFont("scribble.TTF"));
        button->setFontSize(30);
        if(center)
            button->setCenterAsOrigin();        button->setColor(sf::Color::Black);
        return button;
    }
}


#endif // BUTTONCREATOR_H_INCLUDED
