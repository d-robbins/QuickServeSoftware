#include "qstable_manager.h"
#include "qssystem.h"
#include "qsconsts.h"
#include "qssystem.h"
#include "qssystemorder.h"
#include "dialogs/qsorderdiag.h"

QSTableManager::QSTableManager(QSSystem* sys, wxPanel* parent) : wxPanel(parent, qsc::ID_TABLE_MANAGER, wxDefaultPosition)
{
	_sys = sys;
	
	// TODO: Get the table layout from the system
	for (int i = 0; i < 10; i++) {

		// create the new table in the table manager
		this->_tables.push_back(new QSTable(i));
		
		// create a button for the table
		this->_table_buttons.push_back(new wxButton(this, qsc::ID_TABLE_CLICK, std::to_string(i), wxPoint(0, i * 50), wxSize(50, 50)));
		
		// connect the button up to its event handler
		Connect(qsc::ID_TABLE_CLICK, wxEVT_BUTTON, wxCommandEventHandler(QSTableManager::OnTableClick));
		this->_table_buttons.back()->SetClientData((void*)_tables.back());
	}

	Connect(qsc::ID_TABLE_MANAGER, wxEVT_LEFT_DOWN, wxCommandEventHandler(QSTableManager::OnClick));
	
	this->SetBackgroundColour(wxColour(148, 150, 150, 255));
	this->Show();
}

QSTableManager::~QSTableManager()
{
	for (int i = 0; i < _tables.size(); i++) {
		delete _tables[i];
	}
}

/**
 * When a table button is clicked
 */
void QSTableManager::OnTableClick(wxCommandEvent& e)
{
	_editing = (wxButton*)e.GetEventObject();

	switch (_state) {
	case STATE::EDIT:
		MoveButton();
		break;
	case STATE::NORMAL:
	default:
		// Create an Order
		auto* diag = new QSOrderDiag("Create Order");
		diag->SetSystem(_sys);
		diag->Centre();
		diag->ShowModal();
		diag->Destroy();
		
		//auto user = _sys->GetCurrentUser();

		auto label = ((wxButton*)e.GetEventObject())->GetLabel();
		
		// ensure that order was submitted successfully and meals were ordered
		if (diag->OrderSuccessful() && diag->GetMeals().size() > 0) {
			auto * table = (QSTable*)(((wxButton*)e.GetEventObject())->GetClientData());

			std::vector<Meal> order_meals;
			for (auto& p : diag->GetMeals()) {
				table->AddMeal(p->first);
				order_meals.push_back(p->first);
			}

			_sys->AddOrder(std::make_shared<QSSystemOrder>(std::to_string(table->GetID()), order_meals));
		}	
		
		break;
	}
}

/**
 * When the table manager wxPanel is clicked
 */
void QSTableManager::OnClick(wxCommandEvent& e)
{
	MoveButton();
}

void QSTableManager::MoveButton()
{
	if (_state == STATE::EDIT) {
		if (_editing != nullptr) {
			_editing->SetPosition(ScreenToClient(wxGetMousePosition() - (_editing->GetSize() / 2)));
		}
		else {
			wxMessageBox("Could not find table in <table, button> map!");
		}
	}
}

