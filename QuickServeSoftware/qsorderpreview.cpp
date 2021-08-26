#include "qsorderpreview.h"


struct IngredientData {
	Meal _m;
	std::vector<std::string> _ingredients;
};

QSOrderPreview::QSOrderPreview(wxPanel* parent) : wxListBox(parent, wxID_ANY, wxDefaultPosition)
{

}

void QSOrderPreview::AddItem(Meal m, const std::vector<std::string>& default_meal_items)
{
	IngredientData d;
	d._m = m;
	d._ingredients = default_meal_items;
	
	//auto data = static_cast<void*>(d);
	this->AppendString("fjkdlsa");
}
