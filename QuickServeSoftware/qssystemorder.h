#pragma once

#include <string>
#include <vector>

#include "meal.h"

/**
 * Class describes an order that has been placed and given to the system
 */
class QSSystemOrder
{
public:
	QSSystemOrder(std::string table, const std::vector<Meal>& order);

	~QSSystemOrder() {}

	
private:
	float _price = 0.f;	
	std::string _table = "undefined";
	std::vector<Meal> _order_meals;

};

