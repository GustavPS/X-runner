#include "level_parser.h"

#include "../objects/non_abstract/player.h"
#include "../objects/non_abstract/slow_bird.h"
#include "../objects/non_abstract/bomb_bird.h"
#include "../objects/non_abstract/boost_bird.h"
#include "../objects/non_abstract/nfbb.h"

#include <sstream>

Level_Parser::Level_Parser(const std::string &path)
{
    pugi::xml_parse_result parse_result;
    parse_result = m_xml_doc.load_file(path.c_str());
    if (!parse_result)
    {
        throw std::logic_error(std::string(parse_result.description()));
    }

    m_textures["player"] = new sf::Texture;
    m_textures["player"]->loadFromFile("Block_Ninja/idle.PNG");

    m_textures["slow_bird"] = new sf::Texture;
    m_textures["slow_bird"]->loadFromFile("Block_Ninja/idle.PNG");

    m_textures["boost_bird"] = new sf::Texture;
    m_textures["boost_bird"]->loadFromFile("Block_Ninja/idle.PNG");

    m_textures["bomb_bird"] = new sf::Texture;
    m_textures["bomb_bird"]->loadFromFile("Block_Ninja/idle.PNG");

    m_textures["nfbb"] = new sf::Texture;
    m_textures["nfbb"]->loadFromFile("Block_Ninja/idle.PNG");
}

std::vector<Object*> Level_Parser::get_objects() const
{
    std::vector<Object*> objects;

    auto xml_objects { get_xml_objects() };

    auto csv_objects { get_csv_objects() };

    objects.insert(objects.end(), xml_objects.begin(), xml_objects.end());

    objects.insert(objects.end(), csv_objects.begin(), csv_objects.end());
    
    return objects;
}

std::vector<Object*> Level_Parser::get_xml_objects() const
{
    std::vector<Object*> xml_objects;

    for (pugi::xml_node xml_objectgroup
            { m_xml_doc.child("map").child("objectgroup") }
         ; xml_objectgroup
         ; xml_objectgroup = xml_objectgroup.next_sibling("objectgroup"))
    {
        bool ignore { false };

        for (pugi::xml_node xml_property
                 { xml_objectgroup.child("properties").child("property") }
             ; xml_property
             ; xml_property = xml_property.next_sibling("property"))
        {
            if (std::string(xml_property.attribute("name").as_string()) == "ignore")
            {
                if (xml_property.attribute("value").as_bool() == false)
                {
                    ignore = true;
                    break;
                }
            }
        }

        if (ignore)
            continue;

        for (pugi::xml_node xml_object
                { xml_objectgroup.child("object") }
             ; xml_object
             ; xml_object = xml_object.next_sibling("object"))
        {
            std::string type { (xml_object.attribute("name").as_string()) };

            sf::Vector2f position
                { xml_object.attribute("x").as_float(), xml_object.attribute("y").as_float() };

            sf::Vector2f size
                { xml_object.attribute("width").as_float(), xml_object.attribute("height").as_float() };

            int gid {xml_object.attribute("gid").as_int()};

            float speed {};
            int direction {};
            for (pugi::xml_node xml_property
                    { xml_object.child("properties").child("property") }
                ; xml_property
                ; xml_property = xml_property.next_sibling("property"))
            {
                if (std::string(xml_property.attribute("name").as_string()) == "speed")
                    speed = xml_property.attribute("value").as_float();
                else if (std::string(xml_property.attribute("name").as_string()) == "direction")
                    direction = xml_property.attribute("value").as_int(); 
            }

            // Bugfix: Tiled Map Editor offsets position.y with +size.y for texturated objects
            if (gid != 0)
                position.y -= size.y;

            if (type == "player")
            {
                xml_objects.push_back( new Player { position, size, type, m_textures.find(type)->second, speed } );
            }
            else if (type == "slow_bird")
            {
                xml_objects.push_back( new Slow_Bird { position, size, type, m_textures.find(type)->second, speed, direction } );
            }
            else if (type == "boost_bird")
            {
                xml_objects.push_back( new Boost_Bird { position, size, type, m_textures.find(type)->second, speed, direction } );
            }
            else if (type == "bomb_bird")
            {
                xml_objects.push_back( new Bomb_Bird { position, size, type, m_textures.find(type)->second, speed, direction, m_textures.find("nfbb")->second } );
            }
            else if (type == "nfbb")
            {
                xml_objects.push_back( new NFBB { position, size, type, m_textures.find(type)->second } );
            }
        }
    }

    return xml_objects;
}

std::vector<Object*> Level_Parser::get_csv_objects() const
{
    std::vector<Object*> csv_objects;

    for (pugi::xml_node xml_layer
            { m_xml_doc.child("map").child("layer") }
         ; xml_layer
         ; xml_layer = xml_layer.next_sibling("layer"))
    {
        bool ignore { false };

        for (pugi::xml_node xml_property
                { xml_layer.child("properties").child("property") }
             ; xml_property
             ; xml_property = xml_property.next_sibling("property"))
        {
            if (std::string(xml_property.attribute("name").as_string()) == "ignore")
            {
                if (xml_property.attribute("value").as_bool() == true)
                {
                    ignore = true;
                    break;
                }
            }
        }

        if (ignore)
            continue;

        int row {};
        int column {};
        std::istringstream iss { xml_layer.child("data").text().as_string() };
        int gid {};
        while (iss >> gid)
        {
            if (gid != 0.0)
            {
                bool found { false };
                for (pugi::xml_node xml_tileset
                        { m_xml_doc.child("map").child("tileset") }
                    ; xml_tileset
                    ; xml_tileset = xml_tileset.next_sibling("tileset"))
                {
                    int firstgid { xml_tileset.attribute("firstgid").as_int() };
                    float tilewidth { xml_tileset.attribute("tilewidth").as_float() };
                    float tileheight { xml_tileset.attribute("tileheight").as_float() };

                    for (pugi::xml_node xml_tile
                            { xml_tileset.child("tile") }
                        ; xml_tile
                        ; xml_tile = xml_tile.next_sibling("tile"))
                    {
                        if (xml_tile.attribute("id").as_int() == gid - firstgid)
                        {
                            sf::Vector2f position { column * tilewidth, row * tileheight };

                            sf::Vector2f size { tilewidth, tileheight };

                            std::string type;

                            bool solid {};

                            for (pugi::xml_node xml_property
                                    { xml_tile.child("properties").child("property") }
                                ; xml_property
                                ; xml_property = xml_property.next_sibling("property"))
                            {
                                if (std::string(xml_property.attribute("name").as_string()) == "type")
                                    type = xml_property.attribute("value").as_string();
                                else if (std::string(xml_property.attribute("name").as_string()) == "solid")
                                    solid = xml_property.attribute("value").as_bool();

                                
                            }

                            csv_objects.push_back ( new Object { position, size, type, solid } );

                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            }

            iss.ignore();
            if (iss.peek() == '\n')
            {
                ++row;
                column = 0;
            }
            else
            {
                ++column;
            }
        }
    }

    return csv_objects;
}