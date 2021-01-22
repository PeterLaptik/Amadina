#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include "../graphics/colour.h"
#include <string>

class IAdapterDC;

class Layer
{
    public:
        Layer(const std::string &name);
        virtual ~Layer();

        void Apply(IAdapterDC &dc) const;

        void SetColour(const Colour &colour);

        const Colour& GetColour() const;

    protected:

    private:
        std::string m_name;
        bool m_is_visible;
        Colour m_colour;
        int m_thickness;
};

#endif // LAYER_H_INCLUDED
