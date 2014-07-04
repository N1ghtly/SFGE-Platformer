#include "Level.h"
#include <iostream>

Level::Level(sfge::CollisionDetector& cd, const std::string& filename) : sfge::Node("Level"), cd(cd)
{
    tilesetTexture.loadFromFile("Data/Images/tileset.png");
    loadFromFile(filename);
}

Level::~Level()
{

}

void Level::loadFromFile(const std::string& filename)
{
    pugi::xml_document doc;
    doc.load_file(filename.c_str());

    //map
    pugi::xml_node map = doc.child("map");

    widthInTiles = map.attribute("width").as_int();
    heightInTiles = map.attribute("height").as_int();

    cd.setBounds(getBounds());

    //tileset
    pugi::xml_node tileset = map.child("tileset");
    readTilesetAttributes(tileset);

     //properties
    pugi::xml_node tile = tileset.child("tile");
    readTileProperties(tile);

    //tiles
    pugi::xml_node layer = map.child("layer");
    parseTiles(layer);

    //objects
    pugi::xml_node obj = map.child("objectgroup").child("object");
    parseObjects(obj);
}

LayerType Level::readLayerType(pugi::xml_node layer)
{
    pugi::xml_node property = layer.child("properties").child("property");
    std::string prop = property.attribute("name").as_string();
    if(prop == "transparent")
    {
        return TRANSPARENT;
    }
    else if (prop == "invisible")
    {
        return INVISIBLE;
    }
    else
    {
        return NORMAL;
    }
}

void Level::parseTiles(pugi::xml_node layer)
{
    //layer
    while(layer)
    {
        LayerType type = readLayerType(layer);
         //Columns and rows (of tileset image)
        int columns = tilesetTexture.getSize().x / (tileWidth + tilesetAttributes["spacing"]);
        int rows = tilesetTexture.getSize().y / (tileHeight + tilesetAttributes["spacing"]);

        std::vector <sf::IntRect > subRects;//container of subrects (to divide the tilesheet image up)
        buildSubRects(subRects, columns, rows);

        int x = 0;
        int y = 0;
        pugi::xml_node data = layer.child("data");
        for (pugi::xml_node tile = data.child("tile"); tile; tile = tile.next_sibling("tile"))
        {
            int GID = tile.attribute("gid").as_int();
            int subrect = GID - tilesetAttributes["firstgid"];
            if(subrect >= 0 && GID != 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tilesetTexture);
                sprite.setTextureRect(subRects[subrect]);
                sprite.setPosition(x * tileWidth, y * tileHeight);

                if(std::find(tileProperties[subrect].begin(), tileProperties[subrect].end(), "fallingtile") != tileProperties[subrect].end())
                {
                    FallingTile* newtile = new FallingTile(sprite);
                    cd.add(newtile);
                    addNode(newtile);
                }
                else
                {
                    if(type == NORMAL || type == TRANSPARENT)
                    {
                        Tile* newtile = new Tile(sprite, tileProperties[subrect]);
                        if(type != TRANSPARENT)
                            cd.add(newtile);
                        addNode(newtile);
                    }
                    else if(type == INVISIBLE)
                    {
                        InvisibleTile* newTile = new InvisibleTile(sprite, tileProperties[subrect]);
                        cd.add(newTile);
                        addNode(newTile);
                    }

                }
            }

            x++;
            if (x >= widthInTiles)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
            }
        }

        layer = layer.next_sibling("layer");
    }

}

void Level::parseObjects(pugi::xml_node obj)
{
    while(obj)
    {
        int x = obj.attribute("x").as_int();
        int y = obj.attribute("y").as_int();
        std::string name = std::string(obj.attribute("name").as_string());
        if(name == "coin")
        {
            Coin* coin = new Coin(x, y);
            coin->setZ(2);
            cd.add(coin);
            addNode(coin);
        }
        else if(name == "skeleton" || name == "bat")
        {
            FixedMovementEntity* skeleton = new FixedMovementEntity(name + ".xml", x, y);
            cd.add(skeleton);
            addNode(skeleton);
        }
        else if(name == "player")
        {
            playerpos.x = x;
            playerpos.y = y;
        }
        else if(name == "movingplatform")
        {
            int dx = 0;
            int dy = 0;
            sf::Time duration = sf::Time::Zero;

            for(pugi::xml_node property = obj.child("properties").child("property"); property; property = property.next_sibling("property"))
            {
                std::string name = std::string(property.attribute("name").as_string());
                if(name == "dx")
                {


                    dx = property.attribute("value").as_int();
                     std::cout<<dx;
                }
                else if(name == "dy")
                    dy = property.attribute("value").as_int();
                else if(name == "duration")
                    duration = sf::seconds(property.attribute("value").as_float());
            }

            MovingPlatform* platform = new MovingPlatform(x, y, dx, dy, duration);
            cd.add(platform);
            addNode(platform);
        }
        else if(name == "trampoline")
        {
            Trampoline* tramp = new Trampoline(x, y);
            cd.add(tramp);
            addNode(tramp);
        }
        else if(name == "leftcannon")
        {
            Cannon* cannon = new Cannon(x, y, DIRECTION::LEFT);
            cd.add(cannon);
            addNode(cannon);
        }
        else if(name == "rightcannon")
        {
            Cannon* cannon = new Cannon(x, y, DIRECTION::RIGHT);
            cd.add(cannon);
            addNode(cannon);
        }

        obj = obj.next_sibling("object");
    }
}

void Level::readTileProperties(pugi::xml_node tile)
{
    while (tile)
    {
        int id = tile.attribute("id").as_int();
        std::vector<std::string> properties;

        for(pugi::xml_node property = tile.child("properties").child("property"); property; property = property.next_sibling("property"))
            properties.push_back(property.attribute("name").as_string());

        tileProperties[id] = properties;

        tile = tile.next_sibling("tile");
    }
}

void Level::readTilesetAttributes(pugi::xml_node tileset)
{
    tilesetAttributes["spacing"] = tileset.attribute("spacing").as_int();
    tilesetAttributes["margin"] = tileset.attribute("margin").as_int();
    tilesetAttributes["tilewidth"] = tileset.attribute("tilewidth").as_int();
    tilesetAttributes["tileheight"] = tileset.attribute("tileheight").as_int();
    tilesetAttributes["firstgid"] = tileset.attribute("firstgid").as_int();
}

void Level::buildSubRects(std::vector<sf::IntRect>& subRects, int columns, int rows)
{
    //tiles/subrects are counted from 0, left to right, top to bottom
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::IntRect rect;
            rect.top = y * (tilesetAttributes["tileheight"] + tilesetAttributes["spacing"]) + tilesetAttributes["margin"];
            rect.width = tilesetAttributes["tilewidth"];
            rect.left = x * (tilesetAttributes["tilewidth"] + tilesetAttributes["spacing"]) + tilesetAttributes["margin"];
            rect.height = tilesetAttributes["tileheight"];
            subRects.push_back(rect);
        }
    }
}

sf::FloatRect Level::getBounds()
{
    return sf::FloatRect(0, 0, widthInTiles*tileWidth, heightInTiles*tileHeight);
}

sf::Vector2f Level::getPlayerStartingPosition()
{
    return playerpos;
}
