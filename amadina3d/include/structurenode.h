#ifndef STRUCTURENODE_H
#define STRUCTURENODE_H

#include <vector>
#include <string>

namespace cad
{
    namespace structure
    {
        class StructureNode
        {
            public:
                StructureNode();
                StructureNode(const std::string &name);
                virtual ~StructureNode();

            private:
                std::string m_name;
                std::vector<StructureNode*> m_children;
        };
    }
}


#endif // STRUCTURENODE_H
