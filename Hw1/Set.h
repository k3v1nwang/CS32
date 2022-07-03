#ifndef SET_H
#define SET_H

#include <string>
using namespace std;

using ItemType = std::string;
//using ItemType = unsigned long;

const int DEFAULT_MAX_ITEMS = 240;

class Set
{
public:
    Set();         // Create an empty set (i.e., one with no items).

    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value is actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).

    bool erase(const ItemType&value);
    // Remove the value from the set if it is present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.

    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.

    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
    // Exchange the contents of this set with the other one.



private: 
    ItemType data[DEFAULT_MAX_ITEMS];
    int m_size = 0;
};



#endif // !SET_H

