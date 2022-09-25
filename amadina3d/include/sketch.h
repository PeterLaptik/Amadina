#ifndef SKETCH_H
#define SKETCH_H

#include "historynode.h"
#include <string>
#include <vector>
#include <set>

namespace cad
{
    namespace modeller
    {
        namespace structure
        {
            class Sketch: public HistoryNode
            {
                public:
                    Sketch();
                    Sketch(const std::string &sketch_name);
                    virtual ~Sketch();

                    void SetName(const std::string &sketch_name);

                private:
                    static int m_name_counter;
                    static std::set<std::string> m_names_set;
                    static std::string GenerateName(void);

                    std::string m_name;
                    std::vector<HistoryNode*> m_children;
            };
        }
    }
}

#endif // SKETCH_H
