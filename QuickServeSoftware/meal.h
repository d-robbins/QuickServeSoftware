#pragma once

#include "item.h"

#include <vector>
#include <iostream>

class Meal
{
public:
	Meal(const std::vector<std::string>& items, const float& price, const std::string& name);
	~Meal() {}

	void PrintMeal();
	std::string GetMealName() const { return _name; }
	void DisplayIngredients();
	void DeleteIngredient(unsigned int i);
private:	
	std::vector<std::string> _ingredients;
	float _price;
	std::string _name;
};

