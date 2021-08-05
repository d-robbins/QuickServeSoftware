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
	~Order() {}

	void CreateOrder();

	wxSizer* QSGetSizer() { return this->GetSizer(); }

private:
	void OnReturnMain(wxCommandEvent& e);
	void OnAddCajun(wxCommandEvent& e);
	void UpdatePreview();

	wxButton* _return = nullptr;
	wxListBox* _list = nullptr;

	wxPanel* _lhs = nullptr;
	wxPanel* _rhs = nullptr;

	wxButton**_buttons = nullptr;

	wxPanel* _main = nullptr;
	std::string _orderid;
	std::vector<Meal> _components;

	QSSystem* _sys = nullptr;
	User* _usr = nullptr;
};



