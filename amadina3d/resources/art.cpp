#include "art.h"
#include "icons.h"
#include <wx/mstream.h>
#include <wx/artprov.h>

wxBitmap create_image(const unsigned char *data, int size);

wxBitmap modeller::art::get_icon(Icon icon)
{
    switch(icon)
    {
        case ICO_VIEW_BACK:
            return create_image(cube_back_ico, cube_back_ico_size);
        case ICO_VIEW_FRONT:
            return create_image(cube_front_ico, cube_front_ico_size);
        case ICO_VIEW_LEFT:
            create_image(cube_left_ico, cube_left_ico_size);
        case ICO_VIEW_RIGHT:
            create_image(cube_right_ico, cube_right_ico_size);
        case ICO_VIEW_TOP:
            return create_image(cube_top_ico, cube_top_ico_size);
        case ICO_VIEW_BOTTOM:
            return create_image(cube_bottom_ico, cube_bottom_ico_size);
    }
    return wxArtProvider::GetBitmap(wxART_QUESTION);
}

wxBitmap create_image(const unsigned char *data, int size)
{
    wxMemoryInputStream inStream (data, size);
    wxImage img(inStream, wxBITMAP_TYPE_ICO);
    return wxBitmap(img);
}
