#include <iostream>
#include <map>
using namespace std;


int main() {
    map<int, char> a = {{1, 'a'}};
    cout << a.at(1);
    a.insert(make_pair(2, 'b'));
    cout << a.at(2);
    a.emplace(make_pair(1, 'b'));
    a.insert_or_assign(1, 'b');
    cout << a.at(1);
    return 0;
}