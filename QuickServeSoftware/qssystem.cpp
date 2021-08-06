#include "qssystem.h"
#include "json.hpp"
#include "user.h"

#include <iostream>
#include <fstream>

using namespace nlohmann;


QSSystem::QSSystem(std::string inventory) : wxFrame(nullptr, wxID_ANY, "QS", wxDefaultPosition, wxSize(1280, 720)) {

	// BACKEND ----------------------------------------------------
	this->_inventory = std::make_shared<Inventory>(inventory);
	this->_meals = std::make_shared<std::vector<Meal>>();

	ConfigureSystem();

	User david("david", "1");

	//Order o(this, &david);
	//o.CreateOrder();

	//Run();

	// FRONTEND ----------------------------------------------------

	_main = new wxPanel(this, wxID_ANY);

	_order = new wxButton(_main, ID_BEGINORDER, "Begin Order", wxPoint(50, 50), wxSize(150, 50));
	Connect(ID_BEGINORDER, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(QSSystem::OnCreateOrder));

	Centre();
}

void QSSystem::Run()
{
	switch (this->_state)
	{
	case SYS_STATE::DEFAULT:
		DefaultState();
		break;

	case SYS_STATE::BUILDING_ORDER:
		break;

	default:
		break;
	}
}

void QSSystem::OnCreateOrder(wxCommandEvent& e)
{
	//this->_main->Hide();
	User u("David", "1");

	_neworder = new Order(this, &u, this);
}

void QSSystem::DefaultState()
{
	
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
