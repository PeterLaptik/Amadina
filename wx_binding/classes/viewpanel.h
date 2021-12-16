#ifndef VIEWPANEL_H_INCLUDED
#define VIEWPANEL_H_INCLUDED

#include <wx/panel.h>
#include <thread>
#include "view_2d/screen.h"
#include "context/context.h"

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

class ScreenInterface;
class DrawManager;
class Command;

///\brief Drawing panel implementation for wxWidgets GUI-library.
class DLL_EXPORT ViewPanel: public wxPanel, private Screen
{
    public:
        ///\brief Constructor
        ///\param parent - parent window
        ///\param pos - default panel position
        ///\param size - panel size
        ///\param style - panel style (see wxWidgets documentation)
        ///\param name - panel name
        ViewPanel(wxWindow *parent,
                    wxWindowID winid = wxID_ANY,
                    const wxPoint &pos = wxDefaultPosition,
                    const wxSize &size = wxDefaultSize,
                    long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                    const wxString &name = wxPanelNameStr);

        ///\brief Destructor
        virtual ~ViewPanel();

        void AssignCommand(Command *cmd);

        ///\brief Cancels current command execution.
        /// The method has to be called on escape-button clicked
        /// (or other specific events)
        void CancelCommand(void);

        ///\brief Deletes current entities selection.
        /// The method has to be called on delete-button clicked
        /// (or other specific events)
        void DeleteSelection(void);

        ///\brief Creates new entity on drawing
        /// using appropriate builder instance
        ///\param builder - builder instance
        ///\see AbstractBuilder
        void CreateEntityByPoints(AbstractBuilder *builder);

        /// Sets panel background colour
        ///\param colour - colour value
        virtual bool SetBackgroundColour(const wxColour &colour);

        virtual void ScreenRefresh(void);
        //
        // TODO
        // Remove draw manager getter:
        // Command executions have to work through Screen implementation
        //
        DrawManager* GetDrawManager(void);

        Context* GetContext(void)
        {
            return Screen::GetContext();
        }

    protected:
        // Event handlers
        void OnPaint(wxPaintEvent &event);
        void OnResize(wxSizeEvent &event);
        void OnMouseMove(wxMouseEvent &event);
        void OnMouseLeftButtonDown(wxMouseEvent &event);
        void OnMouseLeftButtonUp(wxMouseEvent &event);
        void OnMouseWheel(wxMouseEvent &event);
        void OnMouseWheelDown(wxMouseEvent &event);
        void OnMouseWheelUp(wxMouseEvent &event);
        void OnMouseEnterPanel(wxMouseEvent &event);
        void OnMouseLeavePanel(wxMouseEvent &event);

    private:
        /// Add several shapes for testing (test mode)
        void AddTestShapes(void);
        void ShowCursor(wxDC &dc);

        Command *m_current_command;
        std::thread *m_cmd_thread;;

        // Screen interface implementation
        //ScreenInterface *m_screen_impl;

    wxDECLARE_EVENT_TABLE();
};

#endif // VIEWPANEL_H_INCLUDED
