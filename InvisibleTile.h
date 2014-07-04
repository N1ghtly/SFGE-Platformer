#ifndef INVISIBLETILE_H
#define INVISIBLETILE_H
#include <vector>
#include <string>
#include "Tile.h"


class InvisibleTile : public Tile
{
    public:
        InvisibleTile(const sf::Sprite& sprite, std::vector<std::string> properties);
        virtual ~InvisibleTile();
        void onCollision(sfge::CollidableNode* obj, sf::Vector2f mtv);
        void onDraw();

    private:
        bool visible;
};

#endif // INVISIBLETILE_H
