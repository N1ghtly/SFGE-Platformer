#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include <SFGE/Core/CollisionDetector.h>
#include "pugixml.hpp"
#include "InvisibleTile.h"
#include "FallingTile.h"
#include "Trampoline.h"
#include "MovingPlatform.h"
#include "Coin.h"
#include "FixedMovementEntity.h"
#include "Cannon.h"
#include <memory>

enum LayerType {NORMAL, TRANSPARENT, INVISIBLE};

class Level : public sfge::Node
{
    friend class GameState;
    friend class Player;

    public:
        Level(sfge::CollisionDetector& cd, const std::string& filename);
        virtual ~Level();

        sf::Vector2f getPlayerStartingPosition();
        sf::FloatRect getBounds();

    private:
        sfge::CollisionDetector& cd;
        sf::Texture tilesetTexture;
        int widthInTiles;
        int heightInTiles;
        sf::Vector2f playerpos;

        std::map<std::string, int> tilesetAttributes;
        std::map<int, std::vector<std::string> > tileProperties;

        void loadFromFile(const std::string& filename);
        void readTilesetAttributes(pugi::xml_node tileset);
        void readTileProperties(pugi::xml_node tile);
        void parseTiles(pugi::xml_node layer);
        void parseObjects(pugi::xml_node obj);
        LayerType readLayerType(pugi::xml_node obj);
        void buildSubRects(std::vector<sf::IntRect>& subRects, int columns, int rows);
};

#endif // LEVEL_H
