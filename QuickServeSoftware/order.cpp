#include "order.h"
#include "qssystem.h"

#include <algorithm>
#include <functional>
#include <string>
#include <cstdlib>

const int CUR_INGREDIENTS = 12832;
const int PAST_INGREDIENTS = 12839;

wxBEGIN_EVENT_TABLE(Order, wxFrame)
	
EVT_LISTBOX_DCLICK(PAST_INGREDIENTS, Order::OnListClick)
EVT_LISTBOX_DCLICK(CUR_INGREDIENTS, Order::OnListClick)

wxEND_EVENT_TABLE()

Order::Order(QSSystem* sys, User* usr, wxFrame* parent) : _sys(sys), _usr(usr), wxFrame(nullptr, wxID_ANY, "Create Order", wxDefaultPosition, wxSize(1280, 720))
{
	_main = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	_lhs = new wxPanel(_main, wxID_ANY);
	_rhs = new wxPanel(_main, wxID_ANY);
	_lhsbt = new wxPanel(_lhs, wxID_ANY);
	_lhstp = new wxPanel(_lhs, wxID_ANY);
	_rhstp = new wxPanel(_rhs, wxID_ANY);

	_return = new wxButton(_lhstp, ID_RETURN, "Return");
	Connect(ID_RETURN, wxEVT_BUTTON, wxCommandEventHandler(Order::OnReturnMain));
	
	_list = new wxListBox(_rhstp, wxID_ANY, wxDefaultPosition);

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
	_rhssizer = new wxBoxSizer(wxVERTICAL);

	_lhsbt->SetSizer(gsizer);

	sizer->Add(_lhs, 1, wxEXPAND | wxALL);
	sizer->Add(_rhs, 1, wxEXPAND | wxALL);
	
	sizerlhs->Add(_lhstp, 1, wxEXPAND | wxALL);
	sizerlhs->Add(_lhsbt, 1, wxEXPAND | wxALL);

	_rhssizer->Add(_rhstp, 1, wxEXPAND | wxALL);
	_rhssizer->Layout();

	_rhs->SetSizer(_rhssizer);
	_lhs->SetSizer(sizerlhs);
	_main->SetSizer(sizer);

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
		auto* panel = new wxPanel(_rhs, -1, wxDefaultPosition);
		panel->SetBackgroundColour(wxColour(154, 177, 178));
		
		_rhssizer->Add(panel, 1, wxEXPAND | wxALL);
		_rhssizer->Layout();

		auto* sizer = new wxBoxSizer(wxHORIZONTAL);
		auto* lhspanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition);
		auto* rhspanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition);

		_available_ingredients = new wxListBox(lhspanel, PAST_INGREDIENTS, wxPoint(0, 20), wxSize(150, 300));
		_current_ingredients = new wxListBox(rhspanel, CUR_INGREDIENTS, wxPoint(0, 20), wxSize(150, 300));
		
		auto* lhstitle = new wxStaticText(lhspanel, wxID_ANY, "Available Ingredients", wxPoint(20, 0));
		auto items = _sys->GetInventoryItems();
		for (auto it = items.begin(); it != items.end(); ++it) {
			_available_ingredients->AppendString(it->first.GetName());
		}

		auto* rhstitle = new wxStaticText(rhspanel, wxID_ANY, "Current Ingredients", wxPoint(20, 0));

		auto label = ((wxButton*)e.GetEventObject())->GetLabel();
		auto to_edit = std::find_if(_sys->GetMeals()->begin(), _sys->GetMeals()->end(), [label](const Meal& m) {
			if (label == m.GetMealName()) {
				return true;
			}
			else {
				return false;
			}
			});

		if (to_edit == _sys->GetMeals()->end()) {
			wxMessageBox("Could not find item to edit!");
			dlg->Destroy();
			return;
		}
		else {
			for (const auto& i : to_edit->GetIngredients()) {
				_current_ingredients->AppendString(i);
			}
		}

		sizer->Add(lhspanel, 1);
		sizer->Add(rhspanel, 1);
		
		panel->SetSizer(sizer);
		panel->Layout();

		panel->Show();
	}
	dlg->Destroy();
}

void Order::OnListClick(wxCommandEvent& e)
{
	auto id = ((wxListBox*)e.GetEventObject())->GetId();
	if (id == PAST_INGREDIENTS) {
		_current_ingredients->AppendString(((wxListBox*)e.GetEventObject())->GetStringSelection());
	}
	else if (id == CUR_INGREDIENTS) {
		_available_ingredients->AppendString(((wxListBox*)e.GetEventObject())->GetStringSelection());
	}
	


	((wxListBox*)e.GetEventObject())->DeselectAll();
}
