#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

#include <math.h>

typedef unsigned char colour_t;

static const colour_t DEFAULT_VALUE = 0;

class Colour
{
    public:
        // Predefined colour values
        static const Colour BLACK;
        static const Colour WHITE;
        static const Colour RED;
        static const Colour GREEN;
        static const Colour BLUE;

        Colour()
            : R(DEFAULT_VALUE), G(DEFAULT_VALUE), B(DEFAULT_VALUE)
        { }

        Colour(int r, int g, int b)
            :   R(static_cast<colour_t>(r)),
                G(static_cast<colour_t>(g)),
                B(static_cast<colour_t>(b))
        { }

        ~Colour()
        { }

        unsigned char R;
        unsigned char G;
        unsigned char B;


        bool operator==(const Colour &other)
        {
            return (this->R==other.R)&&(this->G==other.G)&&(this->B==other.B);
        }

        bool IsGrey(void) const
        {
            return (R==G)==B;
        }

        void CheckAndInverse(const Colour &background)
        {
            if(!background.IsGrey())
                return;

            double level = background.R;
            double diff = fabs(static_cast<int>(level) - static_cast<int>(R));

            // Black / white backgrounds
            if(diff<MIN_DIFF)
            {
                if(level<70)
                {
                    // Black background
                    R = MAX_VALUE - R;
                    G = MAX_VALUE - G;
                    B = MAX_VALUE - B;
                    return;
                }
                else if(level>MAX_VALUE - MIN_DIFF)
                {
                    // White background
                    R = MAX_VALUE - background.R;
                    G = MAX_VALUE - background.G;
                    B = MAX_VALUE - background.B;
                    return;
                }
            }
            // Grey background
            if((background.R==background.G)&&(background.R==background.B))
            {

            }
            // Colour backgrounds

        }

    private:
        static const int MIN_DIFF = 15;
        static const int MAX_VALUE = 255;
};


#endif // COLOUR_H_INCLUDED
