#ifndef LEVEL_H
#define LEVEL_H

#include <pugixml.hpp>
#include <string>
#include <vector>

#include "../objects/abstract/object.h"
#include "../objects/non_abstract/player.h"
//#include "../objects/block.h"
//#include "../objects/player.h"

class Level_Parser
{
    public:
        Level_Parser(const std::string&);
        std::vector<Object*> get_objects() const;
        Player* get_player() const;
        std::vector<Object*> get_npcs() const;
        std::vector<Object*> get_blocks() const;

    private:
        pugi::xml_document xml_doc;
        std::vector<pugi::xml_node*> get_objects_as_xml(const std::string&) const;
        void delete_ptrs(const std::vector<pugi::xml_node*>&) const;
};

#endif