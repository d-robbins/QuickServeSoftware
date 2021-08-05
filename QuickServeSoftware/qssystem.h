#pragma once

#include <wx/wx.h>

#include "inventory.h"
#include "order.h"
#include "meal.h"

#include <map>
#include <memory>
#include <vector>

const int ID_BEGINORDER = 1002;

const int BW = 10;
const int BH = 10;

class QSSystem : public wxFrame
{
public:
	enum class SYS_STATE { DEFAULT, BUILDING_ORDER };

	QSSystem(std::string inventory);
	~QSSystem() {}

	void Run();

	Order* GetQueuedOrder() { return _neworder; }

	std::shared_ptr<std::vector<Meal>> GetMeals() const { return this->_meals; }
	wxPanel* GetMain() { return _main; }
private:
	void OnCreateOrder(wxCommandEvent& e);
	wxPanel* _main = nullptr;
	Order* _neworder = nullptr;
	wxButton* _order = nullptr;

	wxButton** _buttons = nullptr;

private:
	void DefaultState();
	
	void ConfigureSystem();

	void ViewInventory() { _inventory->PrintItems(); }

	SYS_STATE _state = SYS_STATE::DEFAULT;
	std::shared_ptr<std::vector<Meal>> _meals;
	std::shared_ptr<Inventory> _inventory;
	std::vector<Order> _orders;
};