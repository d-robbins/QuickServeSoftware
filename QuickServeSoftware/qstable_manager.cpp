#include "qstable_manager.h"
#include "qssystem.h"
#include "qsconsts.h"
QSTableManager::QSTableManager(QSSystem* sys, wxPanel* parent) : wxPanel(parent, qsc::ID_TABLE_MANAGER, wxDefaultPosition)
{
	// TODO: Get the table layout from the system
	for (int i = 0; i < 10; i++) {
		this->_tables.insert(std::pair<QSTable, wxButton*>
			(QSTable(i), new wxButton(this, 12008 + i, std::to_string(i), wxPoint(0, i * 50), wxSize(50, 50))));
		Connect(12008 + i, wxEVT_BUTTON, wxCommandEventHandler(QSTableManager::OnTableClick));
	}
	
	Connect(qsc::ID_TABLE_MANAGER, wxEVT_LEFT_DOWN, wxCommandEventHandler(QSTableManager::OnClick));
	
	this->SetBackgroundColour(wxColour(148, 150, 150, 255));
	this->Show();
}

void QSTableManager::OnTableClick(wxCommandEvent& e)
{
	_editing_id = ((wxButton*)e.GetEventObject())->GetLabel();

	if (_state == STATE::EDIT) {
		MoveButton();
	}
}

wxButton* QSTableManager::GetButtonFromId(std::string id)
{
	wxButton* found_button = nullptr;
	for (auto i = _tables.begin(); i != _tables.end(); ++i) {
		if (std::to_string(i->first.GetID()) == _editing_id) {
			found_button = i->second;
		}
	}

	return found_button;
}

void QSTableManager::OnClick(wxCommandEvent& e)
{
	
	MoveButton();
}

void QSTableManager::MoveButton()
{
	if (_state == STATE::EDIT) {
		wxButton* t = GetButtonFromId(_editing_id);

		if (t != nullptr) {
			t->SetPosition(ScreenToClient(wxGetMousePosition() - (t->GetSize() / 2)));
		}
		else {
			wxMessageBox("Could not find table in <table, button> map!");
		}
	}
}

