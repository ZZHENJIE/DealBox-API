#pragma once

#include "cpr/cpr.h"
#include "yyjson/yyjson.h"
#include "gumbo-parser/gumbo.h"
#include "pugixml/pugixml.hpp"

namespace DB_API{
    std::vector<std::string> SplitString(const std::string& str, char delimiter);
    void Gumbo_To_Pugi(GumboNode* gnode, pugi::xml_node& pnode);
    std::vector<pugi::xml_node> Find_Nodes_By_XPath(const std::string& html, const std::string& xpath);
};