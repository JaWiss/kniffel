#ifndef BOTREGISTRY_H
#define BOTREGISTRY_H

#include "../utilities/sheet.h"
#include "../utilities/diceRollResult.h"

typedef diceRollResult (*BotMoveFunc)(Sheet, int, int*);

typedef struct {
    const char* name;
    BotMoveFunc func;
} BotEntry;

// Bot-Funktionen, die in der Tabelle registriert werden
diceRollResult randomBot(Sheet sheet,int rollNumber, int* dice);
diceRollResult improvedRandomBot(Sheet sheet,int rollNumber, int* dice);

BotMoveFunc findBotByName(const char* name);
void printBotNames();

#endif