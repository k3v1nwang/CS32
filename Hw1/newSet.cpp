#include "newSet.h"
#include <iostream>

using namespace std;

//default constructor
Set::Set()
{
	data = new ItemType[DEFAULT_MAX_ITEMS];
	m_max = DEFAULT_MAX_ITEMS;
}

//constructor if value supplied in 
Set::Set(int k)
{
	//check supplied value is greater than 0
	if (k <= 0)
	{
		cerr << "cannot hold less than 0 items" << endl;
		exit(1);
	}

	data = new ItemType[k];
	m_max = k;
}

//destructor
Set::~Set()
{
	delete[] data;
}

//copy construtor 
Set::Set(const Set& other)
{
	m_max = other.m_max;
	m_size = other.m_size;
	data = new ItemType[m_max];

	for (int k = 0; k < m_max; k++)
	{
		data[k] = other.data[k];
	}
}

Set& Set::operator=(const Set& rhs)
{
	if (this != &rhs)
	{
		Set temp(rhs);
		swap(temp);
	}
	return *this;
}
bool Set::empty() const
{
	if (m_size > 0)
		return false;
	else
		return true;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	//if array is full
	if (m_max == m_size)
		return false;
	//if value is already contained
	if (contains(value))
		return false;

	data[m_size] = value;
	m_size++;
	return true;

}

bool Set::erase(const ItemType& value)
{
	if (empty())
		return false;

	for (int k = 0; k < m_size; k++)
	{
		if (data[k] == value)
		{
			data[k] = data[m_size - 1];		//replace with the last element in array
			m_size--;						//reduce size by 1
			return true;
		}
	}
	//otherwise return false
	return false;
}

bool Set::contains(const ItemType& value) const
{
	for (int k = 0; k < m_size; k++)
	{
		if (data[k] == value)
		{
			return true;
		}
	}

	return false;
}

bool Set::get(int i, ItemType& value) const
{

	if (0 <= i && i < size())
	{
		int counter;
		bool match = false;
		while (!match)		//loop until match is found
		{
			for (int k = 0; k < m_size; k++)
			{
				counter = 0;
				for (int j = 0; j < m_size; j++)
				{
					if (data[k] > data[j])	//increment counter for each value it is greater than
						counter++;
				}
				if (counter == i)		//match found, set value to data[k] and set match to be true
				{
					value = data[k];
					match = true;
				}
			}
		}
		return true;
	}
	else
		return false;
}

void Set::swap(Set& other)
{
	//initialize temp variables
	ItemType* tempSet;
	tempSet = data;
	int tempMax = m_max;
	int tempSize = m_size;

	//swap
	data = other.data;
	other.data = tempSet;

	m_max = other.m_max;
	other.m_max = tempMax;

	m_size = other.m_size;
	other.m_size = tempSize;

}