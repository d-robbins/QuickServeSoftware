#include "order.h"
#include "qssystem.h"

#include <algorithm>
#include <functional>
#include <string>
#include <cstdlib>

Order::Order(QSSystem* sys, User* usr, wxFrame* parent) : _sys(sys), _usr(usr), wxFrame(nullptr, wxID_ANY, "Create Order", wxDefaultPosition, wxSize(1280, 720))
{
	_main = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	_lhs = new wxPanel(_main, wxID_ANY);
	_rhs = new wxPanel(_main, wxID_ANY);
	_lhsbt = new wxPanel(_lhs, wxID_ANY);
	_lhstp = new wxPanel(_lhs, wxID_ANY);

	_return = new wxButton(_lhstp, ID_RETURN, "Return");
	Connect(ID_RETURN, wxEVT_BUTTON, wxCommandEventHandler(Order::OnReturnMain));
	
	_list = new wxListBox(_rhs, wxID_ANY, wxDefaultPosition, wxDefaultSize);

	auto _buttons_size = sys->GetMeals()->size();
	_buttons = new wxButton * [_buttons_size];
	wxGridSizer* gsizer = new wxGridSizer(_buttons_size / 2, _buttons_size / 2, 0, 0);

	for (int i = 0; i < _buttons_size; i++) {
		_button_ids.push_back((i + 10000));
		_buttons[i] = new wxButton(_lhsbt, (i + 10000), (*sys->GetMeals())[i].GetMealName());
		Connect(_button_ids.back(), wxEVT_BUTTON, wxCommandEventHandler(Order::OnAddItem));
		gsizer->Add(_buttons[i], 1, wxEXPAND | wxALL);
	}

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerlhs = new wxBoxSizer(wxVERTICAL);
	
	_lhsbt->SetSizer(gsizer);

	sizer->Add(_lhs, 1, wxEXPAND | wxALL);
	sizer->Add(_rhs, 1, wxEXPAND | wxALL);
	
	sizerlhs->Add(_lhstp, 1, wxEXPAND | wxALL);
	sizerlhs->Add(_lhsbt, 1, wxEXPAND | wxALL);

	_lhs->SetSizer(sizerlhs);
	_main->SetSizer(sizer);
	sizer->Layout();
	this->Show();
	Centre();
}

Order::~Order()
{
	for (int i = 0; i < _sys->GetMeals()->size(); i++) {
		delete _buttons[i];
	}

	delete[]_buttons;
}
void Order::CreateOrder()
{
	
}

void Order::OnReturnMain(wxCommandEvent& e)
{
	this->Close();
	_sys->GetMain()->Show();

	e.Skip();
}

void Order::OnAddItem(wxCommandEvent& e)
{
	wxArrayString ops;
	ops.Add("Add");
	ops.Add("Edit");
	wxSingleChoiceDialog* dlg = new wxSingleChoiceDialog(NULL, "", "Options", ops);
	dlg->ShowModal();
	if (dlg->GetStringSelection() == "Add") {
		this->_list->AppendString(((wxButton*)e.GetEventObject())->GetLabel());
	}
	else if (dlg->GetStringSelection() == "Edit") {
		wxMessageBox("Edit");
	}
	dlg->Destroy();
}

void Order::UpdatePreview()
{
}
