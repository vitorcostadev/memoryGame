#ifndef READER_H
#define READER_H

#include <fstream>
#include <string>
#include <stdexcept>
#include "DoubleLinkedList.h"
#include <cstring>

using namespace std;

struct Reader {
    string file;
    ifstream ifs;
};

void create(Reader &reader, string file) {
    reader.file = file;
    if(reader.ifs.is_open()) reader.ifs.close();
    reader.ifs.open(file.c_str());
}

DoublyLinkedList<string> readCsvColumn(Reader &reader, int column) {
    DoublyLinkedList<string> list;
    create(list);

    reader.ifs.clear();
    reader.ifs.seekg(0);

    string line;
    bool firstLine = true;

    while(getline(reader.ifs, line)) {
        if(firstLine) { firstLine = false; continue; }

        string value = "";
        int currentColumn = 0;
        bool added = false;
        
        for(size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if(c == ',') {
                if(currentColumn == column) {
                    add(list, value);
                    added = true;
                    break;
                }
                value.clear();
                currentColumn++;
            } else {
                value.push_back(c);
            }
        }
        if(!added && currentColumn == column && !value.empty()) {
            add(list, value);
        }
    }
    return list;
}

int getParFromIdent(Reader &reader, int identificador) {
    if(identificador <= 0 || identificador > 20) return -1; 

    DoublyLinkedList<string> columnData = readCsvColumn(reader, 4);
    int result = -1;

    try {
        string pair = get(columnData, identificador-1);
        if(!pair.empty()) {
            result = stoi(pair);
        }
    } catch (const char *err) {
        if(strcmp(err, "INDEX_NOT_FOUND") == 0){
            destroy(columnData); 
            return result;
        }
    }

    destroy(columnData);
    return result;
}
#endif