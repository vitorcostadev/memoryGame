/*
GAME_H

Nesta header estão definidas todas as estruturas e
subrotinas relacionadas ao jogo.

struct Game -> Armazena os dados do jogo, incluindo os jogadores, o número de rodadas e o
tabuleiro de cartas.

getEmoji(CardName name) -> Retorna o emoji correspondente ao nome da carta.
generateMapEmoji(const Tabuleiro &tab, int cols = 5) -> Gera uma representação em string do tabuleiro
de cartas usando emojis, organizados em colunas.
isPair(Card c1, Card c2) -> Verifica se duas cartas formam um par.
start(Game &game) -> Inicializa o jogo, configurando os jogadores e o tabuleiro.
createEffect(Card card) -> Cria uma definição de efeito com base na carta fornecida.
removeFirstPenalty(Player &player) -> Remove a primeira penalidade ativa do inventário do jogador.
applyEffect(Player &player, EffectDef eff) -> Aplica um efeito ao jogador, adicionando-o ao inventário do mesmo.
processEffects(Player &player) -> Processa os efeitos ativos do jogador, atualizando suas durações e removendo os que expiraram.
hasActiveEffect(Player &player, EffectType type) -> Verifica se o jogador possui um efeito ativo do tipo especificado e
retorna seu índice, ou -1 se não encontrado.
*/
#ifndef Game_H
#define Game_H
#define CARDS_COUNT 33
#define MAX_ROUNDS 30

#include <iostream>
#include <string>
#include "DoubleLinkedList.h"
#include "../models/Card.h"
#include "../models/Player.h"

struct Game
{
    Player playerOne, playerTwo;
    unsigned rodadas;
    Tabuleiro cards;
};


struct CardEmojis
{
    string table[20] =
    {
        "\xF0\x9F\x8D\x8E", 
        "\xF0\x9F\x8F\xAB",
        "\xE2\xAD\x90",    
        "\xE2\x8F\xB0",    
        "\xF0\x9F\x92\x80", 
        "\xF0\x9F\x93\x9A", 
        "\xF0\x9F\x8E\xAE", 
        "\xF0\x9F\x8E\xB2", 
        "\xF0\x9F\x94\x91",
        "\xE2\x9A\xA1",
        "\xF0\x9F\x92\xA5",
        "\xF0\x9F\x9A\xAB", 
        "\xF0\x9F\x8C\x99", 
        "\xF0\x9F\x8E\xB5", 
        "\xE2\x9D\xA4",     
        "\xF0\x9F\x91\x91", 
        "\xF0\x9F\x90\x9F",
        "\xF0\x9F\x8C\xAB", 
        "\xF0\x9F\x94\x92", 
        "\xE2\x8F\xB3"      
    };
} cardEmojis;

string getEmoji(CardName name)
{
    return cardEmojis.table[(int)name];
}

string generateMapEmoji(const Tabuleiro &tab, int cols = 5)
{
    /*
    Constroi o menu dos emojis organizando em colunas que
    por default, assume o valor 5.
    */
    string emojiMap;
    Node<Card>* current = tab.start;
    int idx = 0;
    while(current != NULL)
    {
        if(current->element.state == State::OCULTA)
        {
            emojiMap += "?";
        }
        else
        {
            emojiMap += getEmoji(current->element.name);
        }
        idx++;
        if(idx % cols == 0) emojiMap += "\n";
        else emojiMap += " ";
        current = current->next;
    }
    return emojiMap;
}

bool isPair(Card c1, Card c2)
{
    /*
    Verifica se a carta 1 é igual a carta 2 ou vice-versa.
    */
    return (c1.parIdentificador == c2.identificador ||
            c2.parIdentificador == c1.identificador);
}

void start(Game &game)
{
    /*
    Inicializa o jogo, configurando os jogadores e o tabuleiro.
    */
    game.rodadas = 0;
    game.playerOne.points = 0;
    game.playerTwo.points = 0;
    create(game.playerOne.effectInv.effects);
    create(game.playerTwo.effectInv.effects);
    createTabuleiro(game.cards);
}

EffectDef createEffect(Card card)
{
    /*
    Cria um tipo de dado EffectDef (Definição de Efeito)
    Baseado na carta passada como parametro
    para no fim, retornar um EffectDef construído.
    */
    EffectDef effect;
    switch (card.name)
    {
    case CardName::PROIBIDO:
        effect.type = EFFECT_SKIP_TURN;
        effect.duration = 1;
        effect.name = "Bloqueio de jogada";
        effect.description = "A proxima rodada do jogador é ignorada.";
        break;
    case CardName::SKULL:
        effect.type = EFFECT_SKIP_TURN;
        effect.duration = 1;
        effect.name = "Paralisia";
        effect.description = "A proxima rodada do jogador é bloqueada.";
        break;
    case CardName::STAR:
        effect.type = EFFECT_EXTRA_TURN;
        effect.duration = 1;
        effect.name = "Jogada extra";
        effect.description = "Jogador ganha mais uma jogada.";
        break;
    case CardName::RAIO:
        effect.type = EFFECT_REMOVE_PENALTY;
        effect.duration = 0;
        effect.name = "Remoção de penalidade";
        effect.description = "Remove uma penalidade ativa do inventario.";
        break;
    case CardName::FOG:
        effect.type = EFFECT_LIMIT_VISION;
        effect.duration = 2;
        effect.name = "Limite de visão";
        effect.description = "O jogador só pode virar uma carta.";
        break;
    case CardName::LOCK:
        effect.type = EFFECT_CARD_BLOCK;
        effect.duration = 2;
        effect.name = "Bloqueio de carta";
        effect.description = "Uma carta específica não pode ser virada por 2 rodadas.";
        break;
    case CardName::HOURGLASS:
        effect.type = EFFECT_EXTRA_TIME;
        effect.duration = 2;
        effect.name = "Tempo extra";
        effect.description = "Revela uma carta oculta aleatória para memorizar antes da proxima jogada.";
        break;
    default:
        effect.type = EFFECT_EXTRA_TURN;
        effect.duration = 0;
        effect.name = "";
        effect.description = "";
        break;
    }
    return effect;
}

void removeFirstPenalty(Player &player)
{
    /*
    Removendo a primeira penalidade da lista
    do player passado por referencia.
    */
    Node<ActiveEffect>* current = player.effectInv.effects.start;
    int index = 0;
    while(current != NULL)
    {
        if(current->element.definition.type == EFFECT_SKIP_TURN)
        {
            cout << player.name << ": penalidade removida por bônus: "
                 << current->element.definition.name << "\n";
            remove(player.effectInv.effects, index);
            return;
        }
        current = current->next;
        index++;
    }
    cout << player.name << ": nenhuma penalidade ativa para remover." << endl;
}

void applyEffect(Player &player, EffectDef eff)
{
    /*
    Aplica um efeito ao jogador, adicionando-o ao inventário do mesmo.
    */
    if(eff.type == EFFECT_REMOVE_PENALTY)
    {
        /*
        Se o tipo do efeito é remover penalidade
        nesse caso, é só remover a primeira penalidade
        ativa (remove apenas uma, e nao todas)
        */
        removeFirstPenalty(player);
        return;
    }
    if(eff.name.empty()) return;
    ActiveEffect active;
    active.definition = eff;
    active.rmDuration = eff.duration;
    /*
    E se caso passar pelos checks, cria um tipo de dado
    ActiveEffect e adiciona no inventario do player.
    */
    add(player.effectInv.effects, active,
        player.effectInv.effects.cardinalidade);
}

bool processEffects(Player &player)
{
    /*
    Processa os efeitos que estão ativos no inventário do player, atualizando suas durações
    e removendo os que expiraram. Retorna um booleano indicando se o jogador pode jogar ou não,
    baseado na presença de efeitos do tipo skip turn.
    */
    bool canPlay = true;
    int i = 0;
    Node<ActiveEffect>* node = player.effectInv.effects.start;

    while(node != NULL)
    {
        Node<ActiveEffect>* next = node->next;

        if(node->element.definition.type == EFFECT_SKIP_TURN)
            /*
            Se o tipo do efeito for skip turn, simplesmente atualiza
            a variavel canPlay para false para depois retornar.
            */
            canPlay = false;

        node->element.rmDuration--;

        if(node->element.rmDuration <= 0)
        {
            /*
            Se a duração chegou a zero, o efeito expirou e
            deve ser removido da lista de efeitos ativos.
            */
            cout << player.name << ": efeito expirou: "
                 << node->element.definition.name << endl;
            remove(player.effectInv.effects, i);
        }
        else
        {
            i++;
        }

        node = next;
    }

    return canPlay;
}

int hasActiveEffect(Player &player, EffectType type)
{
    /*
    Retorna o indice de onde está presente o efeito
    a ser buscado, e caso o mesmo não exista, retorna -1.
    */
    Node<ActiveEffect>* current = player.effectInv.effects.start;
    int index = 0;

    while(current != NULL)
    {
        if(current->element.definition.type == type)
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

#endif
