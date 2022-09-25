#include "structurenode.h"

cad::structure::StructureNode::StructureNode(const std::string &name)
    : m_name(name)
{ }

cad::structure::StructureNode::~StructureNode()
{
    for(auto child: m_children)
        delete child;
}
