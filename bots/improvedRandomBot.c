
#include "../utilities/diceRollResult.h"
#include "../utilities/sheet.h"
#include "../utilities/calculations.h"
#include "randomBot.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ONE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define FIVE 4
#define SIX 5
#define FULLHOUSE 6
#define THREESOME 7
#define FOURSOME 8
#define SMALLSTRAIGHT 9
#define BIGSTRAIGHT 10
#define KNIFFEL 11
#define CHANCE 12

int enterRandomValuesImproved(Sheet, int*);

diceRollResult improvedRandomBot(Sheet sheet, int rollNumber, int* diceThrow) {
    diceRollResult result;
    if(rollNumber == 3) {
        result.status = ENTER;
        result.data.field = enterRandomValuesImproved(sheet, diceThrow);
    } else {
        if(chooseRandomMove() == 1) {
            result.status = ENTER;
            result.data.field = enterRandomValuesImproved(sheet, diceThrow);
        } else {
            result.status = REROLL;
            result.data.dice = rerollRandomDice(diceThrow);
        }
    }
    return result;
}

int enterRandomValuesImproved(Sheet sheet, int* diceThrow) {
    int* possibleEntries = calculateScoreForEveryOpenField(diceThrow, sheet);
    int* legalEntries = malloc(13*sizeof(int));
    int numberOfLegalEntries = 0;
    for(int i = 0; i < 13;i++) {
        if(possibleEntries[i] >= 0) {
            legalEntries[numberOfLegalEntries] = i;
            numberOfLegalEntries++;
        }
    }
    if(numberOfLegalEntries == 0) {
        for(int i = 0; i < 13;i++) {
            if(possibleEntries[i] >= -1) {
                legalEntries[numberOfLegalEntries] = i;
                numberOfLegalEntries++;
            }
        }
    }
    if(numberOfLegalEntries == 0) {
        fprintf(stderr, "Fehler: Keine legalen Felder mehr im Sheet vorhanden.\n");
        free(legalEntries);
        free(possibleEntries);
        exit(EXIT_FAILURE);
    }
    int index = (rand() % numberOfLegalEntries);
    int entry = legalEntries[index];
    free(legalEntries);
    free(possibleEntries);
    return entry;
}