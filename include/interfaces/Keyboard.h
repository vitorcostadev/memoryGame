/*
Keyboard_H

Nesta header, definimos toda a lógica que controla os movimentos
do teclado que o usuário irá usar para navegar pelo menu de seleção de cartas.

a struct KeyboardState é a estrutura que armazena o estado atual do teclado, incluindo a posição atual,
os limites mínimo e máximo, o espaçamento visual entre as opções e o deslocamento visual para
centralizar o cursor.

A função initKeyboard é responsável por inicializar o estado do teclado com os valores fornecidos,
garantindo que a posição inicial esteja dentro dos limites definidos.

A função drawConsole é responsável por desenhar a interface do console, incluindo o mapa visual das
cartas, uma linha de pontos para separar o mapa do cursor, o cursor em si (representado por um "^") e
uma mensagem de status opcional.

A função runInteractiveMenu é a função principal que executa o loop de interação com o usuário. Ela
escuta as entradas do teclado para mover o cursor para a esquerda (tecla 'a' ou 'A') ou para a direita
(tecla 'd' ou 'D'), e para confirmar a seleção (tecla Enter). O loop continua até que o usuário confirme
a seleção, momento em que a função retorna a posição final selecionada.
*/
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <cstdlib>
#include <conio.h>
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;


struct KeyboardState
{
    int position;
    int min_pos;
    int max_pos;
    int visual_stride;
    int visual_offset;
};

void initKeyboard(
    /*
    Inicializa o estado do teclado com os valores fornecidos, garantindo que a posição inicial esteja
    dentro dos limites definidos.
    */
    KeyboardState& kb,
    int min_val,
    int max_val,
    int start_val,
    int stride,
    int offset)
{

    kb.min_pos = min_val;
    kb.max_pos = max_val;
    kb.position = start_val;
    kb.visual_stride = stride;
    kb.visual_offset = offset;

    if (kb.position < kb.min_pos)
    {
        kb.position = kb.min_pos;
    }
    if (kb.position > kb.max_pos)
    {
        kb.position = kb.max_pos;
    }
}

void drawConsole(
    /*
    Desenha o console, incluindo o mapa visual das cartas, uma linha de pontos para separar o
    mapa do cursor, e uma mensagem de status opcional. O cursor é representado por um "^" e é
    posicionado de acordo com o estado do teclado.
    */
    const KeyboardState& kb,
    const Tabuleiro& visual_map,
    const string& statusMessage = ""
)
{
    system("cls");
    cout << generateMapEmoji(visual_map, 5) << "\n";

    int total_visual_columns = kb.visual_offset + ((kb.max_pos - kb.min_pos) * kb.visual_stride) + 2;

    for (int i = 0; i < total_visual_columns; i++)
    {
        cout << ".";
    }
    cout << "\n";

    int cursor_spaces = kb.visual_offset + ((kb.position - kb.min_pos) * kb.visual_stride);

    for (int i = 0; i < cursor_spaces; i++)
    {
        cout << " ";
    }
    cout << "^\n";

    cout << "\nIndice atual: " << kb.position << "\n";
    if (!statusMessage.empty())
    {
        cout << statusMessage << "\n";
    }
}

int runInteractiveMenu(
    /*
    Executa o loop de interação com o usuário, escutando as entradas do teclado para mover o cursor
    para a esquerda (tecla 'a' ou 'A') ou para a direita (tecla 'd' ou 'D'), e para confirmar a seleção
    (tecla Enter). O loop continua até que o usuário confirme a seleção, momento em que a função retorna
    a posição final selecionada.
    */
    KeyboardState &kb,
    const Tabuleiro &visual_map,
    const string &statusMessage = ""
)
{
    bool running = true;
    int key = 0;

    drawConsole(kb, visual_map, statusMessage);

    while (running)
    {
        key = _getch();

        if (key == 'a' || key == 'A')
        {
            if (kb.position > kb.min_pos)
            {
                kb.position--;
                drawConsole(kb, visual_map, statusMessage);
            }
        }
        else if (key == 'd' || key == 'D')
        {
            if (kb.position < kb.max_pos)
            {
                kb.position++;
                drawConsole(kb, visual_map, statusMessage);
            }
        }
        else if (key == '\r')
        {
            running = false;
        }
    }

    system("cls");
    return kb.position;
}

#endif
