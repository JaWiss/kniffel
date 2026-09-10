#include <stdio.h>
#include <argp.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "utilities/sheet.h"
#include "utilities/calculations.h"
#include "utilities/helper.h"
#include "utilities/game.h"
#include "botRegistry.h"

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

int main(int argc, char *argv[]) {
    Sheet* listofsheets;
    int numberofplayers;
    initrandom();
    bool botMode = 0;
    char botModeInput[2];
    int numberOfIterations = 1;
    printf("Möchtest du das Programm im Bot Modues starten? (J/N)\n");
    while(1) {
        scanf("%1s", botModeInput);
        if(strcmp(botModeInput, "N") == 0) {
            break;
        }
        else if(strcmp(botModeInput, "J") == 0) {
            botMode = 1;
            break;
        }
        else {
            printf("Gebe J oder N ein.\n");
        }
    }
    if(botMode) {
        numberofplayers = numberOfBots();
        printf("Wie viele Iterationen soll es geben?\n");
        scanf("%d", &numberOfIterations);
    } else {
        listofsheets = registerplayers(&numberofplayers);
    }
    for(int k = 0; k < numberOfIterations; k++) {
        listofsheets = registerBots();
        for(int i = 0; i < 13; i++) {
            for(int j = 0; j < numberofplayers; j++) {
                if(strcmp(listofsheets[j].status, "COM") == 0) {
                    botTurn(&listofsheets[j]);
                } else {
                    humanTurn(&listofsheets[j]);
                }
            }
        }
        if(numberOfIterations == 1) {
            for(int k = 0; k < numberofplayers; k++) {
                listofsheets[k].totalScore = calculatetotalscore(listofsheets[k]);
                printf("Spieler %s:\n",listofsheets[k].playername);
                printf("Blatt:\n");
                printf("Einser:         %s\n",convertscoretotext(listofsheets[k].ones));
                printf("Zweier:         %s\n",convertscoretotext(listofsheets[k].twos));
                printf("Dreier:         %s\n",convertscoretotext(listofsheets[k].threes));
                printf("Vierer:         %s\n",convertscoretotext(listofsheets[k].fours));
                printf("Fünfer:         %s\n",convertscoretotext(listofsheets[k].fives));
                printf("Sechser:        %s\n",convertscoretotext(listofsheets[k].sixes));
                printf("-------------------------------------\n");
                printf("Punktzahl Oben: %d", calculateupperscore(&listofsheets[k]));
                printf("-------------------------------------\n");
                printf("Dreierpasch:    %s\n",convertscoretotext(listofsheets[k].threesome));
                printf("Viererpasch:    %s\n",convertscoretotext(listofsheets[k].foursome));
                printf("Full-House:     %s\n",convertscoretotext(listofsheets[k].fullhouse));
                printf("kleine Straße:  %s\n",convertscoretotext(listofsheets[k].smallstraight));
                printf("große Straße:   %s\n",convertscoretotext(listofsheets[k].bigstraight));
                printf("Kniffel:        %s\n",convertscoretotext(listofsheets[k].kniffel));
                printf("Chance:         %s\n",convertscoretotext(listofsheets[k].chance));
                printf("-------------------------------------\n");
                printf("Punktzahl Unten:%d", calculatelowerscore(&listofsheets[k]));
                printf("-------------------------------------\n");
                printf("Gesamtpunktzahl:%d\n",listofsheets[k].totalScore);
            }
        } 
        enterGameDataTOCSV(listofsheets, numberofplayers);
    }
    return 0;
}
