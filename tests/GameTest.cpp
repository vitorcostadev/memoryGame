#include <iostream>
#include "../domain/interfaces/Game.h"
#include "../domain/models/Models.h"
#include "../domain/interfaces/Reader.h"

using namespace std;

int main(){
    //Card cardOne = {CardName::APPLE, 1, State::OCULTA, Type::NORMAL}, cardTwo = {CardName::APPLE, 7,State::OCULTA, Type::NORMAL};
    Reader reader;
    create(reader, "../domain/models/cards.csv");

    Game game;
    createTabuleiro(game.cards);

    toString(game.cards);

}