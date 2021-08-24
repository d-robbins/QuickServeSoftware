#pragma once

#include <vector>

class QSTable
{
public:
	QSTable(int id) : _id(id) {}
	~QSTable();

	int GetID() const { return _id; }

	friend bool operator<(const QSTable& lhs, const QSTable& rhs) {
		return lhs.GetID() < rhs.GetID();
	}
private:
	int _id;
};

