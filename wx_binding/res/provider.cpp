#include "provider.h"
#include <wx/artprov.h>
#include <wx/mstream.h>
#include "icons.h"

wxBitmap create_image(const unsigned char *data, int size);

wxBitmap get_icon(ICONS icon)
{
    wxBitmap no_bitmap = wxArtProvider::GetBitmap(wxART_QUESTION);

    switch(icon)
    {
        case ICON_POINT:
            return create_image(icon_point_ico, icon_point_ico_size);
        case ICON_LINE:
            return create_image(icon_line_ico, icon_line_ico_size);
        case ICON_CIRCLE:
            return create_image(icon_circle_ico, icon_circle_ico_size);
        case ICON_DELETE:
            break;
    }

    return no_bitmap;
}

wxBitmap create_image(const unsigned char *data, int size)
{
    wxMemoryInputStream inStream (data, size);
    wxImage img(inStream, wxBITMAP_TYPE_ICO);
    return wxBitmap(img);
}
