
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
    double* scoreByLikleyhoodOfImprovment = malloc(sizeof(double)*13);
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
    double bestFieldScore = -100000.0;
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

    double* likelyhoodsOfImprovementLower  = likelyhoodOfImprovementLower(diceThrow);
    scorePerLikelyHoodUpper(diceThrow, scoreByLikleyhoodOfImprovment);
    result.status = ENTER;
    result.data.field = legalEntries[bestFieldIndex];
    //printf("CHOSEN FIELD :%d\n", result.data.field);
    free(possibleEntries);
    free(currentscore);
    free(currentScorePerLikelyhood);
    free(lowerBaseLikelyhoods);
    free(likelyhoodsOfImprovementLower);
    return result;
}

void scorePerLikelyHoodUpper(int* diceRoll, double* likelyhoodOfImprovement, double* res) {

}

void scorePerLikelyHoodUpper(int* diceRoll, double* res) {
    for(int i = 0; i < 6; i++) {
        int possibleAdditionRolls = 5 - numberOfOccurences(diceRoll, i + 1);
        double score = 0.0;
        for(int j = 1; j <= possibleAdditionRolls; j++) {
            double likelyHood = 0.0;
            if( possibleAdditionRolls > j) {
                likelyHood = (fak(possibleAdditionRolls) / (fak(possibleAdditionRolls - j) * fak(j))) * pow(5, possibleAdditionRolls - j) / pow(6,possibleAdditionRolls);
            } else {
                likelyHood = 1 / pow(6, possibleAdditionRolls);
            }
            double points = j * (i+1);
            points += (points/63) * 35;
            score += points / likelyHood;
        } 
        res[i] = score;
    }
}

int pow(int base, int exponent) {
    int score = 1;
    for(int i = 0; i < exponent; i++) {
        score = base * score; 
    }    
    return score;
}

int fak(int base) {
    int result = 1;
    while(base > 0) {
        result = result * base;
        base--;
    }
    return result;
}

int numberOfOccurences(int* diceRoll, int number) {
    int occurences = 0;
    for(int i = 0; i < 5; i++) {
        if(diceRoll[i] == number) {
            occurences++;
        }
    }
    return occurences;
}

static int hasStraight(const int *c, int len) {
    int run = 0, best = 0;
    for (int i = 0; i < 6; i++) {
        if (c[i] > 0) { run++; if (run > best) best = run; }
        else run = 0;
    }
    return best >= len;
}

/* beste Chance auf eine Straße der Länge len mit einem Neuwurf */
static double straightChance(const int *diceRoll, int len) {
    int own[6] = {0};
    for (int i = 0; i < 5; i++) own[diceRoll[i] - 1]++;
    if (hasStraight(own, len)) return 0.0;      /* schon vorhanden */

    double best = 0.0;
    for (int mask = 1; mask < 32; mask++) {     /* Bit i = Würfel i neu würfeln */
        int kept[6] = {0}, r = 0;
        for (int i = 0; i < 5; i++) {
            if (mask & (1 << i)) r++;
            else kept[diceRoll[i] - 1]++;
        }
        int total = 1;
        for (int k = 0; k < r; k++) total *= 6;

        int hits = 0;
        for (int o = 0; o < total; o++) {
            int c[6];
            for (int i = 0; i < 6; i++) c[i] = kept[i];
            int t = o;
            for (int k = 0; k < r; k++) { c[t % 6]++; t /= 6; }
            if (hasStraight(c, len)) hits++;
        }
        double p = (double)hits / total;
        if (p > best) best = p;
    }
    return best;
}

double* likelyhoodOfImprovementLower(int* diceRoll) {
    double* likelyhoods = malloc(7 * sizeof(double));
    for (int i = 0; i < 7; i++) likelyhoods[i] = 0.0;

    int count[6] = {0};
    int highestCount = 0;
    int numberOfdoubles = 0;

    for (int i = 0; i < 5; i++) {
        if (diceRoll[i] >= 1 && diceRoll[i] <= 6) count[diceRoll[i] - 1]++;
    }
    for (int j = 0; j < 6; j++) {
        if (count[j] > highestCount) highestCount = count[j];
        if (count[j] == 2) numberOfdoubles++;
    }

    /* Dreierpasch */
    if (highestCount >= 3)       likelyhoods[0] = 0.0;
    else if (highestCount == 2)  likelyhoods[0] = 1.0 - 125.0 / 216.0;
    else                         likelyhoods[0] = 0.1319;

    /* Viererpasch */
    if (highestCount >= 4)       likelyhoods[1] = 0.0;
    else if (highestCount == 3)  likelyhoods[1] = 1.0 - 25.0 / 36.0;
    else if (highestCount == 2)  likelyhoods[1] = 16.0 / 216.0;
    else                         likelyhoods[1] = 21.0 / 1296.0;

    /* Full House */
    if (highestCount == 1) {
        likelyhoods[2] = 50.0 / 1296.0;                 /* ca. 0,0386 */
    } else if (highestCount == 2) {
        if (numberOfdoubles == 2) likelyhoods[2] = 1.0 / 3.0;
        else                      likelyhoods[2] = 5.0 / 54.0;
    } else if (highestCount == 3) {
        if (numberOfdoubles == 1) likelyhoods[2] = 0.0; /* schon Full House */
        else                      likelyhoods[2] = 1.0 / 6.0;
    } else if (highestCount == 4) {
        likelyhoods[2] = 1.0 / 6.0;
    } else {                                            /* Kniffel */
        likelyhoods[2] = 5.0 / 36.0;
    }

    /* Kleine und große Straße */
    likelyhoods[3] = straightChance(diceRoll, 4);
    likelyhoods[4] = straightChance(diceRoll, 5);

    /* Kniffel */
    if (highestCount == 1)       likelyhoods[5] = 1.0 / 1296.0;
    else if (highestCount == 2)  likelyhoods[5] = 1.0 / 216.0;
    else if (highestCount == 3)  likelyhoods[5] = 1.0 / 36.0;
    else if (highestCount == 4)  likelyhoods[5] = 1.0 / 6.0;
    else                         likelyhoods[5] = 0.0;

    return likelyhoods;   /* Aufrufer muss free() aufrufen */
}