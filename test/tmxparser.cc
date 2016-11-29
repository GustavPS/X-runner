#include "pugixml.hpp"
#include <iostream>

class TMXparser
{
public:
  pugi::xml_parse_result loadmap()
  {
      pugi::xml_document doc;
      pugi::xml_parse_result result = doc.load_file("new.tmx");
      return result;
  }
};

int main()
{
  pugi::xml_document doc;
  pugi::xml_parse_result parse_result = doc.load_file("new.tmx");
  if (!parse_result) return 1;

  pugi::xml_node map { doc.child("map") };
  pugi::xml_node objectgroup { map.child("objectgroup") };
  for (pugi::xml_node object { objectgroup.child("object") }
       ; object; object = object.next_sibling("object"))
  {
    std::cerr << "name: " << object.attribute("name").value()
              << "\t||\tid: " << object.attribute("id").value()
              << "\n";
  }
}
