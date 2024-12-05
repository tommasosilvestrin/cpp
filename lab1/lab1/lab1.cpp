#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> fibonacci (int x, int y, vector<int> &v, int n) {
    v.clear ();
    v.push_back (x);
    v.push_back (y);
    for (int i = 2; i < n; i++) {
        v.push_back (v[i-1] + v[i-2]);
    }
    return v;
}

void print (string s, vector<int> v) {
    cout << s << "\n";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\n";
    }
}

int main()
{
    int x = 1;
    int y = 2;
    string s = "Vettore: ";
    vector<int> v = {1, 2, 3, 4};
    int n = 7;
    v = fibonacci (x, y, v, n);
    print (s, v);
	// cout << "hello world\n";
	return 0;
}