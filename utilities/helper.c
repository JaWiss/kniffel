#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    char* zahl[10];
    sprintf(zahl, "%d", score);
    return zahl;
}
