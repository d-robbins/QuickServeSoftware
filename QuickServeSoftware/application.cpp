#include "application.h"

wxIMPLEMENT_APP(Application);

Application::Application()
{
}

Application::~Application()
{
}

bool Application::OnInit()
{
    _sys = new QSSystem("items.txt");
    _sys->Show();

    return true;
}
