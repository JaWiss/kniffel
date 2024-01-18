#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>


#include "sheet.h"

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

Sheet* registerplayers(int*);
char* convertscoretotext(int score);
void turn(Sheet* playersheet);
int dicethrow();
void findemptyrows(Sheet playersheet, int* throw);
int checkinput(char* input, Sheet* playersheet);
int findsmallestnumberindex(int* list);
bool enterpointstosheet(Sheet* playersheet, int* throw);

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

int checkscore(int score) {
    if(score > 0) {
        return score;
    }
    return 0;
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

void turn(Sheet* playersheet) {
    srand(time(NULL));
    int* throw = malloc(sizeof(int)*5);
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
    printf("Dreierpasch:    %s\n",convertscoretotext(playersheet->threesome));
    printf("Viererpasch:    %s\n",convertscoretotext(playersheet->foursome));
    printf("Full-House:     %s\n",convertscoretotext(playersheet->fullhouse));
    printf("kleine Straße:  %s\n",convertscoretotext(playersheet->littlestreet));
    printf("große Straße:   %s\n",convertscoretotext(playersheet->bigstreet));
    printf("Kniffel:        %s\n",convertscoretotext(playersheet->kniffel));
    printf("Chance:         %s\n",convertscoretotext(playersheet->chance));
    for(int i = 0; i < 5; i++) {
        throw[i] = dicethrow();
    }
    for(int j = 0; j < 2; j++) {
        if(hasenteredpoints) {
            break;
        }
        printf("Dein Wurf:\n");
        printf(" %d, %d, %d, %d, %d\n",throw[0],throw[1],throw[2],throw[3],throw[4]);
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
            printf("Der Wurf war: \nWÜrfel 1: %d,WÜrfel 2: %d,Würfel 3: %d,Würfel 4: %d,Würfel 5: %d\n",throw[0],throw[1],throw[2],throw[3],throw[4]);
            while(1) {
                scanf("%s",input);
                if(strlen(input) > 0) {
                    break;
                }
            }
            for(int i = 0; i < strlen(input); i++) {
                if(input[i] == '1') {
                    throw[0] = dicethrow();
                }
                if(input[i] == '2') {
                    throw[1] = dicethrow();
                }
                if(input[i] == '3') {
                    throw[2] = dicethrow();
                }
                if(input[i] == '4') {
                    throw[3] = dicethrow();
                }
                if(input[i] == '5') {
                    throw[4] = dicethrow();
                }
            }
        }
        if(strcmp(input, "e") == 0) {
            hasenteredpoints = enterpointstosheet(playersheet, throw);
        }
    }
    if(!hasenteredpoints) {
        printf("Dein Wurf:\n");
        printf(" %d, %d, %d, %d, %d\n",throw[0],throw[1],throw[2],throw[3],throw[4]);
        enterpointstosheet(playersheet, throw);
    }
}
bool enterpointstosheet(Sheet* playersheet, int* throw) {
    char input[10];
    bool hasenteredpoints = 0;
    printf("Gib an in welche Zeile du etwas eintragen willst. Das sind deine möglichen, offenen Zeilen:\n");
    findemptyrows(*playersheet, throw);
    while(1) {
        scanf("%s", input);
        if(strcmp(input, "e") == 0) {
            enterpoints(ONE, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "z") == 0) {
            enterpoints(TWO, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "d") == 0) {
            enterpoints(THREE, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "v") == 0) {
            enterpoints(FOUR, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "f") == 0) {
            enterpoints(FIVE, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "s") == 0) {
            enterpoints(SIX, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "dp") == 0) {
            enterpoints(THREESOME, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "vp") == 0) {
            enterpoints(FOURSOME, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "fh") == 0) {
            enterpoints(FULLHOUSE, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "ks") == 0) {
            enterpoints(LITTLESTREET, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "gs") == 0) {
            enterpoints(BIGSTREET, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "k") == 0) {
            enterpoints(KNIFFEL, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
        if(strcmp(input, "ch") == 0) {
            enterpoints(CHANCE, throw, playersheet);
            hasenteredpoints = 1;
            break;
        }
    }
    return hasenteredpoints;
}
int checkpointsforturn(int place, int* throw) {
    int score = 0;
    switch(place) {
        case ONE:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case TWO:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 2) {
                    score+=throw[i];
                }
            }
            break;
        case THREE:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 3) {
                    score+=throw[i];
                }
            }
            break;
        case FOUR:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 4) {
                    score+=throw[i];
                }
            }
            break;
        case FIVE:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 5) {
                    score+=throw[i];
                }
            }
            break;
        case SIX:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 6) {
                    score+=throw[i];
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
                timesofoccurence[throw[i]-1]+=1;
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
                timesofoccurencethree[throw[i]-1]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencethree[k] >= 3) {
                    hasthreesome = 1;
                }
            }
            if(hasthreesome) {
                for(int l = 0; l < 5; l++) {
                    score += throw[l];
                }
            }
            break;
        case FOURSOME:
            bool hasfoursome = 0;
            int* timesofoccurencefour = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurencefour[j] = 0;
            }for(int i = 0; i < 5; i++) {
                timesofoccurencefour[throw[i]-1]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencefour[k] >= 4) {
                    hasfoursome = 1;
                }
            }
            if(hasfoursome) {
                for(int l = 0; l < 5; l++) {
                    score += throw[l];
                }
            }
            break;
        case LITTLESTREET:
            int currentindexlittle = findsmallestnumberindex(throw);
            int currentstreaklittle = 1;
            for(int i = 0; i < 4; i++) {
                for(int j = 0; j < 5; j++) {
                    if(throw[j] == throw[currentindexlittle] + 1) {
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
            int currentindexbig = findsmallestnumberindex(throw);
            int currentstreakbig = 1;
            for(int i = 0; i < 5; i++) {
                for(int j = 0; j < 5; j++) {
                    if(throw[j] == throw[currentindexbig] + 1) {
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
            for(int i = 1; i < 4; i++) {
                if(throw[i] != throw[4]) {
                    score = 0;
                    break;
                } else {
                    score = 50;
                }
            }
            break;
        case CHANCE:
            for(int i = 0; i < 5; i++) {
                score += throw[i];
            }
    }
    if(score == 0) {
        score = -1;
    }
    return score;
}
void enterpoints(int place, int* throw, Sheet* playersheet) {
    switch(place) {
        case ONE:
            playersheet->ones = checkpointsforturn(place, throw);
            break;
        case TWO:
            playersheet->twos = checkpointsforturn(place, throw);
            break;
        case THREE:
            playersheet->threes = checkpointsforturn(place, throw);
            break;
        case FOUR:
            playersheet->fours = checkpointsforturn(place, throw);
            break;
        case FIVE:
            playersheet->fives = checkpointsforturn(place, throw);
            break;
        case SIX:
            playersheet->sixes = checkpointsforturn(place, throw);
            break;
        case FULLHOUSE:
            playersheet->fullhouse = checkpointsforturn(place, throw);
            break;
        case THREESOME:
            playersheet->threesome = checkpointsforturn(place, throw);
            break;
        case FOURSOME:
            playersheet->foursome = checkpointsforturn(place, throw);
            break;
        case LITTLESTREET:
            playersheet->littlestreet = checkpointsforturn(place, throw);
            break;
        case BIGSTREET:
            playersheet->bigstreet = checkpointsforturn(place, throw);
            break;
        case KNIFFEL:
            playersheet->kniffel = checkpointsforturn(place, throw);
            break;
        case CHANCE:
            playersheet->chance = checkpointsforturn(place, throw);
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

void findemptyrows(Sheet playersheet, int* throw) {
    char* score;
    if(playersheet.ones == 0) {
        score = convertscoretotext(checkpointsforturn(ONE, throw));
        printf("Einser[e]: %s\n",score);
    }
    if(playersheet.twos == 0) {
        score = convertscoretotext(checkpointsforturn(TWO, throw));
        printf("Zweier[z]: %s\n",score);
    }
    if(playersheet.threes == 0) {
        score = convertscoretotext(checkpointsforturn(THREE, throw));
        printf("Dreier[d]: %s\n",score);
    }
    if(playersheet.fours == 0) {
        score = convertscoretotext(checkpointsforturn(FOUR, throw));
        printf("Vierer[v]: %s\n",score);
    }
    if(playersheet.fives == 0) {
        score = convertscoretotext(checkpointsforturn(FIVE, throw));
        printf("Fünfer[f]: %s\n",score);
    }
    if(playersheet.sixes == 0) {
        score = convertscoretotext(checkpointsforturn(SIX, throw));
        printf("Sechser[s]: %s\n",score);
    }
    if(playersheet.threesome == 0) {
        score = convertscoretotext(checkpointsforturn(THREESOME, throw));
        printf("Dreierpasch[dp]: %s\n",score);
    }
    if(playersheet.foursome == 0) {
        score = convertscoretotext(checkpointsforturn(FOURSOME, throw));
        printf("Viererpasch[vp]: %s\n",score);
    }
    if(playersheet.fullhouse == 0) {
        score = convertscoretotext(checkpointsforturn(FULLHOUSE, throw));
        printf("Full House[fh]: %s\n",score);
    }
    if(playersheet.littlestreet == 0) {
        score = convertscoretotext(checkpointsforturn(LITTLESTREET, throw));
        printf("Kleine Straße[ks]: %s\n",score);
    }
    if(playersheet.bigstreet == 0) {
        score = convertscoretotext(checkpointsforturn(BIGSTREET, throw));
        printf("Große Straße[gs]: %s\n",score);
    }
    if(playersheet.kniffel == 0) {
        score = convertscoretotext(checkpointsforturn(KNIFFEL, throw));
        printf("Kniffel[k]: %s\n",score);
    }
    if(playersheet.chance == 0) {
        score = convertscoretotext(checkpointsforturn(CHANCE, throw));
        printf("Chance[ch]: %s\n",score);
    }
}

char* convertscoretotext(int score) {
    char* zahl = malloc(sizeof(char) * 10);

    if(score == 0) {
        return "offen";
    }
    if(score == -1) {
        return "gestrichen";
    }
    sprintf(zahl, "%d", score);
    return zahl;
}

int dicethrow() {
    return (rand() % 6) + 1; 
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