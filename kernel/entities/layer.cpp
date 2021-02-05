#include "layer.h"
#include "../graphics/dc.h"

Layer::Layer(const std::string &name, const Colour &colour)
    : m_name(name),
    m_is_visible(true),
    m_colour(colour),
    m_thickness(1)
{ }

Layer::~Layer()
{ }


void Layer::Apply(IAdapterDC &dc) const
{
    dc.CadSetColour(m_colour);
}

void Layer::SetColour(const Colour &colour)
{
    m_colour = colour;
}

const Colour& Layer::GetColour() const
{
    return m_colour;
}

const std::string& Layer::GetName(void) const
{
    return m_name;
}
