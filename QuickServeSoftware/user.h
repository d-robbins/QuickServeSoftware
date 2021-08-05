#pragma once

#include <string>

class User
{
public:
	User(std::string name, std::string id) : _name(name), _id(id) {}
	~User() {}


private:
	std::string _name;
	std::string _id;
};

