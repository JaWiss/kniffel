
#include "../utilities/diceRollResult.h"
#include "../utilities/sheet.h"
#include "../utilities/calculations.h"
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

int chooseRandomMove();
int* rerollRandomDice();
int enterRandomValues(Sheet, int*);

diceRollResult randomBot(Sheet sheet, int rollNumber, int* diceThrow) {
    diceRollResult result;
    if(rollNumber == 3) {
        result.status = ENTER;
        result.data.field = enterRandomValues(sheet, diceThrow);
    } else {
        if(chooseRandomMove() == 1) {
            result.status = ENTER;
            result.data.field = enterRandomValues(sheet, diceThrow);
        } else {
            result.status = REROLL;
            result.data.dice = rerollRandomDice(diceThrow);
        }
    }
    return result;
}

int chooseRandomMove() {
    return (rand() % 2); 
}

int* rerollRandomDice() {
    int* diceToBeRerolled = malloc(5 * sizeof(int));    
    for(int i = 0; i < 5; i++) {
        diceToBeRerolled[i] = (rand() % 2);
    }
    return diceToBeRerolled;
}


int enterRandomValues(Sheet sheet, int* diceThrow) {

    printf("Dice throw: ");

    for (int i = 0; i < 5; i++) {
        printf("%d ", diceThrow[i]);
    }

    printf("\n");
    printf("11\n");
    int* possibleEntries = calculateScoreForEveryOpenField(diceThrow, sheet);
    printf("AA: %d\n",possibleEntries[0]);
    printf("12\n");
    int* legalEntries = malloc(13*sizeof(int));
    printf("13\n");
    int numberOfLegalEntries = 0;
    for(int i = 0; i < 13;i++) {
        printf("ENTRY: %d, WERT: %d\n", i, possibleEntries[i]);
        if(possibleEntries[i] >= 0) {
            legalEntries[numberOfLegalEntries] = i;
            numberOfLegalEntries++;
        }
    }
    printf("14\n");
    if(numberOfLegalEntries == 0) {
        fprintf(stderr, "Fehler: Keine legalen Felder mehr im Sheet vorhanden.\n");
        free(legalEntries);
        free(possibleEntries);
        exit(EXIT_FAILURE);
    }
    printf("15\n");
    int index = (rand() % numberOfLegalEntries);
    int entry = legalEntries[index];
    free(legalEntries);
    free(possibleEntries);
    printf("16\n");
    return entry;
}