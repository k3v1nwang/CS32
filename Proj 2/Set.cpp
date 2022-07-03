#include "Set.h"
#include <iostream>

using namespace std;

Set::Set() //default constructor
{
	head = new node;
	head->next = head;		//circular structure
	head->prev = head;
	m_size = 0;
}

Set::Set(const Set& other)		//copy constructor
{
	//create new set object from existing set object 
	m_size = other.m_size; 
	
	head = new node;
	head->next = head;
	head->prev = head; 

	node* cur = head->next;		//pointer to the current node

	//create a pointer p that traverses through the set and assigns values to a newNode
	for (node* p = other.head->next; p != other.head; p = p->next)
	{
		node* newNode = new node;
		newNode->val = p->val;

		newNode->next = cur->next;
		newNode->prev = cur;
		cur->next = newNode;
		head->prev = newNode;

		cur = newNode;			//update the current node with value of newNode
	}

}
Set::~Set()				//destructor
{
	while (head->next != head)	//loop until only dummy node left
	{
		node* p = head->next;
		//deallocate the pointer
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
	}
	delete head;			//delete the dummy node
}

Set&Set::operator=(const Set& rhs)	//assignment operator 
{
	if (this != &rhs)		//alias check 
	{
		Set temp(rhs);			//copy-and-swap
		swap(temp);
	}
	return *this;
}

//function implmentations
bool Set::empty() const
{
	//return true  if set is empty, otherwise false
	if (m_size == 0)
		return true;
	else
		return false;
}

int Set::size() const
{
	//return number of items in the set
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	//insert value into set if it not already present
	//return true if value is actually inserted
	//leave set unchanged and return false if value is not inserted 
	if (contains(value))
		return false;

	//find the current node, if it is empty, it will be the dummy node in which head points to, otherwise, traverse to the end
	node* cur = head->next;			//node at which head points to
	while (cur->next != head)		//stops at the last node
	{
		cur = cur->next;
	}

	node* p = new node; 
	p->val = value;

	p->next = head;			//new node's next pointer points to dummy node 
	p->prev = cur;			//new node's previous pointer is the current node
	cur->next = p;			//current node points to new node
	head->prev = p;			//dummy node wraps around and completes the circle 

	m_size++;				//increase size by 1
	return true;

}
	
bool Set::erase(const ItemType& value)
{
	//remove value from set if it is present
	//return true if value is removed
	//otherwise return false and leave set unchanged
	
	if (empty())			//cannot erase from empty set
		return false;
	if (!contains(value))	//cannot erase if value is not contained within set
		return false;

	node* cur = head->next;
	while (cur != head && cur->val != value)	//traverse to position where value is located
	{
		cur = cur->next;
	}

	//free the current node
	(cur->prev)->next = cur->next;				//previous "next" pointer set to the one after it
	(cur->next)->prev = cur->prev;				//current pointer's next "prev" pointer set to the one before it 
	
	//ensure that current pointer points to nothing and delete it
	cur->next = nullptr;
	cur->prev = nullptr;
	delete cur;									//delete the node
	cur = nullptr;

	m_size--;

	return true;
}

bool Set::contains(const ItemType& value)const
{
	//return true if the value is in the set, otherwise false
	for (node* p = head->next; p != head; p = p->next)	//traverse through the set until reaching the dummy node
	{
		if (p->val == value)			//return true if value is found
			return true;
	}
	return false;		//if traversal through entire set did not find value, return false
}

bool Set::get(int pos, ItemType& value) const
{
	// If 0 <= pos < size(), copy into value the item in the set that is
	// strictly greater than exactly pos items in the set and return true.
	// Otherwise, leave value unchanged and return false.
	if (0 <= pos && pos < size())
	{
		int counter;				//counter for how many items that the current value is greater than
		bool match = false;			
		while (!match)				//continue until match is found
		{
			for (node* p = head->next; p != head; p = p->next)			//pointer p to a value in the set
			{
				counter = 0;											//resets to 0 for every new value that is evaluated in a set
				for (node* k = head->next; k != head; k = k->next)		//compare it with pointer k to another value in the set
				{
					if (p->val > k->val)
						counter++;					//increment the coutner for each value it is strictly greater than
				}
				if (counter == pos)					//when the counter matches the pos supplied in, set value to that of the currently evaluated node and exit the while loop
				{
					value = p->val;
					match = true;
				}
			}
		}
		return true;				//return true if value was found
	}
	else
		return false;				//otherwise return false 

}

void Set::swap(Set& other)
{
	// Exchange the contents of this set with the other one.
	
	//swap sizes
	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;

	//swap head pointers
	node* tempHead = head;
	head = other.head;
	other.head = tempHead;

}

void Set::dump() const
{
	cerr << "The size of the Set is: " << m_size << endl;
	cerr << "The items in the Set are: " << endl;
	node* cur = head->next;
	for (; cur != head; cur = cur->next)
	{
		cerr << cur->val << " ";
	}

	cerr << endl;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
	//initialize an empty, temporary Set
	Set tempSet;

	//copy into tempSet the values from s1
	for (int k = 0; k < s1.size(); k++)
	{
		ItemType item;
		s1.get(k, item);
		tempSet.insert(item);
	}

	//copy into tempSet the values from s2
	for (int j = 0; j < s2.size(); j++)
	{
		ItemType item;
		s2.get(j, item);
		tempSet.insert(item);
	}

	//assign tempSet to be resulting Set
	result = tempSet;

}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	//intialize empty, temporary Set
	Set tempSet;

	//unite the two sets
	unite(s1, s2, tempSet);

	//erase from tempSet values that match values from s2
	for (int j = 0; j < s2.size(); j++)
	{
		ItemType item; 
		s2.get(j, item);
		tempSet.erase(item);
	}

	//assign tempSet to resulting Set
	result = tempSet;
}