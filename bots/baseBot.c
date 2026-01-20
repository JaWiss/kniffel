
#include "../utilities/sheet.h"
#include "../utilities/calculations.h"

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

int evalDiceRoll(int* diceThrow, int rollNumber, Sheet sheet) {
    int currentscore = calculateScoreForEveryField(diceThrow, sheet);
    
    return 0;
}
