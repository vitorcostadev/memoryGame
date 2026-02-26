#include <iostream> 
#include "../domain/interfaces/LinkedHashMap.h"

using namespace std;
int main(){
    LinkedHashMap<int, string> map;
    create(map);

    put(map, 1, string("one"));
    put(map, 2, string("two"));
    put(map, 3, string("three"));

    cout << getValue(map, 1) << endl; // one
    cout << getValue(map, 2) << endl; // two
    cout << getValue(map, 3) << endl; // three

    removeKey(map, 2);

    cout << containsKey(map, 2) << endl; // false
    cout << size(map) << endl; // 2

    return 0;
}