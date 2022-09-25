#ifndef STRUCTURE_DRAWABLE_H_INCLUDED
#define STRUCTURE_DRAWABLE_H_INCLUDED

namespace cad
{
    namespace modeller
    {
        namespace structure
        {
            class Drawable
            {
                public:
                    virtual void Draw(void) = 0;
            };
        }
    }
}

#endif // STRUCTURE_DRAWABLE_H_INCLUDED
