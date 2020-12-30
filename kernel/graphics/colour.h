#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED

typedef unsigned char colour_t;

static const colour_t DEFAULT_VALUE = 0;

class Colour
{
    public:
        Colour()
            : R(DEFAULT_VALUE), G(DEFAULT_VALUE), B(DEFAULT_VALUE)
        { }

        Colour(int r, int g, int b)
            : R(static_cast<colour_t>(r)),
            G(static_cast<colour_t>(g)),
            B(static_cast<colour_t>(b))
        { }

        ~Colour()
        { }

        unsigned char R;
        unsigned char G;
        unsigned char B;
};

#endif // COLOUR_H_INCLUDED
