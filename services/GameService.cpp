#include <iostream>
#include <string>
#include "../domain/interfaces/Game.h"
#include "../domain/interfaces/List.h"

using namespace std;

void createPlayers(List<Player, 2> &players, Game &game){
    int cont = 0;

    while(cont < 2){
        do{
            cout << "Digite o nome do " << cont+1 << " jogador(a): ";
            string name;
            getline(cin, name);

            Player player = get(players, cont);
            player.name = name;
            player.points = 0;
            cont++;

        } while(get(players, cont).name.empty());
    }

    setPlayers(game, get(players, 0), get(players, 1));
}