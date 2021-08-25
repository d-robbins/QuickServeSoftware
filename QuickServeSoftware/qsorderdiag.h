#pragma once
#include <wx/wx.h>
#include <string>
#include "qssystem.h"
#include "meal.h"
class QSOrderDiag : public wxDialog
{
public:
	QSOrderDiag(const wxString& title);
	~QSOrderDiag();
	
	std::string GetName() { return _name; }
	void SetSystem(QSSystem* s);
	//std::vector<Meal> GetOrderMeals() { return _meals; }

private:
	void OnSubmitOrder(wxCommandEvent& e);
	void OnAddItem(wxCommandEvent& e);
	void OnListClick(wxCommandEvent& e);
	void OnSubmitEdit(wxCommandEvent& e);
	void OnPreviewListDblClick(wxCommandEvent& e);
	void OnSubmitSave(wxCommandEvent& e);

	wxDECLARE_EVENT_TABLE();

	void EditItem(wxString, wxDialog*, Meal* m);

	wxButton* _submit_order = nullptr;
	wxListBox* _list = nullptr;

	// Create Order Menu

	wxBoxSizer* _sizerrhstp = nullptr;
	wxPanel* _lhs = nullptr;
	wxPanel* _lhsbt = nullptr;
	wxPanel* _lhstp = nullptr;
	wxPanel* _rhs = nullptr;
	wxPanel* _rhstp = nullptr;

	// ---------------------------

	wxButton** _buttons = nullptr;
	std::vector<int> _button_ids;
	wxBoxSizer* _rhssizer = nullptr;

	wxListBox* _available_ingredients = nullptr;
	wxListBox* _current_ingredients = nullptr;

	wxPanel* _edit_panel = nullptr;
	//std::vector<Meal> _meals;
	wxDialog* _dlg = nullptr;

	wxPanel* _main = nullptr;
	wxString _edited_title = "";

	std::string _orderid;

	int _current_editing = -1;

	// The default ingredients this meal gets
	std::vector<std::pair<Meal, std::vector<std::string>>> _meals_default_pair;
private:
	QSSystem* _sys = nullptr;
	std::string _name = "david";
};

