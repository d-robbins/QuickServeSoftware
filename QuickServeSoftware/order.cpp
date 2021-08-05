#include "order.h"
#include "qssystem.h"

#include <algorithm>

Order::Order(QSSystem* sys, User* usr, wxFrame* parent) : _sys(sys), _usr(usr), wxFrame(nullptr, wxID_ANY, "Create Order", wxDefaultPosition, wxSize(1280, 720))
{
	_main = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	_lhs = new wxPanel(_main, wxID_ANY);
	_rhs = new wxPanel(_main, wxID_ANY);

	_return = new wxButton(_lhs, ID_RETURN, "Return");
	Connect(ID_RETURN, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Order::OnReturnMain));
	
	_list = new wxListBox(_rhs, wxID_ANY);

	auto _buttons_size = sys->GetMeals()->size();
	_buttons = new wxButton * [_buttons_size];
	wxGridSizer* gsizer = new wxGridSizer(_buttons_size / 2, _buttons_size / 2, 0, 0);

	for (int i = 0; i < _buttons_size; i++) {
		_buttons[i] = new wxButton(_lhs, wxID_ANY, (*sys->GetMeals())[i].GetMealName());
		gsizer->Add(_buttons[i], 1, wxEXPAND | wxALL);
	}

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	_lhs->SetSizer(gsizer);

	sizer->Add(_lhs, 1, wxEXPAND | wxALL);
	sizer->Add(_rhs, 1, wxEXPAND | wxALL);

	_main->SetSizer(sizer);

	this->Show();
	Centre();
}

void Order::CreateOrder()
{
	// Get table # from usr

	std::shared_ptr<std::vector<Meal>> meals;
	if (_sys != nullptr) {
		meals = _sys->GetMeals();
	}
	else {
		std::cerr << "This order is not registered with the system!\n";
		return;
	}

	bool done = false;
	while (!done) {
		std::cout << "Select Meal To Add To Order\n";
		for (int i = 0; i < meals->size(); i++) {
			printf("%d: %s\n", i + 1, (*meals)[i].GetMealName().c_str());
		}
		int selection;
		char a;
		std::cin >> selection;
		Meal m = (*meals)[selection - 1];

		// Would we like to edit this before adding it?
		std::cout << "Would you like to edit this meal? (y/n)\n";
		std::cin >> a;
		if (a == 'y') {

			bool edit = true;
			while (edit)
			{
				std::cout << m.GetMealName() << std::endl;
				m.DisplayIngredients();
				std::cout << "remove, add, or cancel? (r/a/c): ";
				std::cin >> a;
				switch (a) {
				case 'r':
					std::cout << "please enter index to edit: ";
					std::cin >> selection;
					--selection;

					m.DeleteIngredient(selection);
					break;
				case 'a':

					break;
				case 'c':
				default:
					edit = false;
					break;
				}

				std::cout << "Continue editing? (y/n): ";
				std::cin >> a;
				if (a == 'n') {
					edit = false;
				}
			}
		}

		std::cout << "Adding " << m.GetMealName() << " to order!\n";
		m.DisplayIngredients();

		std::cout << "Continue? (y/n): ";
		std::cin >> a;
		if (a == 'n') {
			done = true;
		}
	}
}

void Order::OnReturnMain(wxCommandEvent& e)
{
	this->Close();
	_sys->GetMain()->Show();

	e.Skip();
}

void Order::OnAddCajun(wxCommandEvent& e)
{
	std::string name = "Cajun Wrap";
	auto m = std::find_if((*_sys->GetMeals()).begin(), (*_sys->GetMeals()).end(), [name](const Meal& m) {
		if (m.GetMealName() == name) {
			return true;
		}
		else {
			return false;
		}
		});

	if (m != (*_sys->GetMeals()).end()) {
		this->_components.push_back(*m);
		UpdatePreview();
	}

	e.Skip();
}

void Order::UpdatePreview()
{
}
