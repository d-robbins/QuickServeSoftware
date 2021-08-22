#include "qstable_manager.h"
#include "qssystem.h"
QSTableManager::QSTableManager(QSSystem* sys, wxPanel* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(500, 500))
{
	// TODO: Get the table layout from the system

	for (int i = 0; i < 10; i++) {
		//this->_buttons.push_back(new wxButton(this, wxID_ANY, std::to_string(i), wxPoint(0, i*50), wxSize(50, 50)));
		this->_tables.insert(std::pair<QSTable, wxButton*>(QSTable(), new wxButton(this, wxID_ANY, std::to_string(i), wxPoint(0, i * 50), wxSize(50, 50))));
	}

	this->Show();
}
