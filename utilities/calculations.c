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
#define SMALLSTRAIGHT 9
#define BIGSTRAIGHT 10
#define KNIFFEL 11
#define CHANCE 12

int checkscore(int score) {
    if(score > 0) {
        return score;
    }
    return 0;
}

int calculatelowerscore(Sheet* playersheet) {
    int score = 0;
    score += checkscore(playersheet->threesome);
    score += checkscore(playersheet->foursome);
    score += checkscore(playersheet->fullhouse);
    score += checkscore(playersheet->smallstraight);
    score += checkscore(playersheet->bigstraight);
    score += checkscore(playersheet->kniffel);
    score += checkscore(playersheet->chance);
    return score;
}

int calculateupperscore(Sheet* playersheet) {
    int score = 0;
    score += checkscore(playersheet->ones);
    score += checkscore(playersheet->twos);
    score += checkscore(playersheet->threes);
    score += checkscore(playersheet->fours);
    score += checkscore(playersheet->fives);
    score += checkscore(playersheet->sixes);
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
    score += checkscore(playersheet.smallstraight);
    score += checkscore(playersheet.bigstraight);
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
            enterpoints(SMALLSTRAIGHT, dicethrow, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "gs") == 0) {
            enterpoints(BIGSTRAIGHT, dicethrow, playersheet);
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
    printf("A\n");
    int score = 0;

    // Count how often each die value occurs
    int count[6] = {0};

    printf("B\n");
    for (int i = 0; i < 5; i++) {
        printf("ZAHL: %d\n", dicethrow[i]);
        if (dicethrow[i] >= 1 && dicethrow[i] <= 6) {
            count[dicethrow[i] - 1]++;
        }
    }

    printf("C\n");
    switch (place) {

        case ONE:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 1) {
                    score += dicethrow[i];
                }
            }
            break;

        case TWO:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 2) {
                    score += dicethrow[i];
                }
            }
            break;

        case THREE:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 3) {
                    score += dicethrow[i];
                }
            }
            break;

        case FOUR:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 4) {
                    score += dicethrow[i];
                }
            }
            break;

        case FIVE:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 5) {
                    score += dicethrow[i];
                }
            }
            break;

        case SIX:
            for (int i = 0; i < 5; i++) {
                if (dicethrow[i] == 6) {
                    score += dicethrow[i];
                }
            }
            break;

        case FULLHOUSE: {
            bool hasthree = false;
            bool hastwo = false;

            for (int i = 0; i < 6; i++) {
                if (count[i] == 3) {
                    hasthree = true;
                }

                if (count[i] == 2) {
                    hastwo = true;
                }
            }

            if (hasthree && hastwo) {
                score = 25;
            }

            break;
        }

        case THREESOME: {
            bool hasthreesome = false;

            for (int i = 0; i < 6; i++) {
                if (count[i] >= 3) {
                    hasthreesome = true;
                    break;
                }
            }

            if (hasthreesome) {
                for (int i = 0; i < 5; i++) {
                    score += dicethrow[i];
                }
            }

            break;
        }

        case FOURSOME: {
            bool hasfoursome = false;

            for (int i = 0; i < 6; i++) {
                if (count[i] >= 4) {
                    hasfoursome = true;
                    break;
                }
            }

            if (hasfoursome) {
                for (int i = 0; i < 5; i++) {
                    score += dicethrow[i];
                }
            }

            break;
        }

        case SMALLSTRAIGHT: {
            if ((count[0] && count[1] && count[2] && count[3]) ||
                (count[1] && count[2] && count[3] && count[4]) ||
                (count[2] && count[3] && count[4] && count[5])) {

                score = 30;
            }

            break;
        }

        case BIGSTRAIGHT: {
            if ((count[0] && count[1] && count[2] && count[3] && count[4]) ||
                (count[1] && count[2] && count[3] && count[4] && count[5])) {

                score = 40;
            }

            break;
        }

        case KNIFFEL: {
            score = 50;

            for (int i = 1; i < 5; i++) {
                if (dicethrow[i] != dicethrow[0]) {
                    score = 0;
                    break;
                }
            }

            break;
        }

        case CHANCE:
            for (int i = 0; i < 5; i++) {
                score += dicethrow[i];
            }
            break;
    }

    // -1 means that the category was not achieved
    if (score == 0) {
        score = -1;
    }

    printf("D\n");
    return score;
}


int* calculateScoreForEveryField(int* dicethrow, Sheet sheet) {
    int* scores = malloc(13 * sizeof(int)); 
    if(sheet.ones == -1) {
        scores[ONE] = -1;
    } else {
        scores[ONE] = checkpointsforturn(ONE, dicethrow);
    }
    if(sheet.twos == -1) {
        scores[TWO] = -1;
    } else {
        scores[TWO] = checkpointsforturn(TWO, dicethrow);
    }
    if(sheet.threes == -1) {
        scores[THREE] = -1;
    } else {
        scores[THREE] = checkpointsforturn(THREE, dicethrow);
    }
    if(sheet.fours == -1) {
        scores[FOUR] = -1;
    } else {
        scores[FOUR] = checkpointsforturn(FOUR, dicethrow);
    }
    if(sheet.fives == -1) {
        scores[FIVE] = -1;
    } else {
        scores[FIVE] = checkpointsforturn(FIVE, dicethrow);
    }
    if(sheet.sixes == -1) {
        scores[SIX] = -1;
    } else {
        scores[SIX] = checkpointsforturn(SIX, dicethrow);
    }
    if(sheet.threesome == -1) {
        scores[THREESOME] = -1;
    } else {
        scores[THREESOME] = checkpointsforturn(THREESOME, dicethrow);
    }
    if(sheet.foursome == -1) {
        scores[FOURSOME] = -1;
    } else {
        scores[FOURSOME] = checkpointsforturn(FOURSOME, dicethrow);
    }
    if(sheet.fullhouse == -1) {
        scores[FULLHOUSE] = -1;
    } else {
        scores[FULLHOUSE] = checkpointsforturn(FULLHOUSE, dicethrow);
    }
    if(sheet.smallstraight == -1) {
        scores[SMALLSTRAIGHT] = -1;
    } else {
        scores[SMALLSTRAIGHT] = checkpointsforturn(SMALLSTRAIGHT, dicethrow);
    }
    if(sheet.bigstraight == -1) {
        scores[BIGSTRAIGHT] = -1;
    } else {
        scores[BIGSTRAIGHT] = checkpointsforturn(BIGSTRAIGHT, dicethrow);
    }
    if(sheet.kniffel == -1) {
        scores[KNIFFEL] = -1;
    } else {
        scores[KNIFFEL] = checkpointsforturn(KNIFFEL, dicethrow);
    }
    if(sheet.chance == -1) {
        scores[CHANCE] = -1;
    } else {
        scores[CHANCE] = checkpointsforturn(CHANCE, dicethrow);
    }
    return scores;
}

int* calculateScoreForEveryOpenField(int* dicethrow, Sheet sheet) {
    printf("100\n");
    int* scores = malloc(13 * sizeof(int));
    printf("200\n");

    scores[ONE]          = (sheet.ones == 0)          ? checkpointsforturn(ONE, dicethrow)          : -1;
    scores[TWO]          = (sheet.twos == 0)          ? checkpointsforturn(TWO, dicethrow)          : -1;
    scores[THREE]        = (sheet.threes == 0)        ? checkpointsforturn(THREE, dicethrow)        : -1;
    scores[FOUR]         = (sheet.fours == 0)         ? checkpointsforturn(FOUR, dicethrow)         : -1;
    scores[FIVE]         = (sheet.fives == 0)         ? checkpointsforturn(FIVE, dicethrow)         : -1;
    scores[SIX]          = (sheet.sixes == 0)         ? checkpointsforturn(SIX, dicethrow)          : -1;
    scores[THREESOME]    = (sheet.threesome == 0)     ? checkpointsforturn(THREESOME, dicethrow)    : -1;
    scores[FOURSOME]     = (sheet.foursome == 0)      ? checkpointsforturn(FOURSOME, dicethrow)     : -1;
    scores[FULLHOUSE]    = (sheet.fullhouse == 0)     ? checkpointsforturn(FULLHOUSE, dicethrow)    : -1;
    scores[SMALLSTRAIGHT] = (sheet.smallstraight == 0) ? checkpointsforturn(SMALLSTRAIGHT, dicethrow) : -1;
    scores[BIGSTRAIGHT]  = (sheet.bigstraight == 0)   ? checkpointsforturn(BIGSTRAIGHT, dicethrow)  : -1;
    scores[KNIFFEL]      = (sheet.kniffel == 0)       ? checkpointsforturn(KNIFFEL, dicethrow)      : -1;
    scores[CHANCE]       = (sheet.chance == 0)        ? checkpointsforturn(CHANCE, dicethrow)       : -1;

    printf("300\n");
    for(int i = 0; i < 13; i++) {
        printf("SCORE: %d\n",scores[i]);
    }
    return scores;
}