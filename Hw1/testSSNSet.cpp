#include "Set.h"
#include"SSNSet.h"
#include <iostream>
#include <cassert>

using namespace std;


int main()
{
	SSNSet s1;
	s1.add(321);
	s1.add(123);
	cerr << s1.size() << endl;
	assert(!s1.add(123));
	s1.print();
}
