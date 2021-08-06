#pragma once

#include "user.h"
#include "meal.h"

#include <wx/wx.h>

#include <string>
#include <vector>

const int ID_RETURN = 1003;
const int ID_CAJUN = 1004;

class QSSystem;
class Order : wxFrame
{
public:
	enum class TYPE {DEFUALT, PRIORITY, ENTRE, APPETIZER};

	Order(QSSystem* sys, User* usr, wxFrame* parent);
	~Order();

	void CreateOrder();

	wxButton** GetButtons() { return _buttons; }

	wxSizer* QSGetSizer() { return this->GetSizer(); }

private:
	void OnReturnMain(wxCommandEvent& e);
	void OnAddItem(wxCommandEvent& e);
	void UpdatePreview();

	wxButton* _return = nullptr;
	wxListBox* _list = nullptr;

	wxPanel* _lhs = nullptr;
	wxPanel* _lhsbt = nullptr;
	wxPanel* _lhstp = nullptr;
	wxPanel* _rhs = nullptr;

	wxButton**_buttons = nullptr;
	std::vector<int> _button_ids;

	wxDialog* _dlg = nullptr;

	wxPanel* _main = nullptr;
	std::string _orderid;
	std::vector<Meal> _components;
	int _loi = 0;

	QSSystem* _sys = nullptr;
	User* _usr = nullptr;
};



