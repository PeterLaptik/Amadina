#ifndef WXCHOICELAYER_H
#define WXCHOICELAYER_H

#include <wx/bmpcbox.h>
#include <vector>
#include "../../amadin/kernel/entities/layer.h"

// Combo box for selecting layers
class wxChoiceLayer : public wxBitmapComboBox
{
    public:
        wxChoiceLayer(wxWindow *parent, wxWindowID id);
        virtual ~wxChoiceLayer();

        void SetReadOnly(void);

        // Fill combo box values with layers from list
        void AddLayers(const std::vector<Layer> &layers);

    protected:
        void OnChooseEvent(wxCommandEvent &event);

    private:
        DECLARE_EVENT_TABLE()
};

#endif // WXCHOICELAYER_H
