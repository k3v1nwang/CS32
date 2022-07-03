#include "Set.h"
#include <iostream>

using namespace std;

Set::Set()
{

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

bool Set::insert(const ItemType&value)
{
	if (m_size == DEFAULT_MAX_ITEMS)	//if array is at max capacity, return false
		return false;

	if (contains(value))	//if array already contains the value, return false
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
	for (int k = 0; k < DEFAULT_MAX_ITEMS; k++)
	{
		ItemType temp = other.data[k];
		other.data[k] = data[k];
		data[k] = temp;
	}

	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;
}

