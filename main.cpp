#include <iostream>
#include "domain/interfaces/List.h"
#include "domain/interfaces/DoubleLinkedList.h"
#include "domain/interfaces/Game.h"
#include "domain/interfaces/Keyboard.h"
#include "services/GameService.h"
#include <windows.h>

using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8);

    KeyboardState kb;
    Game game;
    initKeyboard(kb, 0, CARDS_COUNT - 1, 0, 2, 2);

    start(game);

    cout << "Bem-vindo ao jogo da memória, " << game.playerOne.name << " e " << game.playerTwo.name << "!\n";
    cout << "O jogo tem " << game.rodadas << " rodadas.\n";
    
    cin.get();
    cout << "\n";
        initKeyboard(kb, 0, size(game.cards) - 1, 0, 2, 2);

        int currentPlayer = 1;

        while(size(game.cards) > 0){
            string status = string("Vez de: ") + (currentPlayer == 1 ? game.playerOne.name : game.playerTwo.name)
                + " | " + game.playerOne.name + ": " + to_string(game.playerOne.points)
                + " - " + game.playerTwo.name + ": " + to_string(game.playerTwo.points)
                + " | Rodadas restantes: " + to_string(game.rodadas);

            drawConsole(kb, game.cards, status);

            int sel1 = runInteractiveMenu(kb, game.cards, status);
            Nodo<Card>* node1 = game.cards.start;
            for(int i = 0; i < sel1 && node1 != NULL; i++) node1 = node1->next;
            if(node1 == NULL) continue;
            node1->element.state = State::VIRADA;
            drawConsole(kb, game.cards, status);

            int sel2;
            Nodo<Card>* node2 = NULL;
            do{
                sel2 = runInteractiveMenu(kb, game.cards, status);
                if(sel2 == sel1){
                    drawConsole(kb, game.cards, string("Seleção inválida: escolha uma posicao diferente da primeira.") + " | " + status);
                    cin.get();
                    continue;
                }
                node2 = game.cards.start;
                for(int i = 0; i < sel2 && node2 != NULL; i++) node2 = node2->next;
                if(node2 == NULL){
                    drawConsole(kb, game.cards, string("Selecao invalida: posicao fora do tabuleiro.") + " | " + status);
                    cin.get();
                }
            } while(node2 == NULL || sel2 == sel1);
            node2->element.state = State::VIRADA;
            drawConsole(kb, game.cards, status);

                if(node1->element.parIdentificador == node2->element.identificador
                    || node2->element.parIdentificador == node1->element.identificador){
                Player* p = (currentPlayer == 1) ? &game.playerOne : &game.playerTwo;
                add(p->cards, node1->element);
                add(p->cards, node2->element);

                if(sel1 > sel2){
                    remove(game.cards, sel1);
                    remove(game.cards, sel2);
                } else {
                    remove(game.cards, sel2);
                    remove(game.cards, sel1);
                }

                int newMax = (size(game.cards) > 0) ? (size(game.cards) - 1) : 0;
                initKeyboard(kb, 0, newMax, 0, kb.visual_stride, kb.visual_offset);

                game.rodadas = (game.rodadas > 0) ? game.rodadas - 1 : 0;
                p->points += 10;
                string okMsg = string("Par encontrado! ") + p->name + " ganhou duas cartas.";
                cin.get();
                drawConsole(kb, game.cards, okMsg + " | " + status);
                _getch();
            } else {
                drawConsole(kb, game.cards, string("Olha, voce nao formou um par") + " | " + status);
                _getch();
                node1->element.state = State::OCULTA;
                node2->element.state = State::OCULTA;
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }

        cout << "Jogo encerrado." << "\n";
        return 0;
}