#include <iostream>
#include <windows.h>
#include <conio.h>
#include "../include/interfaces/Game.h"
#include "../include/interfaces/Keyboard.h"

using namespace std;

string getPlayerName(int playerNum) {
    string name;
    cout << "Digite o nome do jogador " << playerNum << ": ";
    getline(cin, name);
    while(name.empty()) {
        cout << "O nome do jogador não pode ficar vazio!\nDigite novamente o nome do jogador " << playerNum << ": ";
        getline(cin, name);
    }
    return name;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    KeyboardState keyboardState;

    start(game);

    game.playerOne.name = getPlayerName(1);
    game.playerOne.points = 0;
    create(game.playerOne.effectInv.effects);

    game.playerTwo.name = getPlayerName(2);
    game.playerTwo.points = 0;
    create(game.playerTwo.effectInv.effects);

    initKeyboard(keyboardState, 0, size(game.cards) - 1, 0, 2, 2);

    cout << "Bem-vindo ao jogo da memória!\n";
    cout << game.playerOne.name << " vs " << game.playerTwo.name << "\n";
    cout << "Total de cartas: " << size(game.cards) << "\n";
    cout << "Pressione uma tecla para começar...\n";
    cin.get();

    int playerAtual = 1;
    int cartasEncontradas = 0;
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
                       + " | " + game.playerOne.name + ": " + to_string(game.playerOne.points)
                       + " - " + game.playerTwo.name + ": " + to_string(game.playerTwo.points);

        drawConsole(keyboardState, game.cards, status);

        if(!canPlay) {
            cout << jogadorAtual->name << " não pode jogar neste turno!\n";
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
            cout << "Erro ao selecionar carta 1!\n";
            cin.get();
            continue;
        }

        node1->element.state = State::VIRADA;
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

        node2->element.state = State::VIRADA;
        drawConsole(keyboardState, game.cards, status);

        if(isPair(node1->element, node2->element)) {
            cout << "PAR ENCONTRADO!\n";

            playerAtual == 1 ? game.playerOne.points += 10 : game.playerTwo.points += 10;
            cartasEncontradas += 2;

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

            node1->element.state = State::OCULTA;
            node2->element.state = State::OCULTA;

            bool card1Removed = false;
            if(node1->element.type == Type::BONUS || node1->element.type == Type::PENALIDADE) {
                EffectDef effect = createEffect(node1->element);
                if(!effect.name.empty())
                    cout << "Efeito ativado: " << effect.name << "\n";
                applyEffect(*jogadorAtual, effect);
                remove(game.cards, pos1);
                card1Removed = true;
            }

            if(node2->element.type == Type::BONUS || node2->element.type == Type::PENALIDADE) {
                EffectDef effect = createEffect(node2->element);
                if(!effect.name.empty())
                    cout << "Efeito ativado: " << effect.name << "\n";
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
    cout << game.playerOne.name << ": " << game.playerOne.points << " pontos\n";
    cout << game.playerTwo.name << ": " << game.playerTwo.points << " pontos\n\n";

    if(game.playerOne.points > game.playerTwo.points) {
        cout << "Vencedor: " << game.playerOne.name << "!\n";
    } else if(game.playerTwo.points > game.playerOne.points) {
        cout << "Vencedor: " << game.playerTwo.name << "!\n";
    } else {
        cout << "Empate!\n";
    }

    cout << "\nPressione uma tecla para sair...\n";
    cin.get();

    return 0;
}
