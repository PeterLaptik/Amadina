#include "../include/objectpool.h"

ObjectPool::ObjectPool()
{ }

ObjectPool::~ObjectPool()
{
    m_shapes.clear();
}


void ObjectPool::AppendShape(Handle(AIS_Shape) shape)
{
    m_shapes.push_back(shape);
}
