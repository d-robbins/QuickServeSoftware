#include "qsitemeditdiag.h"
#include "qsconsts.h"


wxBEGIN_EVENT_TABLE(QSItemEditDiag, wxDialog)

EVT_LISTBOX_DCLICK(qsc::ID_OPTIONS_LIST, QSItemEditDiag::OnListOptionsClick)
EVT_LISTBOX_DCLICK(qsc::ID_CURRENT_LIST, QSItemEditDiag::OnListCurrentClick)

wxEND_EVENT_TABLE()


QSItemEditDiag::QSItemEditDiag(const wxString& title) : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(qsc::DIAG_W, qsc::DIAG_H))
{

}

void QSItemEditDiag::IntializeEditor(std::shared_ptr<std::pair<Meal, std::vector<std::string>>> item, QSSystem* sys)
{
	_sys = sys;
	_editing = item;
	this->_main = new wxPanel(this, wxID_ANY);
	
	_main->SetBackgroundColour(wxColour(148, 150, 150, 255));

	wxPanel* middle_panel = new wxPanel(_main, wxID_ANY);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* middle_sizer = new wxBoxSizer(wxVERTICAL);

	// listboxes for edit dialog
	_options = new wxListBox(_main, qsc::ID_OPTIONS_LIST);
	_current_meal = new wxListBox(_main, qsc::ID_CURRENT_LIST);
	
	// buttons for edit dialog
	wxButton* submit = new wxButton(middle_panel, qsc::ID_SUBMIT_EDITED, "Submit");
	Connect(qsc::ID_SUBMIT_EDITED, wxEVT_BUTTON, wxCommandEventHandler(QSItemEditDiag::OnSubmitClick));
	
	wxButton* cancel = new wxButton(middle_panel, qsc::ID_EDIT_CANCEL, "Cancel");
	Connect(qsc::ID_EDIT_CANCEL, wxEVT_BUTTON, wxCommandEventHandler(QSItemEditDiag::OnCancelClick));

	for (auto i : item->first.GetIngredients()) {
		_current_meal->AppendString(i);
	}

	for (auto i : _sys->GetInventoryItems()) {
		_options->AppendString(i.first.GetName());
	}

	middle_sizer->Add(submit, 1, wxEXPAND | wxALL, 10);
	middle_sizer->Add(cancel, 1, wxEXPAND | wxALL, 10);
	middle_panel->SetSizer(middle_sizer);

	sizer->Add(_options, 1, wxEXPAND | wxALL, 10);
	sizer->Add(middle_panel, 0, wxEXPAND | wxALL);
	sizer->Add(_current_meal, 1, wxEXPAND | wxALL, 10);
	_main->SetSizer(sizer);
}

/**
 * When the options list is double clicked
 */
void QSItemEditDiag::OnListOptionsClick(wxCommandEvent& e)
{
	wxString option_selected = ((wxListBox*)e.GetEventObject())->GetStringSelection();

	_current_meal->AppendString(option_selected);
}

/**
 * When the current ingredients list is double clicked
 */
void QSItemEditDiag::OnListCurrentClick(wxCommandEvent& e)
{
	wxString ingredient_selected = ((wxListBox*)e.GetEventObject())->GetStringSelection();
	int index = ((wxListBox*)e.GetEventObject())->GetSelection();
	((wxListBox*)e.GetEventObject())->Delete(index);
}

void QSItemEditDiag::OnSubmitClick(wxCommandEvent& e)
{
	this->_editing->first.ClearIngredients();

	for (auto i : _current_meal->GetStrings()) {
		_editing->first.AddIngredient(std::string(i));
	}

	this->_success = true;

	this->Close();
}

void QSItemEditDiag::OnCancelClick(wxCommandEvent& e)
{
	this->Close();
}
