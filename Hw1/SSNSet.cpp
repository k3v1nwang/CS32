#include"SSNSet.h"
#include <iostream>

using namespace std;
SSNSet::SSNSet()
{

}

bool SSNSet::add(unsigned long ssn)
{
	if (m_ssn.insert(ssn))
		return true;
	else
		return false;
}

int SSNSet::size()const
{
	int size;
	size = m_ssn.size();
	return size;
}

void SSNSet::print() const
{
	ItemType val;
	for (int k = 0; k < m_ssn.size(); k++)
	{
		m_ssn.get(k, val);
		cout << val << endl;
	}
}



