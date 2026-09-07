
#include "../utilities/diceRollResult.h"
#include "../utilities/sheet.h"
#include <time.h>

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
#define REROLL 0
#define ENTER 1

int evalDiceRoll(int* diceThrow, int rollNumber, Sheet sheet) {
    srand(time(NULL));
    diceRollResult result;
    if(rollNumber == 3) {
        result.status = ENTER;
        result.data.field = enterRandomValues(&sheet);
    } else {
        if(chooseRandomMove() == 1) {
            result.status = ENTER;
            result.data.field = enterRandomValues(&sheet);
        } else {
            result.status = ENTER;
            result.data.dice = rerollRandomDice(diceThrow);
        }
    }
    return 0;
}

int chooseRandomMove() {
    return (rand() % 2); 
}

int* rerollRandomDice(int* diceThrow) {
    int* diceToBeRerolled = malloc(5 * sizeof(int));    
    for(int i = 0; i < 5; i++) {
        diceToBeRerolled[i] = (rand() % 2);
    }
    return diceToBeRerolled;
}


int enterRandomValues(Sheet* sheet) {

}