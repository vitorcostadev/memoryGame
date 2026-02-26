#include <iostream>
#include "../domain/interfaces/Keyboard.h"
#include "../domain/interfaces/Game.h"
#include <windows.h>

using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);
    KeyboardState kb;
    Game game;
    
    initKeyboard(kb, 1, 20, 0, 3, 2);
    createTabuleiro(game.cards);
    const char* visual_map = generateMapEmoji(game).c_str();
    runInteractiveMenu(kb, visual_map);

    return 0;
}