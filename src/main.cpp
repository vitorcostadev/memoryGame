/*
Nomes: Vitor Kawã Pedrosa Da Costa, Fernando Nunes Francisco e Arthur Abreu

Bibliotecas usadas:

conio.h: Para captura de entrada do teclado sem necessidade de pressionar Enter.
windows.h: Para manipulação do console, como limpar a tela e configurar a codificação de caracteres.

Estrutura do projeto:

include/
    models/
        Card.h: Define a estrutura de uma carta, incluindo seu nome, tipo, estado e identificadores.
        Enums.h: Define os enums usados no jogo, como CardName, Type e State.
        Player.h: Define a estrutura de um jogador, incluindo seus pontos, nome e inventário de efeitos.
    interfaces/
        DoubleLinkedList.h: Implementação de uma lista duplamente ligada genérica.
        Game.h: Define a estrutura do jogo e as funções para iniciar o jogo e processar os efeitos dos jogadores.
        Keyboard.h: Define a estrutura do estado do teclado e as funções para inicializar o teclado e desenhar o console.
    src/
        main.cpp: Contém a função principal do jogo, onde a lógica do jogo é implementada, incluindo a interação com o usuário e o fluxo do jogo.

Referencias para implementação:

- https://cplusplus.com/ : Para consulta de sintaxe e funcionalidades da linguagem C++.
- Editores de codigo utilizados: VsCode & CodeBlocks
*/
#include <iostream>
#include <windows.h>
#include "../include/interfaces/Game.h"
#include "../include/interfaces/Keyboard.h"

using namespace std;

void getPlayerName(Player &player, int playerNum) {
    string name;    
    cout << "Digite o nome do jogador " << playerNum << ": ";
    getline(cin, name);
    while(name.empty()) {
        cout << "O nome do jogador não pode ficar vazio!\nDigite novamente o nome do jogador " << playerNum << ": ";
        getline(cin, name);
    }
    setPlayerName(player, name);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    KeyboardState keyboardState;

    start(game);

    getPlayerName(game.playerOne, 1);
    getPlayerName(game.playerTwo, 2);

    initKeyboard(keyboardState, 0, size(game.cards) - 1, 0, 2, 2);

    cout << "Bem-vindo ao jogo da memória!\n";
    cout << getPlayerName(game.playerOne) << " vs " << getPlayerName(game.playerTwo)  << endl;
    cout << "Total de cartas: " << size(game.cards) << "\n";
    cout << "Pressione uma tecla para começar...\n";
    cin.get();

    int playerAtual = 1;
    bool roundLimitReached = false;

    while(size(game.cards) > 0) {
        Player* jogadorAtual = (playerAtual == 1) ? &game.playerOne : &game.playerTwo;

        game.rodadas++;
        if(game.rodadas > (unsigned)MAX_ROUNDS) {
            roundLimitReached = true;
            break;
        }

        bool canPlay = processEffects(*jogadorAtual);

        string status = string("Rodada ") + to_string(game.rodadas) + "/" + to_string(MAX_ROUNDS)
                       + " | Vez de: " + jogadorAtual->name
                       + " | " + getPlayerName(game.playerOne) + ": " + to_string(game.playerOne.points)
                       + " - " + getPlayerName(game.playerTwo) + ": " + to_string(game.playerTwo.points)
                       + " | " + "Utilize A/D para mover o cursor e Enter para selecionar as cartas.";

        drawConsole(keyboardState, game.cards, status);

        if(!canPlay) {
            cout << getPlayerName(*jogadorAtual) << " não pode jogar neste turno!\n";
            cout << "Pressione uma tecla para continuar...\n";
            cin.get();
            playerAtual = (playerAtual == 1) ? 2 : 1;
            continue;
        }

        int pos1 = runInteractiveMenu(keyboardState, game.cards, status);

        Node<Card>* node1 = game.cards.start;
        for(int i = 0; i < pos1 && node1 != NULL; i++) {
            node1 = node1->next;
        }

        if(node1 == NULL) {
            cout << "Erro ao selecionar carta" << endl;
            cin.get();
            continue;
        }

        setCardState(node1->element, State::VIRADA);
        drawConsole(keyboardState, game.cards, status);

        int pos2 = -1;
        Node<Card>* node2 = NULL;

        do {
            pos2 = runInteractiveMenu(keyboardState, game.cards, status);

            if(pos2 == pos1) {
                drawConsole(keyboardState, game.cards, status + " | ERRO: escolha uma posição diferente!");
                continue;
            }

            node2 = game.cards.start;
            for(int i = 0; i < pos2 && node2 != NULL; i++) {
                node2 = node2->next;
            }

            if(node2 == NULL) {
                drawConsole(keyboardState, game.cards, status + " | ERRO: posição inválida!");
                cin.get();
            }
        } while(node2 == NULL || pos2 == pos1);

        setCardState(node2->element, State::VIRADA);
        drawConsole(keyboardState, game.cards, status);

        if(isPair(node1->element, node2->element)) {
            cout << "PAR ENCONTRADO!\n";

            playerAtual == 1 ? addPoints(game.playerOne, 10) : 
            addPoints(game.playerTwo, 10);

            if(pos1 > pos2) {
                remove(game.cards, pos1);
                remove(game.cards, pos2);
            } else {
                remove(game.cards, pos2);
                remove(game.cards, pos1);
            }

            if(size(game.cards) > 0) {
                initKeyboard(keyboardState, 0, size(game.cards) - 1, 0, 2, 2);
            }

            cout << "Pressione uma tecla para continuar...\n";
            cin.get();

        } else {
            cout << "Par não encontrado!\n";

            setCardState(node1->element, State::OCULTA);
            setCardState(node2->element, State::OCULTA);

            bool card1Removed = false;
            if(getCardType(node1->element) == Type::BONUS || getCardType(node1->element) == Type::PENALIDADE) {
                EffectDef effect = createEffect(node1->element);
                if(!effect.name.empty())
                    cout << "Efeito ativado: " << effect.name << endl;
                applyEffect(*jogadorAtual, effect);
                remove(game.cards, pos1);
                card1Removed = true;
            }

            if(getCardType(node2->element) == Type::BONUS || 
                getCardType(node2->element) == Type::PENALIDADE
            ) {

                EffectDef effect = createEffect(node2->element);

                if(!effect.name.empty())
                    cout << "Efeito ativado: " << effect.name << endl;
                applyEffect(*jogadorAtual, effect);

                int adjustedPos2 = (card1Removed && pos1 < pos2) ? pos2 - 1 : pos2;
                remove(game.cards, adjustedPos2);
            }

            if(size(game.cards) > 0) {
                initKeyboard(keyboardState, 0, size(game.cards) - 1, 0, 2, 2);
            }

            int extraIdx = hasActiveEffect(*jogadorAtual, EFFECT_EXTRA_TURN);
            if(extraIdx >= 0) {
                remove(jogadorAtual->effectInv.effects, extraIdx);
                cout << jogadorAtual->name << " ganhou uma jogada extra!\n";
            } else {
                playerAtual = (playerAtual == 1) ? 2 : 1;
            }

            cout << "Pressione uma tecla para continuar...\n";
            cin.get();
        }
    }

    system("cls");
    if(roundLimitReached) {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║   LIMITE DE JOGADAS ATINGIDO!    ║\n";
        cout << "╚════════════════════════════════════╝\n\n";
        cout << "Rodadas esgotadas! Nenhum jogador encontrou todos os pares.\n\n";
    } else {
        cout << "╔════════════════════════════════════╗\n";
        cout << "║        JOGO ENCERRADO!             ║\n";
        cout << "╚════════════════════════════════════╝\n\n";
    }

    cout << "Resultado Final:\n";
    cout << getPlayerName(game.playerOne) << ": " << getPlayerPoints(game.playerOne) << " pontos\n";
    cout << getPlayerName(game.playerTwo) << ": " << getPlayerPoints(game.playerTwo) << " pontos\n\n";

    if(getPlayerPoints(game.playerOne) > getPlayerPoints(game.playerTwo)) {
        cout << "Vencedor: " << getPlayerName(game.playerOne) << "!\n";
    } else if(getPlayerPoints(game.playerTwo) > getPlayerPoints(game.playerOne)) {
        cout << "Vencedor: " << getPlayerName(game.playerTwo) << "!\n";
    } else {
        cout << "Empate!\n";
    }

    cout << "\nPressione uma tecla para sair...\n";
    cin.get();

    destroy(game.cards);
    destroy(game.playerOne.effectInv.effects);
    destroy(game.playerTwo.effectInv.effects);

    return 0;
}
