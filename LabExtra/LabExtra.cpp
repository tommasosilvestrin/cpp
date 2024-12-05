#include <iostream>
using namespace std;

int main () {
    
    MyVector2 v;
    MyVector2 w(5);
    v[0] = 3.5;
    cout << v[0] << endl;
    v.safe_set (3, 7.7);
    cout << v.safe_get (3) << endl;
    w.safe_set (2, 4.4);
    cout << w.safe_get (2) << endl;
    try {
        w.safe_set (12, 100);
    }
    catch (invalid_argument e)
    {
        cout << "letsgoski" << endl;
    }
    
    //ESERCIZIO 2
    
    MyVector2 v2{v};
    v2.at(1) = 17.4;
    cout << v2.at(1) << endl;
    v2.push_back (2.9);
    cout << v2.pop_back() << endl;
    v2.reserve(20);
    
    return 0;
}