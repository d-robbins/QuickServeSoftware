#pragma once

#include "user.h"
#include "meal.h"

#include <wx/wx.h>

#include <string>
#include <vector>

class QSSystem;

/**
 * Class to handle placing orders
 */
class Order : wxFrame
{
public:
	enum class TYPE {DEFUALT, PRIORITY, ENTRE, APPETIZER};

	Order(QSSystem* sys, User* usr, wxFrame* parent);
	~Order();

	void CreateOrder();

	wxButton** GetButtons() { return _buttons; }

	wxSizer* QSGetSizer() { return this->GetSizer(); }

	wxDECLARE_EVENT_TABLE();

private:
	void OnReturnMain(wxCommandEvent& e);
	void OnAddItem(wxCommandEvent& e);
	void OnListClick(wxCommandEvent& e);
	void OnSubmitEdit(wxCommandEvent& e);
	void OnPreviewListDblClick(wxCommandEvent& e);
	void OnSubmitSave(wxCommandEvent& e);

	void EditItem(wxString, wxDialog*, Meal* m);

	wxButton* _return = nullptr;
	wxListBox* _list = nullptr;

	// Create Order Menu

	wxBoxSizer* _sizerrhstp = nullptr;
	wxPanel* _lhs = nullptr;
	wxPanel* _lhsbt = nullptr;
	wxPanel* _lhstp = nullptr;
	wxPanel* _rhs = nullptr;
	wxPanel* _rhstp = nullptr;

	// ---------------------------

	wxButton**_buttons = nullptr;
	std::vector<int> _button_ids;
	wxBoxSizer* _rhssizer = nullptr;

	wxListBox* _available_ingredients = nullptr;
	wxListBox* _current_ingredients = nullptr;

	wxPanel* _edit_panel = nullptr;

	wxDialog* _dlg = nullptr;

	wxPanel* _main = nullptr;
	wxString _edited_title = "";

	std::string _orderid;

	int _current_editing = -1;

	QSSystem* _sys = nullptr;
	User* _usr = nullptr;
	std::vector<Meal> _meals;
};



