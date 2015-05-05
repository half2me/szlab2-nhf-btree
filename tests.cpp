#include <iostream>
#include "BTree.hpp"

using namespace std;

// Test class with comparable data
class test{
private:
    int n;
public:
    test(){
        n = 0;
    }
    test(int num):n(num){ }
    bool operator<(const test& t){ return n<t.n; }
    bool operator>(const test& t){ return n>t.n; }
    bool operator==(const test& t){ return n==t.n; }
};

int main() {
    // Make different kinds of B-Trees
    Node<int, 2> integer_2;
    //Node<double, 4> double_4;
    //Node<char, 2> char_2;
    //Node<test, 6> test_6;

    // Insert data
    //integer_2.Insert(5); integer_2.Insert(3); integer_2.Insert(6);
    //double_4.Insert(3.45); double_4.Insert(2.87); double_4.Insert(3.87);
    //char_2.Insert('a'); char_2.Insert('d'); char_2.Insert('c');
    //test* a = new test(5); test* b = new test(3); test* c = new test(6);
    //test_6.Insert(*a); test_6.Insert(*b); test_6.Insert(*c);
    //test_6.Insert(*a); test_6.Insert(*b); test_6.Insert(*c);

    // Delete data
    /*
    integer_2.Delete(5);
    double_4.Delete(3.45);
    char_2.Delete('a');
    test_6.Delete(*a);
     */

    // Clean up
    //delete a; delete b; delete c;

    return 0;
}