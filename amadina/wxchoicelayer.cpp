#include "wxchoicelayer.h"
#include <wx/bitmap.h>
#include <wx/dcmemory.h>

static const int BITMAP_SIZE = 16;

wxBEGIN_EVENT_TABLE(wxChoiceLayer, wxComboBox)
    EVT_COMBOBOX(wxID_ANY, wxChoiceLayer::OnChooseEvent)
wxEND_EVENT_TABLE()

wxChoiceLayer::wxChoiceLayer(wxWindow *parent, wxWindowID id)
        : wxBitmapComboBox(parent, id)
{ }

wxChoiceLayer::~wxChoiceLayer()
{ }

void wxChoiceLayer::SetReadOnly(void)
{
    long style = GetWindowStyleFlag() | wxCB_READONLY;
    SetWindowStyleFlag(style);
}

void wxChoiceLayer::AddLayers(const std::vector<Layer> &layers)
{
    Clear();
    for(std::vector<Layer>::const_iterator it=layers.begin(); it!=layers.end(); ++it)
    {
        Colour layer_colour = (*it).GetColour();
        // Create colored square
        wxBitmap bitmap;
        bitmap.Create(BITMAP_SIZE,BITMAP_SIZE);
        // Draw colored square
        wxMemoryDC memdc;
        memdc.SelectObject(bitmap);
        // Outer frame
        memdc.SetPen(wxPen(*wxWHITE));
        memdc.DrawRectangle(0,0,BITMAP_SIZE,BITMAP_SIZE);
        // Filled region
        memdc.SetPen(wxPen(*wxBLACK));
        memdc.SetBrush(wxBrush(wxColour(layer_colour.R, layer_colour.G, layer_colour.B)));
        memdc.DrawRectangle(1,1,BITMAP_SIZE-1,BITMAP_SIZE-1);
        Append((*it).GetName(), bitmap);
    }

    if(!wxItemContainerImmutable::IsEmpty())
        SetSelection(0);
}

void wxChoiceLayer::OnChooseEvent(wxCommandEvent &event)
{
    this->GetParent()->SetFocus();
}
