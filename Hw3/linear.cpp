

// Return false if the somePredicate function returns true for at
// least one of the array elements; return true otherwise.
bool allFalse(const string a[], int n)
{
	if (n <= 0)			//return true because they would all be false or invalid
		return true;

	//check condition when n is only 1
	if (n == 1)
		return !somePredicate(*a);
	
	return allFalse(a, n / 2) &&					//check base condition (n)
	allFalse(a + n / 2, n - n / 2);		            //recursion of fact (n-1); recursive step
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n < 0)
		n = 0;

	if (n == 0)
		return 0;

	if (n == 1)
		return !somePredicate(*a);

	//return total count of falses from first half and second half
	return countFalse(a, n / 2) + countFalse(a + n / 2, n - n / 2);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
	if (n <= 0)
		return -1;
	if (!somePredicate(a[0]))
		return 0;
	else {
		if (firstFalse(a + 1, n - 1) == -1)
			return -1;
		else
			return 1 + firstFalse(a + 1, n - 1);
	}
}

// Return the subscript of the greatest string in the array (i.e.,
// the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.
int locateMaximum(const string a[], int n)
{
	if (n <= 0)
		return -1;

	int pos = 1 + locateMaximum(a + 1, n - 1);

	if (a[0] > a[pos])
		return 0;

	return pos;

}