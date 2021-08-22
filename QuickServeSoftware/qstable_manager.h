#pragma once

#include <wx/wx.h>
#include <map>

#include "qstable.h"

class QSSystem;
class QSTableManager : public wxPanel
{
public:
	QSTableManager(QSSystem* sys, wxPanel* parent);
	~QSTableManager() {}

private:
	std::vector<QSTable> _active_tables;
	std::vector<wxButton*> _buttons;

	std::map<QSTable, wxButton*> _tables;
};

