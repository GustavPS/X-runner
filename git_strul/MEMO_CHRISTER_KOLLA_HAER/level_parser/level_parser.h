#ifndef LEVEL_H
#define LEVEL_H

#include <pugixml.hpp>
#include <string>
#include <vector>

#include "../objects/abstract/object.h"

class Level_Parser
{
    public:
        Level_Parser(const std::string&);
        void load_level(const std::string&);
        std::vector<Object*> get_objects() const;

    private:
        pugi::xml_document m_xml_doc;
        std::vector<Object*> get_xml_objects() const;
        std::vector<Object*> get_csv_objects() const;
};

#endif