#include "qssystemorder.h"

QSSystemOrder::QSSystemOrder(std::string table, const std::vector<Meal>& order)
{
	this->_price = 0.f;
	for (const auto& i : order) {
		this->_price += i.GetMealPrice();
	}

	this->_table = table;
	this->_order_meals = order;
}
