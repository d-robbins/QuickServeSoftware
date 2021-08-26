#pragma once
#include <wx/wx.h>
#include <string>
#include "qssystem.h"
#include "meal.h"
#include "qsorderpreview.h"
#include <memory>

class QSOrderDiag : public wxDialog
{
public:
	QSOrderDiag(const wxString& title);
	~QSOrderDiag();
	
	std::string GetName() { return _name; }
	void SetSystem(QSSystem* s);

	wxListBox* GetPreview() { return _preview; }

private:
	void OnAddItem(wxCommandEvent& e);
	void OnPreviewDbl(wxCommandEvent& e);

	wxDECLARE_EVENT_TABLE();

	wxButton* _submit_order = nullptr;

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

	wxDialog* _dlg = nullptr;

	wxPanel* _main = nullptr;

	std::string _orderid;

	wxListBox* _preview = nullptr;

	// The default ingredients this meal gets
	std::vector<std::shared_ptr<std::pair<Meal, std::vector<std::string>>>> _meals_default_pair;
private:
	QSSystem* _sys = nullptr;
	std::string _name = "david";
};

