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
	~QSTableManager() {}

	void SetManagerState(STATE s) { _state = s; }

private:
	wxButton* GetButtonFromId(std::string id);
	void OnClick(wxCommandEvent& e);
	void MoveButton();
	void OnTableClick(wxCommandEvent& e);
	std::map< QSTable, wxButton*> _tables;
	STATE _state = STATE::NORMAL;
	std::string _editing_id = "";
};

