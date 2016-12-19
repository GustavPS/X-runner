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
}

std::vector<Object*> Level_Parser::get_objects(
    const std::unordered_map<std::string, sf::Texture*> &textures) const
{
    std::vector<Object*> objects;

    auto xml_objects { get_xml_objects(textures) };

    auto csv_objects { get_csv_objects() };

    objects.insert(objects.end(), xml_objects.begin(), xml_objects.end());

    objects.insert(objects.end(), csv_objects.begin(), csv_objects.end());
    
    return objects;
}

std::vector<Object*> Level_Parser::get_xml_objects(
    const std::unordered_map<std::string, sf::Texture*> &textures) const
{
    // vector to store created objects in
    std::vector<Object*> xml_objects;

    // iterate over each objectgroup
    for (pugi::xml_node xml_objectgroup
            { m_xml_doc.child("map").child("objectgroup") }
         ; xml_objectgroup
         ; xml_objectgroup = xml_objectgroup.next_sibling("objectgroup"))
    {
        // check if the objectgroup is to be ignored, if so, continue to the next iteration
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

            
        // iterate over each object in the objectgroup
        for (pugi::xml_node xml_object
                { xml_objectgroup.child("object") }
             ; xml_object
             ; xml_object = xml_object.next_sibling("object"))
        {

            // assign the objects attributes to respective variables
            std::string type { (xml_object.attribute("name").as_string()) };

            sf::Vector2f position
                { xml_object.attribute("x").as_float(), xml_object.attribute("y").as_float() };

            sf::Vector2f size
                { xml_object.attribute("width").as_float(), xml_object.attribute("height").as_float() };

            int gid {xml_object.attribute("gid").as_int()};

            // assign attributes defined in the objects property children to respective varaiables
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

            // if the type is any of the follow, create an object of that type
            // and insert it into vector of objects
            if (type == "player")
            {
                xml_objects.push_back( new Player { position, size, type,
                                                    textures.find(type)->second,
                                                    speed } );
            }
            else if (type == "slow_bird")
            {
                xml_objects.push_back( new Slow_Bird { position, size, type,
                                                       textures.find(type)->second,
                                                       speed, direction } );
            }
            else if (type == "boost_bird")
            {
                xml_objects.push_back( new Boost_Bird { position, size, type,
                                                        textures.find(type)->second,
                                                        speed, direction } );
            }
            else if (type == "bomb_bird")
            {
                xml_objects.push_back( new Bomb_Bird { position, size, type,
                                                       textures.find(type)->second,
                                                       speed, direction,
                                                       textures.find("nfbb")->second } );
            }
            else if (type == "nfbb")
            {
                xml_objects.push_back( new NFBB { position, size, type,
                                                  textures.find(type)->second } );
            }
        }
    }

    // return created objects
    return xml_objects;
}

std::vector<Object*> Level_Parser::get_csv_objects() const
{
    // vector to store created objects in
    std::vector<Object*> csv_objects;

    // iterate over each layer
    for (pugi::xml_node xml_layer
            { m_xml_doc.child("map").child("layer") }
         ; xml_layer
         ; xml_layer = xml_layer.next_sibling("layer"))
    {

        // check if the layer is to be ignored, if so, continue to the next iteration
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

        // iterate over each csv-item
        // we start out att row 0 and column 0
        int row {};
        int column {};
        std::istringstream iss { xml_layer.child("data").text().as_string() };
        int gid {};
        while (iss >> gid)
        {
            // if the item has no gid set in Tiled Map Editor, the object should be ignored
            if (gid != 0.0)
            {
                // iterate over each tileset
                bool found { false };
                for (pugi::xml_node xml_tileset
                        { m_xml_doc.child("map").child("tileset") }
                    ; xml_tileset
                    ; xml_tileset = xml_tileset.next_sibling("tileset"))
                {

                    // first gid in the tileset and the tiles width and height
                    int firstgid { xml_tileset.attribute("firstgid").as_int() };
                    float tilewidth { xml_tileset.attribute("tilewidth").as_float() };
                    float tileheight { xml_tileset.attribute("tileheight").as_float() };

                    // iterate over each tile in the tileset
                    for (pugi::xml_node xml_tile
                            { xml_tileset.child("tile") }
                        ; xml_tile
                        ; xml_tile = xml_tile.next_sibling("tile"))
                    {

                        // if the tile's id == gid - firstgid, the current gid correlates to this tile
                        if (xml_tile.attribute("id").as_int() == gid - firstgid)
                        {
                            // assign the tilesets attributes to respective variables

                            // column * tilewidth = x-position
                            // row * tileheight = y-position
                            sf::Vector2f position { column * tilewidth, row * tileheight };

                            // tilewidth respective tileheight = x,y size
                            sf::Vector2f size { tilewidth, tileheight };

                            std::string type;

                            // assign attributes defined in the tiles property children to respective varaiables
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

                            // Create an object of that type with set attributes
                            // and insert it into vector of objects
                            csv_objects.push_back ( new Object { position, size, type, solid } );

                            found = true; //set found=true so we dont skip atleast some unnecessary iterations
                            break;
                        }
                    }
                    if (found) // no need to continue iterations if found
                        break;
                }
            }

            //ignore a comma
            iss.ignore();

            // if new row, increment rows and set columns to 0
            // else increment columns
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

    // return created objects
    return csv_objects;
}