#include "level_parser.h"

Level_Parser::Level_Parser(const std::string &path)
{
    pugi::xml_parse_result parse_result;
    parse_result = xml_doc.load_file(path.c_str());
    if (!parse_result)
    {
        throw std::logic_error(std::string(parse_result.description()));
    }
}

std::vector<Object*> Level_Parser::get_objects() const
{
    std::vector<Object*> objects { get_player() };

    auto block { get_blocks() };

    objects.insert(objects.end(), block.begin(), block.end());
    
    return objects;
}

Player* Level_Parser::get_player() const
{
    auto xml_player { get_objects_as_xml("player").at(0) };

    sf::Vector2f position { xml_player->attribute("x").as_float(),
                            xml_player->attribute("y").as_float() };

    sf::Vector2f dimensions { xml_player->attribute("width").as_float(),
                              xml_player->attribute("height").as_float() };

    // int gid { xml_player->attribute("gid").as_int() };

    std::vector<std::string> types { xml_player->attribute("name").as_string() };

    delete xml_player; //note possible memleak if > 1 players in level_parser

    return new Player { position, dimensions, types, 250, 10 };
}

std::vector<Object*> Level_Parser::get_blocks() const
{
    auto xml_blocks { get_objects_as_xml("blocks") };

    std::vector<Object*> blocks;

    for (const auto xml_block : xml_blocks)
    {
        sf::Vector2f position { xml_block->attribute("x").as_float(),
                                xml_block->attribute("y").as_float() };
        
        sf::Vector2f dimensions { xml_block->attribute("width").as_float(),
                                  xml_block->attribute("height").as_float() };
        
        std::vector<std::string> types { xml_block->attribute("name").as_string() };

        delete xml_block;

        blocks.push_back( new Object { position, dimensions, types } );
    }

    return blocks;
}

std::vector<pugi::xml_node*> Level_Parser::get_objects_as_xml(
    const std::string &name) const
{
    static pugi::xml_node xml_map { xml_doc.child("map") };
    
    pugi::xml_node xml_objectgroup { xml_map.child("objectgroup") };

    while (xml_objectgroup
        && xml_objectgroup.attribute("name").as_string() != name)
    {
        xml_objectgroup = xml_objectgroup.next_sibling("objectgroup");
    }

    std::vector<pugi::xml_node*> xml_objects;

    if (xml_objectgroup)
    {
        for (pugi::xml_node xml_object { xml_objectgroup.child("object") }
           ; xml_object; xml_object = xml_object.next_sibling("object"))
        {
            xml_objects.push_back( new pugi::xml_node { xml_object } );
        }   
    }
    
    return xml_objects;
}

void Level_Parser::delete_ptrs(
    const std::vector<pugi::xml_node*> &xml_objects) const
{
    for (const auto xml_object : xml_objects)
    {
        delete xml_object;
    }
}