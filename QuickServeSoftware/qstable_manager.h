#pragma once

#include <wx/wx.h>
#include <map>

#include "qstable.h"

class QSSystem;
class QSTableManager : public wxPanel
{
public:
	enum class STATE {NORMAL, EDIT};
	
	QSTableManager(QSSystem* sys, wxPanel* parent);
	~QSTableManager();

	void SetManagerState(STATE s) { _state = s; }

private:
	void OnClick(wxCommandEvent& e);
	void MoveButton();
	void OnTableClick(wxCommandEvent& e);

	QSSystem* _sys = nullptr;
	std::vector<wxButton*> _table_buttons;
	std::vector<QSTable*> _tables;

	wxButton* _editing = nullptr;

	STATE _state = STATE::NORMAL;
};

