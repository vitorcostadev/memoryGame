#include <iostream>
#include "../domain/interfaces/Reader.h"

using namespace std;

int main(){
    Reader reader;
    create(reader, "../domain/models/cards.csv");

    DoublyLinkedList<string> list = readCsvColumn(reader, 4);

    Nodo<string> *aux = list.start;
    while(aux != NULL){
        cout << aux->element << endl;
        aux = aux->next;
    }

    cout << getParFromIdent(reader, 1) << endl;
    return 0;
}