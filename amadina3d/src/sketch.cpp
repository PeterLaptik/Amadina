#include "sketch.h"

using cad::modeller::structure::Sketch;

const std::string DEFAULT_NAME_PREFIX = "Sketch ";

int Sketch::m_name_counter = 0;
std::set<std::string> Sketch::m_names_set;

Sketch::Sketch()
{
    m_name = GenerateName();
}

Sketch::Sketch(const std::string &sketch_name)
    : m_name(sketch_name)
{ }

Sketch::~Sketch()
{ }

void Sketch::SetName(const std::string &sketch_name)
{
    m_name = sketch_name;
}

std::string Sketch::GenerateName()
{
    std::string name = DEFAULT_NAME_PREFIX + std::to_string(m_name_counter++);
    while(Sketch::m_names_set.find(name)!=Sketch::m_names_set.end())
    {
        name = DEFAULT_NAME_PREFIX + std::to_string(m_name_counter++);
    }
    return name;
}
