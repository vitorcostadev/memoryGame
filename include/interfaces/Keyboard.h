#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;


struct KeyboardState {
    int position;       
    int min_pos;        
    int max_pos;        
    int visual_stride;  
    int visual_offset;  
};

void initKeyboard(
    KeyboardState& kb, 
    int min_val, 
    int max_val, 
    int start_val, 
    int stride, 
    int offset) {

    kb.min_pos = min_val;
    kb.max_pos = max_val;
    kb.position = start_val;
    kb.visual_stride = stride;
    kb.visual_offset = offset;

    if (kb.position < kb.min_pos) {
        kb.position = kb.min_pos;
    }
    if (kb.position > kb.max_pos) {
        kb.position = kb.max_pos;
    }
}

void drawConsole(
    const KeyboardState& kb, 
    const Tabuleiro& visual_map, 
    const string& statusMessage = ""
    ) {
    system("cls");
    cout << generateMapEmoji(visual_map, 5) << "\n";

    int total_visual_columns = kb.visual_offset + ((kb.max_pos - kb.min_pos) * kb.visual_stride) + 2; 

    for (int i = 0; i < total_visual_columns; i++) {
        cout << ".";
    }
    cout << "\n";

    int cursor_spaces = kb.visual_offset + ((kb.position - kb.min_pos) * kb.visual_stride);

    for (int i = 0; i < cursor_spaces; i++) {
        cout << " ";
    }
    cout << "^\n";
    
    cout << "\nIndice atual: " << kb.position << "\n";
    if (!statusMessage.empty()) {
        cout << statusMessage << "\n";
    }
}

int runInteractiveMenu(
    KeyboardState &kb, 
    const Tabuleiro &visual_map, 
    const string &statusMessage = ""
    ) {
    bool running = true;
    int key = 0;

    drawConsole(kb, visual_map, statusMessage);

    while (running) {
        key = _getch();

        if (key == 'a' || key == 'A') {
            if (kb.position > kb.min_pos) {
                kb.position--;
                drawConsole(kb, visual_map, statusMessage);
            }
        } 
        else if (key == 'd' || key == 'D') {
            if (kb.position < kb.max_pos) {
                kb.position++;
                drawConsole(kb, visual_map, statusMessage);
            }
        } 
        else if (key == '\r') {
            running = false;
        }
    }

    system("cls");
    return kb.position;
}

#endif