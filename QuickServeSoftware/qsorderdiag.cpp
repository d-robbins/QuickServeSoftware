#include "qsorderdiag.h"
#include "qsconsts.h"

#include "qssystem.h"

wxBEGIN_EVENT_TABLE(QSOrderDiag, wxDialog)

EVT_LISTBOX_DCLICK(qsc::ID_EDIT_AVAIL_INGREDIENTS, QSOrderDiag::OnListClick)
EVT_LISTBOX_DCLICK(qsc::ID_EDIT_CURRENT_INGREDIENTS, QSOrderDiag::OnListClick)
EVT_LISTBOX_DCLICK(qsc::ID_EDIT_PREVIEW, QSOrderDiag::OnPreviewListDblClick)

wxEND_EVENT_TABLE()

QSOrderDiag::QSOrderDiag(const wxString& title) :
	wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(1280, 720))
{
	
}

void QSOrderDiag::OnSubmitOrder(wxCommandEvent& e)
{
	
}

void QSOrderDiag::OnAddItem(wxCommandEvent& e)
{
	wxArrayString ops;
	ops.Add("Add");
	ops.Add("Edit");
	wxSingleChoiceDialog* dlg = new wxSingleChoiceDialog(NULL, "", "Options", ops);
	dlg->ShowModal();
	if (dlg->GetStringSelection() == "Add") {
		auto label = ((wxButton*)e.GetEventObject())->GetLabel();
		auto to_edit = std::find_if(_sys->GetMeals()->begin(), _sys->GetMeals()->end(), [label](const Meal& m) {
			if (label == m.GetMealName()) {
				return true;
			}
			else {
				return false;
			}
			});
		if (to_edit != _sys->GetMeals()->end()) {
			Meal m = *to_edit;
			m.SetMealSystemID(_sys->GetNextSysMealID());
			this->_meals_default_pair.push_back(std::pair<Meal, std::vector<std::string>>(m, m.GetIngredients()));
			this->_list->AppendString(((wxButton*)e.GetEventObject())->GetLabel());
		}
	}
	else if (dlg->GetStringSelection() == "Edit") {
		EditItem(((wxButton*)e.GetEventObject())->GetLabel(), dlg, nullptr);
	}
	dlg->Destroy();
}

void QSOrderDiag::OnListClick(wxCommandEvent& e)
{
	auto id = ((wxListBox*)e.GetEventObject())->GetId();
	if (id == qsc::ID_EDIT_AVAIL_INGREDIENTS) {
		_current_ingredients->AppendString(((wxListBox*)e.GetEventObject())->GetStringSelection());

	}
	else if (id == qsc::ID_EDIT_CURRENT_INGREDIENTS) {

		bool found = false;
		for (const auto& i : _available_ingredients->GetStrings()) {
			if (i == ((wxListBox*)e.GetEventObject())->GetStringSelection()) {
				found = true;
			}
		}

		if (!found) {
			_available_ingredients->AppendString(((wxListBox*)e.GetEventObject())->GetStringSelection());
		}

		int loc = 0;
		for (int i = 0; i < _current_ingredients->GetStrings().size(); i++) {
			if ((_current_ingredients->GetStrings())[i]
				== ((wxListBox*)e.GetEventObject())->GetStringSelection()) {
				loc = i;
			}
		}
		_current_ingredients->Delete(loc);
		_current_ingredients->Refresh();
	}

	((wxListBox*)e.GetEventObject())->DeselectAll();
}

void QSOrderDiag::OnSubmitEdit(wxCommandEvent& e)
{
	Meal meal;
	for (const auto& i : _current_ingredients->GetStrings()) {
		meal.AddIngredient(std::string(i.c_str()));
	}

	if (_edited_title != "") {
		_list->AppendString(_edited_title + wxString(" Edited"));
	}

	meal.SetMealSystemID(_sys->GetNextSysMealID());

	meal.SetMealName(std::string(_edited_title.c_str()));
	//_meals.push_back(meal);

	_edit_panel->Destroy();
	_edit_panel = nullptr;
	this->Refresh();
}

void QSOrderDiag::OnPreviewListDblClick(wxCommandEvent& e)
{
	wxArrayString ops;
	ops.Add("Edit");
	ops.Add("Remove");
	wxSingleChoiceDialog* dlg = new wxSingleChoiceDialog(NULL, "", "Options", ops);
	dlg->ShowModal();
	if (dlg->GetStringSelection() == "Edit") {
		int to_edit = ((wxListBox*)e.GetEventObject())->GetSelection();
		if (to_edit < _meals_default_pair.size()) {
			// Relying on preview order for _meals vector order
			// If we remove items from preview this will cause problems
			// FIX
			auto* m = &_meals_default_pair[to_edit].first;
			_current_editing = m->GetSysID();
			EditItem(m->GetMealName(), nullptr, m);
		}
		else {
			wxMessageBox("Couldn't find meal to edit!");
		}
	}
	else if (dlg->GetStringSelection() == "Remove") {
		wxMessageBox("Implement Me!");
	}


}

void QSOrderDiag::OnSubmitSave(wxCommandEvent& e)
{
	if (_current_editing != -1) {
		auto t = _current_editing;
		/*auto meal = std::find_if(_meals.begin(), _meals.end(), [t](const Meal& m) {
			if (t == m.GetSysID()) {
				return true;
			}
			else {
				return false;
			}
			});*/

		Meal* meal = nullptr;
		for (auto it = _meals_default_pair.begin(); it != _meals_default_pair.end(); ++it) {
			if (it->first.GetSysID() == t) {
				meal = &it->first;
				break;
			}
		}

		if (meal != nullptr) {
			(*meal).ClearIngredients();
			for (const auto& i : _current_ingredients->GetStrings()) {
				(*meal).AddIngredient(std::string(i.c_str()));
			}
		}
	}

	_current_editing = -1;
	_edit_panel->Destroy();
	_edit_panel = nullptr;
}

void QSOrderDiag::EditItem(wxString itemName, wxDialog* dlg, Meal* m)
{
	// So we dont edit 2 orders at once... future feature maybe?
	if (_edit_panel != nullptr) {
		_edit_panel->Destroy();
	}

	_edit_panel = new wxPanel(_rhs, -1, wxDefaultPosition);
	//_edit_panel->SetBackgroundColour(wxColour(154, 177, 178));

	_rhssizer->Add(_edit_panel, 1, wxEXPAND | wxALL);
	_rhssizer->Layout();

	auto* sizer = new wxBoxSizer(wxHORIZONTAL);
	auto* lhspanel = new wxPanel(_edit_panel, wxID_ANY, wxDefaultPosition);
	auto* rhspanel = new wxPanel(_edit_panel, wxID_ANY, wxDefaultPosition);

	// Available and current ingredients of edited items
	_available_ingredients = new wxListBox(lhspanel, qsc::ID_EDIT_AVAIL_INGREDIENTS, wxPoint(0, 20), wxSize(150, 300));
	_current_ingredients = new wxListBox(rhspanel, qsc::ID_EDIT_CURRENT_INGREDIENTS, wxPoint(0, 20), wxSize(150, 300));

	auto* lhstitle = new wxStaticText(lhspanel, wxID_ANY, "Available Ingredients", wxPoint(20, 0));
	auto items = _sys->GetInventoryItems();

	// Get items from the systems inventory and add it to the available toppings for meals
	for (auto it = items.begin(); it != items.end(); ++it) {
		_available_ingredients->AppendString(it->first.GetName());
	}

	auto* rhstitle = new wxStaticText(rhspanel, wxID_ANY, "Current Ingredients", wxPoint(70, 0));

	auto f = itemName;

	auto* rhsediting = new wxStaticText(lhspanel, wxID_ANY, "Editing:\n" + itemName, wxPoint(200, 0));

	auto* editsubmit = new wxButton(lhspanel, qsc::ID_SUBMIT_EDITED, "Submit", wxPoint(200, 50));

	if (m == nullptr) {
		Connect(qsc::ID_SUBMIT_EDITED, wxEVT_BUTTON, wxCommandEventHandler(QSOrderDiag::OnSubmitEdit));
	}
	else {
		editsubmit->SetId(qsc::ID_SAVE_PREVIEW_EDIT);
		editsubmit->SetLabel("Save Edits");
		Connect(qsc::ID_SAVE_PREVIEW_EDIT, wxEVT_BUTTON, wxCommandEventHandler(QSOrderDiag::OnSubmitSave));
	}

	_edited_title = itemName;

	auto label = itemName;

	if (m == nullptr) {
		// Find the actual meal that we want to edit (so we have the current ingredients)
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
	}
	else {
		for (const auto& i : m->GetIngredients()) {
			_current_ingredients->AppendString(i);
		}
	}

	sizer->Add(lhspanel, 1);
	sizer->Add(rhspanel, 1);

	_edit_panel->SetSizer(sizer);
	_edit_panel->Layout();

	_edit_panel->Show();
}

QSOrderDiag::~QSOrderDiag()
{
	for (int i = 0; i < _sys->GetMeals()->size(); i++) {
		delete _buttons[i];
	}

	delete[]_buttons;
}

void QSOrderDiag::SetSystem(QSSystem* s)
{
	_sys = s; 
	// Create all the panels that we need for the order creation
	_main = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	_lhs = new wxPanel(_main, wxID_ANY);
	_rhs = new wxPanel(_main, wxID_ANY);
	_lhsbt = new wxPanel(_lhs, wxID_ANY);
	_lhstp = new wxPanel(_lhs, wxID_ANY);
	_rhstp = new wxPanel(_rhs, wxID_ANY);

	auto* lefttopsizer = new wxBoxSizer(wxHORIZONTAL);
	_submit_order = new wxButton(_lhstp, qsc::ID_SUBMIT_ORDER, "Submit Order", wxDefaultPosition);
	Connect(qsc::ID_SUBMIT_ORDER, wxEVT_BUTTON, wxCommandEventHandler(QSOrderDiag::OnSubmitOrder));
	lefttopsizer->Add(_submit_order, 1, wxEXPAND | wxALL | wxRIGHT, 5);
	_lhstp->SetSizer(lefttopsizer);
	
	_sizerrhstp = new wxBoxSizer(wxHORIZONTAL);
	_list = new wxListBox(_rhstp, qsc::ID_EDIT_PREVIEW, wxDefaultPosition, wxSize(640, 320));

	auto _buttons_size = _sys->GetMeals()->size();
	_buttons = new wxButton * [_buttons_size];
	wxGridSizer* gsizer = new wxGridSizer(_buttons_size / 2, _buttons_size / 2, 0, 0);

	// Intialize all the buttons needed for meals loaded in the system
	for (int i = 0; i < _buttons_size; i++) {
		_button_ids.push_back((i + 10000));
		_buttons[i] = new wxButton(_lhsbt, (i + 10000), (*(_sys->GetMeals()))[i].GetMealName());
		Connect(_button_ids.back(), wxEVT_BUTTON, wxCommandEventHandler(QSOrderDiag::OnAddItem));
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

	_sizerrhstp->Add(_list, 1, wxEXPAND | wxALL, 10);
	_rhstp->SetSizer(_sizerrhstp);

	_rhs->SetSizer(_rhssizer);
	_lhs->SetSizer(sizerlhs);
	_main->SetSizer(sizer);

	_sizerrhstp->Layout();
}
