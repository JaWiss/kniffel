
#include "../utilities/sheet.h"
#include "../utilities/calculations.h"
#include "../utilities/diceRollResult.h"

#include <stdlib.h>
#include <stdio.h>

#define ONE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define FIVE 4
#define SIX 5
#define THREESOME 6
#define FOURSOME 7
#define FULLHOUSE 8
#define SMALLSTRAIGHT 9
#define BIGSTRAIGHT 10
#define KNIFFEL 11
#define CHANCE 12

diceRollResult baseBot(Sheet sheet, int rollNumber, int* diceThrow) {
    diceRollResult result;
    double* currentScorePerLikelyhood = malloc(sizeof(double)*13);
    int* currentscore = calculateScoreForEveryField(diceThrow, sheet);
    double* lowerBaseLikelyhoods = baseLikleyhoodLower(); 
    for(int i = 0; i < FULLHOUSE; i++) {
        if(currentscore[i] > 0) {
            currentScorePerLikelyhood[i] = (double)currentscore[i] / upperLikelyHood(currentscore[i], i);
        } else {
            currentScorePerLikelyhood[i] = 0.0;
        }
    }
    for(int j = FULLHOUSE; j < CHANCE; j++) {
        if(currentscore[j] > 0) {
            currentScorePerLikelyhood[j] = ((double)currentscore[j] * currentscore[j] ) / lowerBaseLikelyhoods[j-6];
        } else {
            currentScorePerLikelyhood[j] = 0.0;
        }
    }
    currentScorePerLikelyhood[CHANCE] = currentscore[CHANCE] / (chanceLikelyhood(currentscore[CHANCE]) * 10);
    double bestFieldScore = 0.0;
    int bestFieldIndex = 0;
    /*for(int l = 0; l < 5; l++) {
        printf("%d, ", diceThrow[l]);
    }*/
    int* legalEntries = malloc(13*sizeof(int));
    int numberOfLegalEntries = 0;
    int* possibleEntries = calculateScoreForEveryOpenField(diceThrow, sheet);
    for(int i = 0; i < 13;i++) {
        if(possibleEntries[i] >= -1) {
            legalEntries[numberOfLegalEntries] = i;
            numberOfLegalEntries++;
        }
    }
    //printf("\n");
    for(int k = 0; k < numberOfLegalEntries; k++) {
        //printf("Feld: %d, Score: %f\n",legalEntries[k], currentScorePerLikelyhood[legalEntries[k]]);
        if(currentScorePerLikelyhood[legalEntries[k]] > bestFieldScore) {
            bestFieldScore = currentScorePerLikelyhood[legalEntries[k]];
            bestFieldIndex = k;
        }
    }
    result.status = ENTER;
    result.data.field = legalEntries[bestFieldIndex];
    //printf("CHOSEN FIELD :%d\n", result.data.field);
    free(possibleEntries);
    free(currentscore);
    free(currentScorePerLikelyhood);
    free(lowerBaseLikelyhoods);
    return result;
}
