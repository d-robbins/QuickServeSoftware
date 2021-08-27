#include "meal.h"

Meal::Meal(const std::vector<std::string>& items, const float& price, const std::string& name)
	: _ingredients(items), _price(price), _name(name)
{

}

void Meal::PrintMeal()
{
	std::string meal = _name + "\n" + std::to_string(_price) + "\n";

	for (const auto& i : _ingredients) {
		meal += i + "\n";
	}

	wxMessageBox(meal);
}

void Meal::DisplayIngredients()
{
	for (int i = 0; i < _ingredients.size(); i++) {
		printf("\t%d: %s\n", i + 1, _ingredients[i].c_str());
	}
}

void Meal::DeleteIngredient(unsigned int i)
{
	_ingredients[i] = _ingredients.back();
	_ingredients.pop_back();
}
	