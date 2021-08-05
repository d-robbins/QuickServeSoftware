#pragma once

#include <wx/wx.h>

#include "qssystem.h"

class Application : public wxApp
{
public:
	Application();
	~Application();

	bool OnInit();

private:
	QSSystem* _sys = nullptr;
};

