#include "provider.h"
#include <wx/artprov.h>
#include <wx/mstream.h>
#include "icons.h"

// Creates bitmap from raw array
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
            return create_image(icon_delete_ico, icon_delete_ico_size);
        case ICON_COPY:
            return create_image(icon_copy_ico, icon_copy_ico_size);
        case ICON_MOVE:
            return create_image(icon_move_ico, icon_move_ico_size);
        case ICON_CUT:
            return create_image(icon_cut_ico, icon_cut_ico_size);
        case ICON_PASTE:
            return create_image(icon_paste_ico, icon_paste_ico_size);
        case ICON_ARC_CENTER:
            return create_image(icon_arc_center_ico, icon_arc_center_ico_size);
        case ICON_ARC_POINTS:
            return create_image(icon_arc_pt_ico, icon_arc_pt_ico_size);
        case ICON_CIRCLE_POINTS:
            return create_image(icon_circle_3p_ico, icon_circle_3p_ico_size);
        case ICON_ELLIPCE:
            return create_image(icon_ellipse_ico, icon_ellipse_ico_size);
    }

    return no_bitmap;
}

wxBitmap create_image(const unsigned char *data, int size)
{
    wxMemoryInputStream inStream (data, size);
    wxImage img(inStream, wxBITMAP_TYPE_ICO);
    return wxBitmap(img);
}
