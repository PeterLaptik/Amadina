#ifndef ART_H_INCLUDED
#define ART_H_INCLUDED

class wxBitmap;

namespace modeller {
    namespace art {

        enum Icons
        {
            ICO_VIEW_TOP,
            ICO_VIEW_LEFT,
            ICO_VIEW_BOTTOM,
            ICO_VIEW_RIGHT,
            ICO_VIEW_FRONT,
            ICO_VIEW_BACK,
            ICO_VIEW_ISO
        };

        wxBitmap get_icon(Icons icon);

    }
}

#endif // ART_H_INCLUDED
