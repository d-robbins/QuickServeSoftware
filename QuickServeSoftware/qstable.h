#pragma once

#include <vector>
#include "meal.h"


class QSTable
{
public:
	QSTable(int id) : _id(id) {}
	~QSTable();

	int GetID() const { return _id; }
	void AddMeal(const Meal& m) { _meals.push_back(m); }

	friend bool operator<(const QSTable& lhs, const QSTable& rhs) {
		return lhs.GetID() < rhs.GetID();
	}
private:
	std::vector<Meal> _meals;
	int _id;
};

