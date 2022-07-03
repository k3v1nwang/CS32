#include "Set.h"
#include <iostream>
#include <cassert>
#include <string>
using namespace std;


void test()
{
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "laobing";
    assert(ss.get(0, x) && x == "pita");
    assert(ss.get(1, x) && x == "roti");
}


/*
void test()
{
    Set uls;
    assert(uls.insert(20));
    assert(uls.insert(10));
    assert(uls.size() == 2);
    assert(uls.contains(10));
    ItemType x = 30;
    assert(uls.get(0, x) && x == 10);
    assert(uls.get(1, x) && x == 20);
}
*/

 
int main()
{
    /*
     Set ss;
     ss.insert("lavash");
     ss.insert("roti");
     ss.insert("chapati");
     ss.insert("injera");
     ss.insert("roti");
     ss.insert("matzo");
     ss.insert("injera");
     assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
     string x;
     ss.get(0, x);
     assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
     ss.get(4, x);
     assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
     ss.get(2, x);
     assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss


     Set ss1;
     ss1.insert("laobing");
     Set ss2;
     ss2.insert("matzo");
     ss2.insert("pita");
     ss1.swap(ss2);
     assert(ss1.size() == 2 && ss1.contains("matzo") && ss1.contains("pita") &&
         ss2.size() == 1 && ss2.contains("laobing"));

     Set ss;
     ss.insert("dosa");
     assert(!ss.contains(""));
     ss.insert("tortilla");
     ss.insert("");
     ss.insert("focaccia");
     assert(ss.contains(""));
     ss.erase("dosa");
     assert(ss.size() == 3 && ss.contains("focaccia") && ss.contains("tortilla") &&
         ss.contains(""));
     string v;
     assert(ss.get(1, v) && v == "focaccia");
     assert(ss.get(0, v) && v == "");
     */



    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert(!s.get(42, x) && x == "arepa"); // x unchanged by get failure
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x) && x == "chapati");
    cout << "Passed all tests" << endl;



    /*
    Set s;
    assert(s.empty());
    ItemType x = 9876543;
    assert(!s.get(42, x) && x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0, x) && x == 123456789);
    cout << "Passed all tests" << endl;
    */


    test();
    cout << "Passed all tests" << endl;
}

