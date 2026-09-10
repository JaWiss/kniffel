#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "../utilities/diceRollResult.h"
#include "../utilities/sheet.h"

diceRollResult greedyRandomBot(Sheet sheet, int rollNumber, int* diceThrow);

#endif