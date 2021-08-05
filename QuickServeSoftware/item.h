#pragma once

#include <string>

class Item
{
public:
	Item() = delete;

	Item(std::string name) : _title(name) {}
	~Item() {}

	std::string GetName() const { return _title; }

	friend bool operator<(const Item& lhs, const Item& rhs) {
		return lhs.GetName() < rhs.GetName();
	}
private:
	std::string _title;
};

