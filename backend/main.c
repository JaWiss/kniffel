#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>


#include "utilities/sheet.h"
#include "utilities/calculations.h"
#include "utilities/helper.h"
#include "utilities/game.h"

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

int main(int argc, char *argv[]) {
    Sheet* listofsheets;
    int numberofplayers;
    
    listofsheets = registerplayers(&numberofplayers);
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < numberofplayers; j++) {
            turn(&listofsheets[j]);
        }
    }
    for(int k = 0; k < numberofplayers; k++) {
        listofsheets[k].totalScore = calculatetotalscore(listofsheets[k]);
        printf("Spieler %s\n:",listofsheets[k].playername);
        printf("    Blatt:\n");
        printf("Einser:         %s\n",convertscoretotext(listofsheets[k].ones));
        printf("Zweier:         %s\n",convertscoretotext(listofsheets[k].twos));
        printf("Dreier:         %s\n",convertscoretotext(listofsheets[k].threes));
        printf("Vierer:         %s\n",convertscoretotext(listofsheets[k].fours));
        printf("Fünfer:         %s\n",convertscoretotext(listofsheets[k].fives));
        printf("Sechser:        %s\n",convertscoretotext(listofsheets[k].sixes));
        printf("Dreierpasch:    %s\n",convertscoretotext(listofsheets[k].threesome));
        printf("Viererpasch:    %s\n",convertscoretotext(listofsheets[k].foursome));
        printf("Full-House:     %s\n",convertscoretotext(listofsheets[k].fullhouse));
        printf("kleine Straße:  %s\n",convertscoretotext(listofsheets[k].littlestreet));
        printf("große Straße:   %s\n",convertscoretotext(listofsheets[k].bigstreet));
        printf("Kniffel:        %s\n",convertscoretotext(listofsheets[k].kniffel));
        printf("Chance:         %s\n",convertscoretotext(listofsheets[k].chance));
        printf("Gesamtpunktzahl:%d\n",listofsheets[k].totalScore);
    }
}
