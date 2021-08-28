#pragma once

#include "item.h"

#include <vector>
#include <iostream>
#include <string>

#include <wx/wx.h>

class Meal
{
public:
	Meal() : _price(0.f), _name("undefined") {}
	Meal(const std::vector<std::string>& items, const float& price, const std::string& name);
	~Meal() {}

	void PrintMeal();
	std::string GetMealName() const { return _name; }
	void AddIngredient(std::string item) { _ingredients.push_back(item); }
	void DisplayIngredients();
	void DeleteIngredient(unsigned int i);
	void SetMealName(const std::string& name) { _name = name; }

	float GetMealPrice() const { return _price; }

	std::vector<std::string> GetIngredients() { return _ingredients; }
	void ClearIngredients() { _ingredients.clear(); }

	void AddOperation(std::pair<std::string, std::string> ops) { _ops.push_back(ops); }

	std::vector<std::pair<std::string, std::string>> GetOps() { return _ops; }

private:	
	std::vector<std::string> _ingredients;
	std::vector<std::pair<std::string, std::string>> _ops;
	float _price = 0.f;
	std::string _name = "undefined";
};

