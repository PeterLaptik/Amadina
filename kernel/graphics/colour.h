#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include <math.h>

///\brief Colour for entities and screen background
class Colour
{
    public:
        // Type for R/G/B values
        typedef unsigned char colour_t;

        // R/G/B value for default constructor
        static const colour_t DEFAULT_VALUE = 90;

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
            return IsGrey() && (R<=Colour::DARK_COLOUR);
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

            bool is_dark_colour = R<=Colour::DARK_COLOUR;
            bool is_dark_background = background.R<=Colour::DARK_BACKGROUND;
            // Black colours on a dark background
            if((is_dark_background)&&(is_dark_colour))
            {
                R = Colour::MAX_VALUE - R;
                G = Colour::MAX_VALUE - G;
                B = Colour::MAX_VALUE - B;
                return;
            }
        }

        // Border R/G/B-values for dark / non-dark colours
        static const colour_t DARK_BACKGROUND = 70;
        static const colour_t DARK_COLOUR = 30;

        // Maximum colour value
        // I.e. white colour for R=G=B
        static const colour_t MAX_VALUE = 255;
};

#endif // COLOUR_H_INCLUDED
