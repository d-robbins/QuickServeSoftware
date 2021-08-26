#include "qssystem.h"
#include "json.hpp"
#include "user.h"
#include "qsconsts.h"
#include <iostream>
#include <fstream>

using namespace nlohmann;

int QS_MEAL_SYS_ID = 0;

QSSystem::QSSystem(std::string inventory) : wxFrame(nullptr, wxID_ANY, "QS", wxDefaultPosition, wxSize(1280, 720)) {

	// BACKEND ----------------------------------------------------
	this->_inventory = std::make_shared<Inventory>(inventory);
	this->_meals = std::make_shared<std::vector<Meal>>();
	_menu = new wxMenuBar();

	ConfigureSystem();

	// FRONTEND ----------------------------------------------------

	_main = new wxPanel(this, wxID_ANY);
	_leftp = new wxPanel(_main, wxID_ANY);
	_rightp = new wxPanel(_main, wxID_ANY);
	
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	_table_manager = new QSTableManager(this, _main);
	sizer->Add(_table_manager, 1, wxEXPAND | wxALL, 10);
	sizer->Add(_rightp, 0, wxEXPAND | wxALL, 10);

	_main->SetSizer(sizer);
	sizer->Layout();
	
	_menu_edit_table = new wxMenu;
	_menu_edit_table->Append(qsc::ID_FILE_EDIT_TABLE, wxT("Configure Table Layout"));
	Connect(qsc::ID_FILE_EDIT_TABLE, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(QSSystem::OnToggleEditTables));
	_menu->Append(_menu_edit_table, wxT("File"));

	SetMenuBar(_menu);
	Centre();
	this->Show();
}

void QSSystem::OnToggleEditTables(wxCommandEvent& WXUNUSED(event))
{
	this->_table_manager->SetManagerState(QSTableManager::STATE::EDIT);
	//wxMessageBox("Click table to move then click location to move to");
}

void QSSystem::ConfigureSystem()
{
	std::ifstream in("rel.json");
	json j;
	in >> j;

	for (auto& el : j.items()) {
		assert(el.key() == "items");
		if (el.value().is_array()) {
			for (auto iter = el.value().begin(); iter != el.value().end(); ++iter) {
				if ((*iter).is_object()) {
					std::vector<std::string> items;
					std::string name, type;
					float price = 0.0;
					for (auto iiter = (*iter).begin(); iiter != (*iter).end(); ++iiter) {
						if (iiter.key() == "contains") {
							if (iiter.value().is_array()) {
								for (auto& obj : iiter.value()) {
									items.push_back(obj);
								}
							}
							else {
								std::cerr << "Incorrect format in json file at \"contains\" key\n";
							}
						}
						else if (iiter.key() == "name") {
							name = iiter.value();
						}
						else if (iiter.key() == "price") {
							price = (float)iiter.value();
						}
						else if (iiter.key() == "type") {
							type = iiter.value();
						}

					}
					this->_meals->push_back(Meal(items, price, name));
				}
			}
		}
	}
}
