#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sheet.h"
#include "helper.h"
#include "game.h"

#define ONE 0
#define TWO 1
#define THREE 2
#define FOUR 3
#define FIVE 4
#define SIX 5
#define FULLHOUSE 6
#define THREESOME 7
#define FOURSOME 8
#define LITTLESTREET 9
#define BIGSTREET 10
#define KNIFFEL 11
#define CHANCE 12

int checkscore(int score) {
    if(score > 0) {
        return score;
    }
    return 0;
}

int calculatelowerscore(Sheet playersheet) {
    int score = 0;
    score += checkscore(playersheet.threesome);
    score += checkscore(playersheet.foursome);
    score += checkscore(playersheet.fullhouse);
    score += checkscore(playersheet.littlestreet);
    score += checkscore(playersheet.bigstreet);
    score += checkscore(playersheet.kniffel);
    score += checkscore(playersheet.chance);
    return score;
}

int calculateupperscore(Sheet playersheet) {
    int score = 0;
    score += checkscore(playersheet.ones);
    score += checkscore(playersheet.twos);
    score += checkscore(playersheet.threes);
    score += checkscore(playersheet.fours);
    score += checkscore(playersheet.fives);
    score += checkscore(playersheet.sixes);
    if(score >= 63) {
        score += 35;
    }
    return score;
}

int calculatetotalscore(Sheet playersheet) {
    int score = 0;
    score += checkscore(playersheet.ones);
    score += checkscore(playersheet.twos);
    score += checkscore(playersheet.threes);
    score += checkscore(playersheet.fours);
    score += checkscore(playersheet.fives);
    score += checkscore(playersheet.sixes);
    if(score >= 63) {
        score += 35;
    }
    score += checkscore(playersheet.threesome);
    score += checkscore(playersheet.foursome);
    score += checkscore(playersheet.fullhouse);
    score += checkscore(playersheet.littlestreet);
    score += checkscore(playersheet.bigstreet);
    score += checkscore(playersheet.kniffel);
    score += checkscore(playersheet.chance);
    return score;
}

bool enterpointstosheet(Sheet* playersheet, int* dicethrow) {
    char input[10];
    bool hasenteredpoints = 0;
    printf("Gib an in welche Zeile du etwas eintragen willst. Das sind deine möglichen, offenen Zeilen:\n");
    findemptyrows(*playersheet, dicethrow);
    while(1) {
        scanf("%s", input);
        if(strcmp(input, "e") == 0) {
            enterpoints(ONE, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "z") == 0) {
            enterpoints(TWO, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "d") == 0) {
            enterpoints(THREE, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "v") == 0) {
            enterpoints(FOUR, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "f") == 0) {
            enterpoints(FIVE, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "s") == 0) {
            enterpoints(SIX, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "dp") == 0) {
            enterpoints(THREESOME, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "vp") == 0) {
            enterpoints(FOURSOME, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "fh") == 0) {
            enterpoints(FULLHOUSE, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "ks") == 0) {
            enterpoints(LITTLESTREET, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "gs") == 0) {
            enterpoints(BIGSTREET, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "k") == 0) {
            enterpoints(KNIFFEL, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "ch") == 0) {
            enterpoints(CHANCE, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
    }
    return hasenteredpoints;
}


int checkpointsforturn(int place, int* dicethrow) {
    int score = 0;
    switch(place) {
        case ONE:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 1) {
                    score+=dicethrow[i];
                }
            }
            break;
        case TWO:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 2) {
                    score+=dicethrow[i];
                }
            }
            break;
        case THREE:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 3) {
                    score+=dicethrow[i];
                }
            }
            break;
        case FOUR:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 4) {
                    score+=dicethrow[i];
                }
            }
            break;
        case FIVE:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 5) {
                    score+=dicethrow[i];
                }
            }
            break;
        case SIX:
            for(int i = 0; i < 5; i++) {
                if(dicethrow[i] == 6) {
                    score+=dicethrow[i];
                }
            }
            break;
        case FULLHOUSE:
            bool hasthree = 0;
            bool hastwo = 0;
            int* timesofoccurence = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurence[j] = 0;
            }
            for(int i = 0; i < 5; i++) {
                timesofoccurence[dicethrow[i]-1]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurence[k] == 3) {
                    hasthree = 1;
                }
                if(timesofoccurence[k] == 2) {
                    hastwo = 1;
                }
            }
            if(hastwo && hasthree) {
                score = 25;
            }
            break;
        case THREESOME:
            bool hasthreesome = 0;
            int* timesofoccurencethree = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurencethree[j] = 0;
            }for(int i = 0; i < 5; i++) {
                timesofoccurencethree[dicethrow[i]-1]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencethree[k] >= 3) {
                    hasthreesome = 1;
                }
            }
            if(hasthreesome) {
                for(int l = 0; l < 5; l++) {
                    score += dicethrow[l];
                }
            }
            break;
        case FOURSOME:
            bool hasfoursome = 0;
            int* timesofoccurencefour = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurencefour[j] = 0;
            }for(int i = 0; i < 5; i++) {
                timesofoccurencefour[dicethrow[i]-1]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencefour[k] >= 4) {
                    hasfoursome = 1;
                }
            }
            if(hasfoursome) {
                for(int l = 0; l < 5; l++) {
                    score += dicethrow[l];
                }
            }
            break;
        case LITTLESTREET:
            int currentindexlittle = findsmallestnumberindex(dicethrow);
            int currentstreaklittle = 1;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 5; j++) {
                    if(dicethrow[j] == dicethrow[currentindexlittle] + 1) {
                        currentindexlittle = j;
                        currentstreaklittle++;
                        break;
                    }
                }   
            }
            if(currentstreaklittle >= 4) {
                score = 30;
            }
            break;
        case BIGSTREET:
            int currentindexbig = findsmallestnumberindex(dicethrow);
            int currentstreakbig = 1;
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    if(dicethrow[j] == dicethrow[currentindexbig] + 1) {
                        currentindexbig = j;
                        currentstreakbig++;
                        break;
                    }
                }   
            }
            if(currentstreakbig == 5) {
                score = 40;
            }
            break;
        case KNIFFEL:
            for(int i = 1; i < 5; i++) {
                if(dicethrow[i] != dicethrow[0]) {
                    score = 0;
                    break;
                } else {
                    score = 50;
                }
            }
            break;
        case CHANCE:
            for(int i = 0; i < 5; i++) {
                score += dicethrow[i];
            }
    }
    if(score == 0) {
        score = -1;
    }
    return score;
}
