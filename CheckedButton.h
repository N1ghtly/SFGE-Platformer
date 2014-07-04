#ifndef CHECKEDBUTTON_H
#define CHECKEDBUTTON_H

#include <SFGE/Gui/LabelButton.h>


class CheckedButton : public sfge::LabelButton
{
    public:
        CheckedButton(const std::string& name, int x, int y);
        virtual ~CheckedButton();

        virtual void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    private:
};

#endif // CHECKEDBUTTON_H
