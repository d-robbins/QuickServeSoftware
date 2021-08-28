#pragma once

#include <wx/wx.h>

#include "inventory.h"
#include "meal.h"
#include "qstable_manager.h"
#include "user.h"
#include "qssystemorder.h"

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
	enum class ITEM_MODIFIERS {ENTREE, APPETITIZER};

	QSSystem(std::string inventory);
	~QSSystem() { }

	std::shared_ptr<std::vector<Meal>> GetSystemMeals() const { return this->_meals; }
	std::map<Item, int> GetStock() const { return this->_stock->GetItems(); }

	QSUser GetCurrentUser() { return QSUser("David", "1"); }
	void AddOrder(std::shared_ptr<QSSystemOrder> order);

private:
	wxPanel* _main = nullptr;
	wxPanel* _leftp = nullptr;
	wxPanel* _rightp = nullptr;

	wxMenuBar* _menu = nullptr;
	wxMenu* _menu_edit_table = nullptr;
	wxButton* _order = nullptr;

private:
	QSTableManager *_table_manager = nullptr;

private:	
	void OnToggleEditTables(wxCommandEvent& e);
	void ConfigureSystem();
	void ViewInventory() { _stock->PrintItems(); }

	SYS_STATE _state = SYS_STATE::DEFAULT;

	std::vector<std::shared_ptr<QSSystemOrder>> _orders;
	std::shared_ptr<std::vector<Meal>> _meals;
	std::shared_ptr<Inventory> _stock;
};