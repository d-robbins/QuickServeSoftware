#pragma once

#include "item.h"

#include <string>
#include <map>

class Inventory
{
public:
	Inventory() {}
	Inventory(std::string file);
	~Inventory() {}

	void PrintItems();
	std::map<Item, int> GetItems() { return _items; }
private:
	std::map<Item, int> _items;
};

