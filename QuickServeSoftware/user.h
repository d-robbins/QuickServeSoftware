#pragma once

#include <string>

class QSUser
{
public:
	QSUser(std::string name, std::string id) : _name(name), _id(id) {}
	~QSUser() {}


private:
	std::string _name;
	std::string _id;
};

