#include "inventory.h"

#include <fstream>
#include <sstream>
#include <iostream>

Inventory::Inventory(std::string file)
{
	std::ifstream in;
	in.open(file);
	if (!in.is_open()) {
		std::cerr << "Error opening: " << file << "\nContinuing without intializing inventory" << std::endl;
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		int quantity;
		std::string item;

		std::istringstream iss(line);
		iss >> item >> quantity;

		this->_items.insert(std::pair<Item, int>(Item(item), quantity));
	}
}

void Inventory::PrintItems()
{
	for (auto i = this->_items.begin(); i != _items.end(); ++i) {
		printf("%s		:	%d\n", i->first.GetName().c_str(), i->second);
	}
}
