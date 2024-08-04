#include "DB_Core.h"

using namespace DB_API;

std::vector<std::string> DB_API::SplitString(const std::string& str, char delimiter){
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void DB_API::Gumbo_To_Pugi(GumboNode* gnode, pugi::xml_node& pnode){
    if (gnode->type == GUMBO_NODE_ELEMENT) {
        pugi::xml_node child = pnode.append_child(gumbo_normalized_tagname(gnode->v.element.tag));
        
        // 添加属性
        GumboVector* attrs = &gnode->v.element.attributes;
        for (unsigned int i = 0; i < attrs->length; ++i) {
            GumboAttribute* attr = static_cast<GumboAttribute*>(attrs->data[i]);
            child.append_attribute(attr->name) = attr->value;
        }
        
        // 递归处理子节点
        GumboVector* children = &gnode->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            Gumbo_To_Pugi(static_cast<GumboNode*>(children->data[i]), child);
        }
    } else if (gnode->type == GUMBO_NODE_TEXT) {
        pnode.append_child(pugi::node_pcdata).set_value(gnode->v.text.text);
    }
}

std::vector<pugi::xml_node> DB_API::Find_Nodes_By_XPath(const std::string& html, const std::string& xpath){
    // 解析 HTML
    GumboOutput* output = gumbo_parse(html.c_str());
    
    // 创建 pugixml 文档
    pugi::xml_document doc;
    pugi::xml_node root = doc.append_child("html");
    
    // 将 Gumbo 树转换为 pugixml 树
    Gumbo_To_Pugi(output->root, root);
    
    // 使用 XPath 查询
    std::vector<pugi::xml_node> results;
    pugi::xpath_node_set nodes = doc.select_nodes(xpath.c_str());
    
    for (pugi::xpath_node node : nodes) {
        results.push_back(node.node());
    }
    
    // 清理 Gumbo 输出
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    
    return results;
}