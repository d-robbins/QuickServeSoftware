#include "qsorderdiag.h"

#include "../qsconsts.h"

#include "qsitemdiag.h"
#include "qsitemeditdiag.h"

wxBEGIN_EVENT_TABLE(QSOrderDiag, wxDialog)

EVT_LISTBOX_DCLICK(qsc::ID_PREVIEW, QSOrderDiag::OnPreviewDbl)

wxEND_EVENT_TABLE()

typedef std::pair<Meal, std::vector<std::string>> OrderData;

QSOrderDiag::QSOrderDiag(const wxString& title) :
	wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(qsc::DIAG_W, qsc::DIAG_H))
{
}

/**
 * Called when a meal is clicked
 * 
*/
void QSOrderDiag::OnAddItem(wxCommandEvent& e)
{
	// get the label from the button that was clicked
	auto label = ((wxButton*)e.GetEventObject())->GetLabel();

	// find the meal in the systems list of meals using the label
	auto to_edit = std::find_if(_sys->GetSystemMeals()->begin(), _sys->GetSystemMeals()->end(), [label](const Meal& m) {
		if (label == m.GetMealName()) {
			return true;
		}
		else {
			return false;
		}
		});

	// add a < meal , default_ingredients > pair to the order meal vector
	this->_meals_default_pair.push_back(std::make_shared<OrderData>(*to_edit, to_edit->GetIngredients()));

	// create the ItemOps dialog
	QSItemDiag* options = new QSItemDiag("Options");
	options->Centre();
	options->IntializeDiag(QSItemDiag::TYPE::UNADDED);

	if (options->ToAdd()) {
		// updating the preview with the recent addition to the meal list
		_preview->Append(_meals_default_pair.back()->first.GetMealName(), (void*)_meals_default_pair.back().get());
	}
	else if (options->ToEdit()) {
		// Meal is to be edited
		OrderData *meal_editing = _meals_default_pair.back().get();

		QSItemEditDiag* editor = new QSItemEditDiag("Edit Meal");
	
		editor->IntializeEditor(meal_editing, _sys);
		editor->Centre();
		editor->ShowModal();
		
		if (editor->IsSuccess()) {
			_preview->Append(_meals_default_pair.back()->first.GetMealName(), (void*)_meals_default_pair.back().get());
			for (auto i : _meals_default_pair.back()->first.GetOps()) {
				wxString str = "\t" + i.first + " " + i.second;
				_preview->AppendString(str);
			}
		}
		else {
			_meals_default_pair.pop_back();
		}

		editor->Destroy();
	}
	else if (options->ToAddMod()) {

	}
	else {
		// no selection was made so remove this meal from the list
		_meals_default_pair.pop_back();
	}
}

/**
 * Called when a meal is clicked in the preview ListBox
 */
void QSOrderDiag::OnPreviewDbl(wxCommandEvent& e)
{	
	// get the index of the ListBox selection
	int index = ((wxListBox*)e.GetEventObject())->GetSelection();
	
	if (_preview->GetClientData(index) != NULL || nullptr) {

		// get the OrderData pair from the list
		auto m = (OrderData*)_preview->GetClientData(index);

		QSItemDiag* options = new QSItemDiag("Options");
		options->Centre();
		options->IntializeDiag(QSItemDiag::TYPE::ADDED);

		if (options->ToRemove()) {
			int remove = 0;
			for (int i = 0; i < _meals_default_pair.size(); i++) {
				if (&(*_meals_default_pair[i].get()) == m) {
					remove = i;
					break;
				}
			}
		
			// clear the preview list box
			_preview->Clear();

			// erase the removed meal from the meal list
			_meals_default_pair.erase(_meals_default_pair.begin() + remove);
		
			// re-add all the other meals and their ops
			for (auto& i : _meals_default_pair) {
				_preview->Append(i->first.GetMealName(), (void*)(i.get()));
				for (auto j : i->first.GetOps()) {
					wxString str = "\t" + j.first + " " + j.second;
					_preview->AppendString(str);
				}
			}

		}
		else if (options->ToEdit()) {
			// Meal is to be edited
			OrderData *meal_editing = m;
			int current_op_index = meal_editing->first.GetOps().size();

			QSItemEditDiag* editor = new QSItemEditDiag("Edit Meal");
			editor->IntializeEditor(meal_editing, _sys);
			editor->Centre();
			editor->ShowModal();
		
			if (editor->IsSuccess()) {
				for (int i = current_op_index; i < _meals_default_pair.back()->first.GetOps().size(); i++) {
					wxString str = "\t" + _meals_default_pair.back()->first.GetOps()[i].first + " " + _meals_default_pair.back()->first.GetOps()[i].second;
					_preview->AppendString(str);
				}
			}

			editor->Destroy();
		}
		else if (options->ToAddMod()) {
		
		}
	}
}

void QSOrderDiag::OnSubmitOrder(wxCommandEvent& e)
{
	_success = true;
	this->Close();
}

QSOrderDiag::~QSOrderDiag()
{
	for (int i = 0; i < _sys->GetSystemMeals()->size(); i++) {
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
	_preview = new wxListBox(_rhstp, qsc::ID_PREVIEW, wxDefaultPosition);
	auto my_font = _preview->GetFont();
	my_font.SetPointSize(12);
	_preview->SetFont(my_font);

	auto _buttons_size = _sys->GetSystemMeals()->size();
	_buttons = new wxButton * [_buttons_size];
	wxGridSizer* gsizer = new wxGridSizer(_buttons_size / 2, _buttons_size / 2, 0, 0);

	// Intialize all the buttons needed for meals loaded in the system
	for (int i = 0; i < _buttons_size; i++) {
		int button_id = (i + 10000);
		_buttons[i] = new wxButton(_lhsbt, button_id, (*(_sys->GetSystemMeals()))[i].GetMealName());
		Connect(button_id, wxEVT_BUTTON, wxCommandEventHandler(QSOrderDiag::OnAddItem));
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

	_sizerrhstp->Add(_preview, 1, wxEXPAND | wxALL, 10);

	_rhstp->SetSizer(_sizerrhstp);
	_rhs->SetSizer(_rhssizer);
	_lhs->SetSizer(sizerlhs);
	_main->SetSizer(sizer);

	_sizerrhstp->Layout();
}
