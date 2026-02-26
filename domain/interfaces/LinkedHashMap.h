#ifndef LinkedHashMap_H
#define LinkedHashMap_H

using namespace std;

template<typename K, typename V>
struct Hash{
    K key;
    V value;
};

template<typename K, typename V>
struct LinkedHashMap{
    int cardinalidade;
    Nodo<Hash<K, V>> *start;
    Nodo<Hash<K, V>> *end;
};

template<typename K, typename V>
void create(LinkedHashMap<K, V> &map){
    map.start = NULL;
    map.end = NULL;
    map.cardinalidade = 0;
}

template<typename K, typename V>
int size(LinkedHashMap<K, V> map){
    return map.cardinalidade;
}

template<typename K, typename V>
bool containsKey(LinkedHashMap<K, V> map, const K &key){
    Nodo<Hash<K, V>> *aux = map.start;
    while(aux != NULL){
        if(aux->element.key == key) return true;
        aux = aux->next;
    }
    return false;
}

template<typename K, typename V>
V getValue(LinkedHashMap<K, V> map, const K &key){
    Nodo<Hash<K, V>> *aux = map.start;
    while(aux != NULL){
        if(aux->element.key == key) return aux->element.value;
        aux = aux->next;
    }
    throw "KEY_NOT_FOUND";
}

template<typename K, typename V>
void put(LinkedHashMap<K, V> &map, const K &key, const V &value){
    Nodo<Hash<K, V>> *aux = map.start;
    while(aux != NULL){
        if(aux->element.key == key){
            aux->element.value = value;
            return;
        }
        aux = aux->next;
    }

    Nodo<Hash<K, V>> *novo = new Nodo<Hash<K, V>>();
    novo->element.key = key;
    novo->element.value = value;
    novo->next = NULL;

    if(map.start == NULL){
        map.start = novo;
        map.end = novo;
        novo->previous = NULL;
    }else{
        map.end->next = novo;
        novo->previous = map.end;
        map.end = novo;
    }

    map.cardinalidade++;
}

template<typename K, typename V>
void removeKey(LinkedHashMap<K, V> &map, const K &key){
    Nodo<Hash<K, V>> *aux = map.start;
    while(aux != NULL){
        if(aux->element.key == key) break;
        aux = aux->next;
    }

    if(aux == NULL) throw "KEY_NOT_FOUND";

    if(aux->previous != NULL){
        aux->previous->next = aux->next;
    }else{
        map.start = aux->next;
    }

    if(aux->next != NULL){
        aux->next->previous = aux->previous;
    }else{
        map.end = aux->previous;
    }

    delete aux;
    map.cardinalidade--;
}

template<typename K, typename V>
Hash<K, V> getAt(LinkedHashMap<K, V> map, int index){
    if(map.cardinalidade == 0) throw "EMPTY_MAP";
    if(index < 0 || index >= map.cardinalidade) throw "OVERFLOW";

    int cont = 0;
    Nodo<Hash<K, V>> *aux = map.start;
    while(aux != NULL){
        if(cont == index) return aux->element;
        cont++;
        aux = aux->next;
    }
    throw "OVERFLOW";
}

template<typename K, typename V>
void toString(LinkedHashMap<K, V> map){
    Nodo<Hash<K, V>> *aux = map.start;
    cout << "{";
    while(aux != NULL){
        cout << aux->element.key << ": " << aux->element.value;
        if(aux->next != NULL){
            cout << ", ";
        }
        aux = aux->next;
    }
    cout << "}" << endl;
}

#endif