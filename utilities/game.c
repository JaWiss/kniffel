#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "sheet.h"
#include "helper.h"
#include "calculations.h"

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


void turn(Sheet* playersheet) {
    srand(time(NULL));
    int* dicethrow = malloc(sizeof(int)*5);
    char input[10];
    bool hasenteredpoints = 0;
    printf("Spieler %s\n",playersheet->playername);
    printf("Blatt:\n");
    printf("Einser:         %s\n",convertscoretotext(playersheet->ones));
    printf("Zweier:         %s\n",convertscoretotext(playersheet->twos));
    printf("Dreier:         %s\n",convertscoretotext(playersheet->threes));
    printf("Vierer:         %s\n",convertscoretotext(playersheet->fours));
    printf("Fünfer:         %s\n",convertscoretotext(playersheet->fives));
    printf("Sechser:        %s\n",convertscoretotext(playersheet->sixes));
    printf("Punktzahl oben: %s\n",calculateupperscore(*playersheet));
    printf("Dreierpasch:    %s\n",convertscoretotext(playersheet->threesome));
    printf("Viererpasch:    %s\n",convertscoretotext(playersheet->foursome));
    printf("Full-House:     %s\n",convertscoretotext(playersheet->fullhouse));
    printf("kleine Straße:  %s\n",convertscoretotext(playersheet->littlestreet));
    printf("große Straße:   %s\n",convertscoretotext(playersheet->bigstreet));
    printf("Kniffel:        %s\n",convertscoretotext(playersheet->kniffel));
    printf("Chance:         %s\n",convertscoretotext(playersheet->chance));
    printf("Punktzahl unten:%s\n",calculatelowerscore(*playersheet));
    printf("Punktzahl Total:%s\n",calculatetotalscore(*playersheet));
    for(int i = 0; i < 5; i++) {
        dicethrow[i] = generatedicethrow();
    }
    for(int j = 0; j < 2; j++) {
        if(hasenteredpoints) {
            break;
        }
        printf("Dein Wurf:\n");
        printf(" %d, %d, %d, %d, %d\n",dicethrow[0],dicethrow[1],dicethrow[2],dicethrow[3],dicethrow[4]);
        printf("Gebe e ein um eine Zahl einzutragen.\nGebe w ein um erneut zu würfeln.\nGebe s ein um etwas zu streichen.\n");
        while(1) {
            scanf("%s", input);
            if(strcmp(input, "e") == 0 || strcmp(input, "w") == 0) {
                break;
            }
            else {
                printf("Gebe e oder w ein.\n");
            }
        }
        if(strcmp(input, "w") == 0) {
            printf("Gebe  die Würfel ein die du neu würfeln willst.\n");
            printf("Der Wurf war: \nWürfel 1: %d\nWürfel 2: %d\nWürfel 3: %d\nWürfel 4: %d,\nürfel 5: %d\n",dicethrow[0],dicethrow[1],dicethrow[2],dicethrow[3],dicethrow[4]);
            while(1) {
                scanf("%s",input);
                if(strlen(input) > 0) {
                    break;
                }
            }
            for(int i = 0; i < strlen(input); i++) {
                if(input[i] == '1') {
                    dicethrow[0] = generatedicethrow();
                }
                if(input[i] == '2') {
                    dicethrow[1] = generatedicethrow();
                }
                if(input[i] == '3') {
                    dicethrow[2] = generatedicethrow();
                }
                if(input[i] == '4') {
                    dicethrow[3] = generatedicethrow();
                }
                if(input[i] == '5') {
                    dicethrow[4] = generatedicethrow();
                }
            }
        }
        if(strcmp(input, "e") == 0) {
            hasenteredpoints = enterpointstosheet(playersheet, dicethrow);
        }
    }
    if(!hasenteredpoints) {
        printf("Dein Wurf:\n");
        printf(" %d, %d, %d, %d, %d\n",dicethrow[0],dicethrow[1],dicethrow[2],dicethrow[3],dicethrow[4]);
        enterpointstosheet(playersheet, dicethrow);
    }
}


void enterpoints(int place, int* dicethrow, Sheet* playersheet) {
    switch(place) {
        case ONE:
            playersheet->ones = checkpointsforturn(place, dicethrow);
            break;
        case TWO:
            playersheet->twos = checkpointsforturn(place, dicethrow);
            break;
        case THREE:
            playersheet->threes = checkpointsforturn(place, dicethrow);
            break;
        case FOUR:
            playersheet->fours = checkpointsforturn(place, dicethrow);
            break;
        case FIVE:
            playersheet->fives = checkpointsforturn(place, dicethrow);
            break;
        case SIX:
            playersheet->sixes = checkpointsforturn(place, dicethrow);
            break;
        case FULLHOUSE:
            playersheet->fullhouse = checkpointsforturn(place, dicethrow);
            break;
        case THREESOME:
            playersheet->threesome = checkpointsforturn(place, dicethrow);
            break;
        case FOURSOME:
            playersheet->foursome = checkpointsforturn(place, dicethrow);
            break;
        case LITTLESTREET:
            playersheet->littlestreet = checkpointsforturn(place, dicethrow);
            break;
        case BIGSTREET:
            playersheet->bigstreet = checkpointsforturn(place, dicethrow);
            break;
        case KNIFFEL:
            playersheet->kniffel = checkpointsforturn(place, dicethrow);
            break;
        case CHANCE:
            playersheet->chance = checkpointsforturn(place, dicethrow);
    }
}


int checkinput(char* input, Sheet* playersheet) {
    if(strcmp(input, "Einser")) {
        if(playersheet->ones == 0) {
            return 0;
        }
    }
    if(strcmp(input, "Zweier")) {
        if(playersheet->twos == 0) {
            return 1;
        }
    }
    if(strcmp(input, "Dreier")) {
        if(playersheet->threes == 0) {
            return 2;
        }        
    }
    if(strcmp(input, "Vierer")) {
        if(playersheet->fours == 0) {
            return 3;
        }        
    }
    if(strcmp(input, "Fünfer")) {
        if(playersheet->fives == 0) {
            return 4;
        }        
    }
    if(strcmp(input, "Sechser")) {
        if(playersheet->sixes == 0) {
            return 5;
        }        
    }
    if(strcmp(input, "Dreierpasch")) {
        if(playersheet->threesome == 0) {
            return 7;
        }        
    }
    if(strcmp(input, "Viererpasch")) {
        if(playersheet->foursome == 0) {
            return 8;
        }        
    }
    if(strcmp(input, "Full House")) {
        if(playersheet->fullhouse == 0) {
            return 6;
        }        
    }
    if(strcmp(input, "kleine Straße")) {
        if(playersheet->littlestreet == 0) {
            return 9;
        }        
    }
    if(strcmp(input, "große Straße")) {
        if(playersheet->bigstreet == 0) {
            return 10;
        }        
    }
    if(strcmp(input, "Kniffel")) {
        if(playersheet->kniffel == 0) {
            return 11;
        }        
    }
    if(strcmp(input, "Chance")) {
        if(playersheet->chance == 0) {
            return 12;
        }        
    }
    return -1;
}


void findemptyrows(Sheet playersheet, int* dicethrow) {
    char* score;
    if(playersheet.ones == 0) {
        score = convertscoretotext(checkpointsforturn(ONE, dicethrow));
        printf("Einser[e]: %s\n",score);
    }
    if(playersheet.twos == 0) {
        score = convertscoretotext(checkpointsforturn(TWO, dicethrow));
        printf("Zweier[z]: %s\n",score);
    }
    if(playersheet.threes == 0) {
        score = convertscoretotext(checkpointsforturn(THREE, dicethrow));
        printf("Dreier[d]: %s\n",score);
    }
    if(playersheet.fours == 0) {
        score = convertscoretotext(checkpointsforturn(FOUR, dicethrow));
        printf("Vierer[v]: %s\n",score);
    }
    if(playersheet.fives == 0) {
        score = convertscoretotext(checkpointsforturn(FIVE, dicethrow));
        printf("Fünfer[f]: %s\n",score);
    }
    if(playersheet.sixes == 0) {
        score = convertscoretotext(checkpointsforturn(SIX, dicethrow));
        printf("Sechser[s]: %s\n",score);
    }
    if(playersheet.threesome == 0) {
        score = convertscoretotext(checkpointsforturn(THREESOME, dicethrow));
        printf("Dreierpasch[dp]: %s\n",score);
    }
    if(playersheet.foursome == 0) {
        score = convertscoretotext(checkpointsforturn(FOURSOME, dicethrow));
        printf("Viererpasch[vp]: %s\n",score);
    }
    if(playersheet.fullhouse == 0) {
        score = convertscoretotext(checkpointsforturn(FULLHOUSE, dicethrow));
        printf("Full House[fh]: %s\n",score);
    }
    if(playersheet.littlestreet == 0) {
        score = convertscoretotext(checkpointsforturn(LITTLESTREET, dicethrow));
        printf("Kleine Straße[ks]: %s\n",score);
    }
    if(playersheet.bigstreet == 0) {
        score = convertscoretotext(checkpointsforturn(BIGSTREET, dicethrow));
        printf("Große Straße[gs]: %s\n",score);
    }
    if(playersheet.kniffel == 0) {
        score = convertscoretotext(checkpointsforturn(KNIFFEL, dicethrow));
        printf("Kniffel[k]: %s\n",score);
    }
    if(playersheet.chance == 0) {
        score = convertscoretotext(checkpointsforturn(CHANCE, dicethrow));
        printf("Chance[ch]: %s\n",score);
    }
}

Sheet* registerplayers(int* numberofplayers) {
    Sheet* listofsheets;
    int numberof;
    printf("Wie viele Spieler möchtens sie haben?\n");
    scanf("%d",&numberof);
    printf("Sie haben %d registriert.\n", numberof);
    listofsheets = malloc(sizeof(Sheet)*numberof);
    for(int i = 0; i < numberof; i++) {
        char name[20];
        printf("Wie soll Spieler %d heißen?\n", i+1);
        scanf("%s",name);
        listofsheets[i] = createSheet(name);
        printf("Spieler %s wurde registriert.\n", listofsheets[i].playername);
    }
    printf("Es wurden %d Spieler registriert\n", numberof);    

    *numberofplayers = numberof;
    return listofsheets;

}
