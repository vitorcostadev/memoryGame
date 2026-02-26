#ifndef List_H
#define List_H

using namespace std;

template<typename T, int MAX>
struct List {
    int cardinalidade;
    T elementos[MAX];
};

template<typename T, int MAX>
bool isEmpty(List<T, MAX> list) {
    return list.cardinalidade == 0;
}

template<typename T, int MAX>
void create(List<T, MAX> &list) {
    list.cardinalidade = 0;
}

template<typename T, int MAX>
bool hasSpace(List<T, MAX> list) {
    return list.cardinalidade < MAX;
}

template<typename T, int MAX>
int size(List<T, MAX> list) {
    return list.cardinalidade;
}

template<typename T, int MAX>
bool contains(List<T, MAX> list, T target) {
    if(isEmpty(list)) throw "EMPTY_LIST";

    for(int i = 0; i < size(list); i++) {  
        if(list.elementos[i] == target) 
            return true;
    }
    return false;
}

template<typename T, int MAX>
T getFirst(List<T, MAX> list) {  
    if(isEmpty(list)) throw "EMPTY_LIST";
    return get(list, 0);  
}


template<typename T, int MAX>
T getLast(List<T, MAX> list) { 
    if(isEmpty(list)) throw "EMPTY_LIST";
    return get(list, size(list)-1); 
}

template<typename T, int MAX>
T get(List<T, MAX> list, int index){
    if(index >= size(list)) throw "OVERFLOW";;
    if(index < 0 || isEmpty(list)) throw "EMPTY_LIST";

    return list.elementos[index];
}

template<typename T, int MAX>
bool add(List<T, MAX> &list, T element) {

    if(hasSpace(list)) {
        list.elementos[list.cardinalidade] = element;
        list.cardinalidade++;
        return true;
    }
    return false;  
}

template<typename T, int MAX>
bool addAt(List<T, MAX> &list, T target, int index){
    if(!hasSpace(list)) return false;
    if(index < 0 || index > list.cardinalidade) throw "EMPTY_LIST";

    for(int i = list.cardinalidade; i > index; i--){
        list.elementos[i] = list.elementos[i-1];
    }
    list.elementos[index] = target;
    list.cardinalidade++;
    return true;
}

template<typename T, int MAX>
void clear(List<T, MAX> &list) {
    list.cardinalidade = 0;
}

template<typename T, int MAX>
bool remove(List<T, MAX> &list, int index){
    if(isEmpty(list)) throw "EMPTY_LIST";
    if(index < 0 || index >= size(list)) throw "OVERFLOW";

    for(unsigned i = index; i < size(list) - 1; i++){
        list.elementos[i] = list.elementos[i+1];
    }
    list.cardinalidade--;
    return true;
}

template<typename T, int MAX>
bool removeFirst(List<T, MAX> &list) {
    return remove(list, 0);
}

template<typename T, int MAX>
bool removeLast(List<T, MAX> &list) {
    if(isEmpty(list)) throw "EMPTY_LIST";
    list.cardinalidade--;
    return true;
}

template<typename T, int MAX>
List<T, MAX> of(T array[], int size) {
    if(size > MAX) throw "OVERFLOW";
    List<T, MAX> newList;
    create(newList);

    for(int i = 0; i < size; i++) {
        add(newList, array[i]);
    }

    return newList;
}

template<typename T, int MAX>
void toString(List<T, MAX> list) {
    cout << "[";
    for(int i = 0; i < size(list); i++) {
        cout << list.elementos[i];
        if(i < size(list) - 1) cout << ", ";
    }
    cout << "]";
}

template<typename T, int MAX>
void sort(List<T, MAX> &list){
    for(unsigned i = 0; i<size(list); i++){
        for(unsigned j = i + 1; j < size(list); j++){
            if(get(list, i) > get(list, j)){
                swap(list.elementos[i], list.elementos[j]);
            }
        }
    }
}

template<typename T, int MAX>
T max(List<T, MAX> list){
    if(isEmpty(list)) throw "EMPTY_LIST";
    
    int maxValue = getFirst(list);

    for(unsigned i = 0; i<size(list); i++){
        if(get(list, i) > maxValue) maxValue = get(list, i);
    }

    return maxValue;
}

template<typename T, int MAX>
T min(List<T, MAX> list){
    if(isEmpty(list)) throw "EMPTY_LIST";

    T minValue = getFirst(list);

    for(unsigned i = 0; i<size(list); i++){
        if(get(list, i) < minValue) minValue = get(list, i);
    }

    return minValue;
}

template<typename T, int MAX>
void removeDuplicates(List<T, MAX> &list){
    if(isEmpty(list)) throw "EMPTY_LIST";

    int occur;
    T value;

    for(int i = 0; i<size(list);){
        value = get(list, i);
        occur = 0;

        for(int j = 0; j<size(list); j++){
            if(get(list, j) == value) occur++;
        }

        if(occur > 1) remove(list, i);
        else i++;
    }

}
#endif