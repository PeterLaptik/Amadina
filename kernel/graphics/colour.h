#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include <math.h>

// Type for R/G/B values
typedef unsigned char colour_t;

// R/G/B value for default constructor
static const colour_t DEFAULT_VALUE = 90;

///\brief Colour for entities and screen background
class Colour
{
    public:
        // Predefined colour values
        static const Colour BLACK;
        static const Colour WHITE;
        static const Colour RED;
        static const Colour GREEN;
        static const Colour BLUE;

        /// Default constructor
        Colour()
            : R(DEFAULT_VALUE), G(DEFAULT_VALUE), B(DEFAULT_VALUE)
        { }

        /// Constructor
        ///\param r - red value
        ///\param g - green value
        ///\param b - blue value
        Colour(int r, int g, int b)
            :   R(static_cast<colour_t>(r)),
                G(static_cast<colour_t>(g)),
                B(static_cast<colour_t>(b))
        { }

        /// Destructor
        ~Colour()
        { }

        unsigned char R;
        unsigned char G;
        unsigned char B;


        bool operator==(const Colour &other)
        {
            return (this->R==other.R)&&(this->G==other.G)&&(this->B==other.B);
        }

        /// Checks is the colour is a grey colour
        /// (i.e. R-value = G-value = B-value)
        bool IsGrey(void) const
        {
            return (R==G)&&(G==B);
        }

        ///\brief Returns: whether the colour is dark or not
        ///\return is a dark colour
        bool IsDark(void) const
        {
            return IsGrey() && (R<=DARK_COLOUR);
        }

        ///\brief Inverses colour value.
        /// Works only for black/white/grey background and entity colours.
        /// If an entity colour is the same as a background colour
        /// or too close to the background colour
        /// then the entity colour will be inverted.
        void CheckAndInverse(const Colour &background)
        {
            if((!background.IsGrey())||(!this->IsGrey()))
                return; // do not inverse for non-grey colours

            bool is_dark_colour = R<=DARK_COLOUR;
            bool is_dark_background = background.R<=DARK_BACKGROUND;
            // Black colours on a dark background
            if((is_dark_background)&&(is_dark_colour))
            {
                R = MAX_VALUE - R;
                G = MAX_VALUE - G;
                B = MAX_VALUE - B;
                return;
            }
        }

    private:
        // Border R/G/B-values for dark / non-dark colours
        static const int DARK_BACKGROUND;
        static const int DARK_COLOUR;

        // Maximum colour value
        // I.e. white colour for R=G=B
        static const int MAX_VALUE;
};


#endif // COLOUR_H_INCLUDED
