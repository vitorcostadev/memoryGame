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
        cout << "Nome não pode estar vazio! Digite o nome do jogador " << playerNum << ": ";
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
    
    while(size(game.cards) > 0) {
        Player* jogadorAtual = (playerAtual == 1) ? &game.playerOne : &game.playerTwo;
        
        bool canPlay = processEffects(*jogadorAtual);
        
        string status = string("Vez de: ") + jogadorAtual->name 
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
        
        cout << jogadorAtual->name << ", selecione a PRIMEIRA carta (A/D + ENTER):\n";
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
        drawConsole(keyboardState, game.cards, status + " | Primeira carta selecionada");
        cin.get();
        
        int pos2 = -1;
        Node<Card>* node2 = NULL;
        
        do {
            cout << jogadorAtual->name << ", selecione a SEGUNDA carta (diferente da primeira):\n";
            pos2 = runInteractiveMenu(keyboardState, game.cards, status);
            
            if(pos2 == pos1) {
                drawConsole(keyboardState, game.cards, status + " | ERRO: escolha uma posição diferente!");
                cin.get();
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
        drawConsole(keyboardState, game.cards, status + " | Segunda carta selecionada");
        cin.get();
        
        if(isPair(node1->element, node2->element)) {
            cout << "✓ PAR ENCONTRADO!\n";
            
            playerAtual == 1 ? game.playerOne.points += 10 : game.playerTwo.points += 10;
            cartasEncontradas += 2;

            if(node1->element.type == Type::BONUS || node1->element.type == Type::PENALIDADE) {
                EffectDef effect = createEffect(node1->element);
                applyEffect(*jogadorAtual, effect);
                cout << "Efeito aplicado: " << effect.name << "\n";
            }
            
            if(node2->element.type == Type::BONUS || node2->element.type == Type::PENALIDADE) {
                EffectDef effect = createEffect(node2->element);
                applyEffect(*jogadorAtual, effect);
                cout << "Efeito aplicado: " << effect.name << "\n";
            }

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
            cout << "✗ Par não encontrado!\n";
            cout << "Pressione uma tecla para continuar...\n";
            cin.get();
            
            node1->element.state = State::OCULTA;
            node2->element.state = State::OCULTA;
            
            playerAtual = (playerAtual == 1) ? 2 : 1;
        }
    }
    
    system("cls");
    cout << "╔════════════════════════════════════╗\n";
    cout << "║        JOGO ENCERRADO!             ║\n";
    cout << "╚════════════════════════════════════╝\n\n";
    
    cout << "Placar Final:\n";
    cout << game.playerOne.name << " (Jogador 1): " << game.playerOne.points << " pontos\n";
    cout << game.playerTwo.name << " (Jogador 2): " << game.playerTwo.points << " pontos\n\n";
    
    if(game.playerOne.points > game.playerTwo.points) {
        cout << "🏆 VENCEDOR: " << game.playerOne.name << "!\n";
    } else if(game.playerTwo.points > game.playerOne.points) {
        cout << "🏆 VENCEDOR: " << game.playerTwo.name << "!\n";
    } else {
        cout << "🤝 EMPATE!\n";
    }
    
    cout << "\nPressione uma tecla para sair...\n";
    cin.get();
    
    return 0;
}
