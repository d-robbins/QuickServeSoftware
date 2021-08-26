#pragma once

#include <wx/wx.h>
#include <vector>
#include <string>

#include "meal.h"

class QSOrderPreview : public wxListBox
{
public:
	QSOrderPreview(wxPanel* parent);

	void AddItem(Meal m, const std::vector<std::string>& default_meal_items);

private:
};

