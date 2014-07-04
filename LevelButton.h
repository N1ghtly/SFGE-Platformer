#ifndef LEVELBUTTON_H
#define LEVELBUTTON_H
#include <SFGE/Gui/Label.h>
#include <SFGE/Core/SpriteNode.h>
#include <SFGE/Core/Node.h>
#include <SFGE/Core/ShapeNode.h>
#include <functional>


class LevelButton : public sfge::Node
{
    typedef std::function<void (std::string)> callback;

    public:
        LevelButton(const std::string& file, const std::string& name, const std::string& difficulty, int bestTime, int x, int y, bool unlocked);
        virtual ~LevelButton();

        template<class T>
        void setOnClickCallback(void (T::*func)(std::string), T* object)
        {
            onClickCallback = std::bind(func, object, std::placeholders::_1);
        }

    protected:
        virtual void onHandle(const sf::Event& event);


    private:
        sfge::Label* nameLabel;
        sfge::Label* difficultyLabel;
        sfge::Label* bestTimeLabel;
        sfge::ShapeNode* frame;

        std::string file;
        callback onClickCallback;
        bool unlocked;
};

#endif // LEVELBUTTON_H
