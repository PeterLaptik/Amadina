#include "entity.h"

std::set<int> Entity::m_id_cash;

Entity::Entity()
{
    m_layer = nullptr;
}

Entity::~Entity()
{

}

void Entity::SetLayer(Layer *layer)
{
    m_layer = layer;
}

Layer* Entity::GetLayer(void) const
{
    return m_layer;
}
