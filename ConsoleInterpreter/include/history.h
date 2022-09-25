#ifndef HISTOTY_NODE_H_INCLUDED
#define HISTOTY_NODE_H_INCLUDED

#include <vector>

namespace cad
{
    namespace structure
    {
        class HistoryNode
        {
            public:
                HistoryNode(HistoryNode *parent = nullptr)
                    : m_parent(parent)
                {}

                virtual ~HistoryNode()
                {}

            private:
                struct Dependency
                {
                    bool is_valid;
                    HistoryNode *node;
                };

                HistoryNode *m_parent;
                std::vector<Dependency> m_dependencies;
        };
    }
}

#endif // HISTOTY_NODE_H_INCLUDED
