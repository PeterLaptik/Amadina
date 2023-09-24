#include "operations_tree.h"

cad::modeller::OperationsTree::~OperationsTree()
{
    for(auto object: m_objects)
        delete object;
}

void cad::modeller::OperationsTree::AddObject(AbstractShape *object)
{

}