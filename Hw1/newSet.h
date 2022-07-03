#ifndef NEWSET_H
#define NEWSET_H

#include <string>

using namespace std;
//using ItemType = unsigned long;
using ItemType =  std::string;

const int DEFAULT_MAX_ITEMS = 240;

class Set
{
public:
	//default constructor and constructor when value supplied to change max size
	Set();
	Set(int k);


	~Set();		//destructor
	Set(const Set& other);	//copy constructor
	Set& operator=(const Set& rhs);

	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int i, ItemType& value) const;
	void swap(Set& other);


private:
	ItemType* data;
	int m_max = DEFAULT_MAX_ITEMS;
	int m_size = 0;

};

#endif
