#ifndef AMADINA_APP_H_INCLUDED
#define AMADINA_APP_H_INCLUDED

#include <wx/app.h>

class AmadinaApp: public wxApp
{
    public:
        bool OnInit() override;
};

#endif // AMADINA_APP_H_INCLUDED
