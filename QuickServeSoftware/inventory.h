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

private:
	std::map<Item, int> _items;
};

