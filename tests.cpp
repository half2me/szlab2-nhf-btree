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
    Node<int, 1> integer_1;
    Node<int, 2> integer_2;
    Node<int, 3> integer_3;
    Node<int, 4> integer_4;

    // Generate some test numbers
    int tmp[50];
    for(int i=0; i<50; i++){
        tmp[i] = i;
    }
    // Shuffle them
    //random_shuffle(begin(tmp), end(tmp));

    // Insert them

    cout << "[Test Numbers]: ";
    for(int i=0; i<50; i++){
        integer_1.Insert(tmp[i]);
        integer_2.Insert(tmp[i]);
        integer_3.Insert(tmp[i]);
        integer_4.Insert(tmp[i]);
        cout << tmp[i] << " ";
        cout.flush();
    }
    cout << endl;

    cout << integer_1 << endl;
    cout << integer_2 << endl;
    cout << integer_3 << endl;
    cout << integer_4 << endl;
    cout.flush();

    return 0;
}