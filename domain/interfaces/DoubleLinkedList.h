#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
struct Nodo {
    T element;
    Nodo* next;
    Nodo* previous;
};

template <typename T>
struct DoublyLinkedList {
    Nodo<T>* start;
    Nodo<T>* end;
    int size;
};

template <typename T>
DoublyLinkedList<T> create() {
    DoublyLinkedList<T> list;
    list.start = NULL;
    list.end = NULL;
    list.size = 0;
    return list;
}

template <typename T>
void create(DoublyLinkedList<T>& list) {
    list.start = NULL;
    list.end = NULL;
    list.size = 0;
}

template <typename T>
int size(DoublyLinkedList<T> list) {
    return list.size;
}

template <typename T>
T get(DoublyLinkedList<T> list, int index) {
    if (index < 0 || index >= list.size) {
        throw "INDEX_NOT_FOUND";
    }
    Nodo<T>* aux = list.start;
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }
    return aux->element;
}

template <typename T>
void addFirst(DoublyLinkedList<T>& list, T element) {
    Nodo<T>* newNodo = new Nodo<T>();
    newNodo->element = element;
    newNodo->next = list.start;
    newNodo->previous = NULL;
    if (list.start != NULL) {
        list.start->previous = newNodo;
    } else {
        list.end = newNodo;
    }
    list.start = newNodo;
    list.size++;
}

template <typename T>
void addLast(DoublyLinkedList<T>& list, T element) {
    Nodo<T>* newNodo = new Nodo<T>();
    newNodo->element = element;
    newNodo->next = NULL;
    newNodo->previous = list.end;
    if (list.end != NULL) {
        list.end->next = newNodo;
    } else {
        list.start = newNodo;
    }
    list.end = newNodo;
    list.size++;
}

template <typename T>
void add(DoublyLinkedList<T>& list, T element) {
    addLast(list, element);
}

template <typename T>
void removeFirst(DoublyLinkedList<T>& list) {
    if (list.start == NULL) return;
    Nodo<T>* temp = list.start;
    list.start = list.start->next;
    if (list.start != NULL) {
        list.start->previous = NULL;
    } else {
        list.end = NULL;
    }
    delete temp;
    list.size--;
}

template <typename T>
void destroy(DoublyLinkedList<T>& list) {
    while (list.start != NULL) {
        removeFirst(list);
    }
}

template <typename T>
void toString(const DoublyLinkedList<T>& list) {
    Nodo<T>* aux = list.start;
    cout << "[";
    while (aux != NULL) {
        cout << aux->element;
        if (aux->next != NULL) {
            cout << ", ";
        }
        aux = aux->next;
    }
    cout << "]" << endl;
}

#endif