#pragma once

#include "item.h"

#include <vector>
#include <iostream>
#include <string>

class Meal
{
public:
	Meal() {}
	Meal(const std::vector<std::string>& items, const float& price, const std::string& name);
	~Meal() {}

	void PrintMeal();
	std::string GetMealName() const { return _name; }
	void AddIngredient(std::string item) { _ingredients.push_back(item); }
	void DisplayIngredients();
	void DeleteIngredient(unsigned int i);

	void SetMealSystemID(int i) { _systemID = i; }
	int GetSysID() const { return _systemID; }

	std::vector<std::string> GetIngredients() { return _ingredients; }
	void ClearIngredients() { _ingredients.clear(); }

private:	
	std::vector<std::string> _ingredients;
	float _price;
	std::string _name;
	int _systemID;
};

