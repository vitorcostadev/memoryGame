#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

template <typename T>
struct Node
{
    T element;
    Node* next;
    Node* previous;
};

template <typename T>
struct DoublyLinkedList
{
    Node<T>* start;
    Node<T>* end;
    int cardinalidade;
};


template <typename T>
void create(DoublyLinkedList<T> &list)
{
    list.start = NULL;
    list.end = NULL;
    list.cardinalidade = 0;
}

template <typename T>
int size(DoublyLinkedList<T> list)
{
    return list.cardinalidade;
}

template <typename T>
T get(DoublyLinkedList<T> list, int index)
{
    if(index < 0 || index >= size(list)) throw "OVERFLOW";

    Node<T> *node = list.start;
    for(int i = 0; node != NULL && i != index; i++, node = node->next);

    return node->element;
}

template <typename T>
void add(DoublyLinkedList<T> &list, T element, int index)
{
    if(index < 0 || index > size(list)) throw "OVERFLOW";

    Node<T> *newNode = new Node<T>();
    newNode->element = element;
    newNode->next = NULL;
    newNode->previous = NULL;

    if(size(list) == 0)
    {
        list.start = newNode;
        list.end = newNode;
    }
    else if(index == 0)
    {
        newNode->next = list.start;
        list.start->previous = newNode;
        list.start = newNode;
    }
    else if(index == size(list))
    {
        list.end->next = newNode;
        newNode->previous = list.end;
        list.end = newNode;
    }
    else
    {
        Node<T> *current = list.start;
        for(int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->previous = current;
        current->next->previous = newNode;
        current->next = newNode;
    }
    list.cardinalidade++;
}

template <typename T>
void remove(DoublyLinkedList<T>& list, int index)
{
    if(index < 0 || index >= size(list)) throw "OVERFLOW";

    Node<T> *nodeToRemove = list.start;
    for(int i = 0; i < index; i++)
    {
        nodeToRemove = nodeToRemove->next;
    }

    if(list.cardinalidade == 1)
    {
        list.start = NULL;
        list.end = NULL;
    }
    else if(index == 0)
    {
        list.start = nodeToRemove->next;
        list.start->previous = NULL;
    }
    else if(index == size(list) - 1)
    {
        list.end = nodeToRemove->previous;
        list.end->next = NULL;
    }
    else
    {
        nodeToRemove->previous->next = nodeToRemove->next;
        nodeToRemove->next->previous = nodeToRemove->previous;
    }
    delete nodeToRemove;
    list.cardinalidade--;
}

template <typename T>
void destroy(DoublyLinkedList<T>& list)
{
    Node<T> *current = list.start;
    while(current != NULL)
    {
        Node<T> *temp = current;
        current = current->next;
        delete temp;
    }
    list.start = NULL;
    list.end = NULL;
    list.cardinalidade = 0;
}

#endif
