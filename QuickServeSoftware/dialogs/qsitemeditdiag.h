#pragma once

#include <wx/wx.h>
#include "../meal.h"
#include "../qssystem.h"

class QSItemEditDiag : public wxDialog
{
public:
	QSItemEditDiag(const wxString& title);
	~QSItemEditDiag() {}

	void IntializeEditor(std::pair<Meal, std::vector<std::string>>* item, QSSystem* sys);

	bool IsSuccess() { return _success; }

private:

	wxDECLARE_EVENT_TABLE();

	void OnListOptionsClick(wxCommandEvent& e);
	void OnListCurrentClick(wxCommandEvent& e);

	void OnSubmitClick(wxCommandEvent& e);
	void OnCancelClick(wxCommandEvent& e);

	wxListBox* _options = nullptr;
	wxListBox* _current_meal = nullptr;

	bool _success = false;

	QSSystem* _sys = nullptr;

	std::pair<Meal, std::vector<std::string>>* _editing = nullptr;

	// Main panel for dialog
	wxPanel* _main = nullptr;
};

