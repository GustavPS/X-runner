#ifndef LEVEL_H
#define LEVEL_H

#include <pugixml.hpp>

#include "../objects/abstractish/object.h"

#include <string>
#include <vector>
#include <unordered_map>

class Level_Parser
{
    public:
        Level_Parser(const std::string&);
        std::vector<Object*> get_objects(
            const std::unordered_map<std::string, sf::Texture*>&) const;
        

    private:
        pugi::xml_document m_xml_doc;

        std::vector<Object*> get_xml_objects(
            const std::unordered_map<std::string, sf::Texture*>&) const;
        std::vector<Object*> get_csv_objects() const;
};

#endif