#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include "../graphics/colour.h"
#include "../graphics/colours.h"
#include <string>
#include "../api/exports.h"

class IAdapterDC;

class DLL_EXPORT Layer
{
    public:
        Layer(const std::string &name, const Colour &colour = Colours::BLACK);
        virtual ~Layer();

        void Apply(IAdapterDC &dc) const;

        void SetColour(const Colour &colour);

        const Colour& GetColour() const;

        const std::string& GetName(void) const;

    protected:

    private:
        std::string m_name;
        bool m_is_visible;
        Colour m_colour;
        int m_thickness;
};

#endif // LAYER_H_INCLUDED
