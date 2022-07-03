#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
//using ItemType = unsigned long;
using ItemType = std::string;

class Set
{
public:

	Set();//constructor
	Set(const Set& other); //copy constructor
	~Set();				//destructor
	Set& operator= (const Set& rhs);	//assignment operator 

	bool empty() const; 
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value)const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
	
	void dump() const;

private:

	struct node
	{
		ItemType val;
		node* next;
		node* prev;
	};

	node* head;
	int m_size;
	
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif