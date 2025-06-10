#include "utils/file_resource_provider.h"
#include <wx/filesys.h>
#include <wx/artprov.h>
#include <wx/msgdlg.h>

FileResourceProvider::FileResourceProvider()
{
    wxString m_cwd = wxGetCwd();

#ifdef WIN32
    bool is_build_dir = m_cwd.EndsWith(wxT("Debug")) || m_cwd.EndsWith(wxT("Release"));
    m_cwd += (is_build_dir ? "/../../share/" : "/../share/");
#endif
    //wxMessageBox(m_cwd);
}

wxBitmap FileResourceProvider::GetBitmapFromFileRelPath(const wxString &rel_path)
{
    wxString full_path = m_cwd + rel_path;
    bool file_exists = wxFileExists(full_path);
    return file_exists ? wxBitmap(full_path, wxBITMAP_TYPE_ICO) : wxArtProvider::GetBitmap(wxART_ERROR);
}

wxBitmap FileResourceProvider::GetBitmapFromFileAbsPath(const wxString &abs_path)
{
    bool file_exists = wxFileExists(abs_path);
    return file_exists ? wxBitmap(abs_path, wxBITMAP_TYPE_ICO) : wxArtProvider::GetBitmap(wxART_ERROR);
}