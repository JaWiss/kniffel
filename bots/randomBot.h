#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "../utilities/diceRollResult.h"
#include "../utilities/sheet.h"

diceRollResult randomBot(Sheet sheet, int rollNumber, int* diceThrow);
int chooseRandomMove();
char* rerollRandomDice();
int enterRandomValues(Sheet, int*);

#endif