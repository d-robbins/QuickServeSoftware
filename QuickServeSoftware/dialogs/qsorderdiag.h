#pragma once
#include <wx/wx.h>
#include <string>
#include <memory>

#include "../qssystem.h"
#include "../meal.h"

typedef std::shared_ptr<std::pair<Meal, std::vector<std::string>>> MealDefaultPair;

/**
 * Class to handle order creation
 */
class QSOrderDiag : public wxDialog
{
public:
	QSOrderDiag(const wxString& title);
	~QSOrderDiag();
	
	std::string GetName() { return _name; }
	void SetSystem(QSSystem* s);

	bool OrderSuccessful() { return _success; }

	wxListBox* GetPreview() { return _preview; }

	std::vector<MealDefaultPair> GetMeals() { return _meals_default_pair; }

private:
	void OnAddItem(wxCommandEvent& e);
	void OnPreviewDbl(wxCommandEvent& e);
	void OnSubmitOrder(wxCommandEvent& e);

	wxDECLARE_EVENT_TABLE();

	// Order Creation UI

	wxBoxSizer* _sizerrhstp = nullptr;
	wxBoxSizer* _rhssizer = nullptr;

	wxPanel* _main = nullptr;

	// left side
	wxPanel* _lhs = nullptr;
	
	// left side bottom and top
	wxPanel* _lhsbt = nullptr;
	wxPanel* _lhstp = nullptr;

	// right side and right top
	wxPanel* _rhs = nullptr;
	wxPanel* _rhstp = nullptr;

	wxButton** _buttons = nullptr;
	wxButton* _submit_order = nullptr;

	wxListBox* _preview = nullptr;

	// ---------------------------

private:
	QSSystem* _sys = nullptr;
	std::string _name = "david";
	bool _success = false;

	// The default ingredients this meal gets
	std::vector<MealDefaultPair> _meals_default_pair;
};

