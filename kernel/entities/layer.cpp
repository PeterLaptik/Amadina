#include "layer.h"

Layer::Layer(const std::string &name)
    : m_name(name),
    m_is_visible(true),
    m_colour(Colour(0,0,0)),
    m_thickness(1)
{ }

Layer::~Layer()
{ }

const Colour& Layer::GetColour() const
{
    return m_colour;
}
