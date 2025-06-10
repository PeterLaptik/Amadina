#ifndef FILE_RESOURCE_PROVIDER_INCLUDED_H
#define FILE_RESOURCE_PROVIDER_INCLUDED_H

#include <wx/string.h>
#include <wx/bitmap.h>

class FileResourceProvider final
{
    public:
        FileResourceProvider();

        ~FileResourceProvider() = default;

        wxBitmap GetBitmapFromFileRelPath(const wxString &rel_path);

        wxBitmap GetBitmapFromFileAbsPath(const wxString &abs_path);

    private:
        wxString m_cwd;
};

#endif

