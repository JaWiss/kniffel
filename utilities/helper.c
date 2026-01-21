#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

int generatedicethrow() {
    return (rand() % 6) + 1; 
}

void initrandom() {
    srand(time(NULL));
}

int findsmallestnumberindex(int* listofnumbers) {
    int smallestnumber = listofnumbers[0];
    int smallestnumberindex = 0;
    for(int i = 1; i < 5; i++) {
        if(listofnumbers[i] < smallestnumber) {
            smallestnumber = listofnumbers[i];
            smallestnumberindex = i;
        }
    }
    return smallestnumberindex;
}

char* convertscoretotext(int score) {
    if(score == 0) {
        return "offen";
    }
    if(score == -1) {
        return "gestrichen";
    }
    char* zahl = malloc(sizeof(char) * 10);
    sprintf(zahl, "%d", score);
    return zahl;
}

double getBaseLikelyhood(int throwCode, int points) {
    switch (throwCode)
    {
    case ONE:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points);
    case TWO:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points/2);
    case THREE:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points/3);
    case FOUR:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points/4); 
    case FIVE:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points/5); 
    case SIX:
        int baseLikelyhood = 1.0/6;
        return pow(baseLikelyhood, points/6);
    case THREESOME:
        return (1.0/6) * (1.0/6);
    case FOURSOME:
        return (1.0/6) * (1.0/6) * (1.0/6);
    case FULLHOUSE:
        return (1.0/6) * (1.0/6) * (5.0/6) * (1.0/6);
    case SMALLSTRAIGHT: 
        return (4.0/6 * 3.0/6 * 2.0/6 * 1.0/6) * 3;
    case BIGSTRAIGHT: 
        return (5.0/6 * 4.0/6 * 3.0/6 * 2.0/6 * 1.0/6) * 2;
    case KNIFFEL:
        return (1.0/6) * (1.0/6) * (1.0/6) * (1.0/6);
    case CHANCE:
        return 100.0;
    default:
        break;
    }
}