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
void findemptyrows(Sheet playersheet);
int checkinput(char* input, Sheet* playersheet);
int findsmallestnumberindex(int* list);

int main(int argc, char *argv[]) {
    Sheet* listofsheets;
    int numberofplayers;
    
    listofsheets = registerplayers(&numberofplayers);
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < numberofplayers; j++) {
            turn(&listofsheets[j]);
        }
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

void turn(Sheet* playersheet) {
    srand(time(NULL));
    int* throw = malloc(sizeof(int)*5);
    char input[10];
    printf("Spieler %s\n:",playersheet->playername);
    printf("    Blatt:\n");
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
    for(int j = 0; j < 3; j++) {
        printf("Dein Wurf:\n");
        printf(" %d, %d, %d, %d, %d\n",throw[0],throw[1],throw[2],throw[3],throw[4]);
        printf("Gebe e ein um eine Zahl einzutragen.\nGebe w ein um erneut zu würfeln.\nGebe s ein um etwas zu streichen.\n");
        while(1) {
            scanf("%s", input);
            if(strcmp(input, "e") == 0 || strcmp(input, "w") == 0 || strcmp(input, "s") == 0) {

                break;
            }
            else {
                printf("Gebe e, w oder s ein.\n");
            }
        }
        if(strcmp(input, "w") == 0) {
            printf("Gebe  die Zahlen ein die du neu würfeln willst.\n");
            printf("Der Wurf war: \n%d, %d, %d, %d, %d\n",throw[0],throw[1],throw[2],throw[3],throw[4]);

        }
        if(strcmp(input, "e") == 0) {
            printf("Gib an in welche Zeile du etwas eintragen willst. Das sind deine möglichen, offenen Zeilen:\n");
            findemptyrows(*playersheet);
        }
        if(strcmp(input, "s") == 0) {
            printf("Gebe an welche Zeile du streichen willst. Das sind deine offenen Zeilen:\n");
            findemptyrows(*playersheet);
            while(1) {
                scanf("%s",input);
                int entrytobechanged = checkinput(input, &playersheet);
                int* addressofentry = &playersheet->ones;
                if(entrytobechanged >= 0) {
                    addressofentry += sizeof(int) * entrytobechanged;
                } else {
                    printf("Bitte wähle eine der möglichen Optionen aus.\n");
                }
            }
        }
    }
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
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case THREE:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case FOUR:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case FIVE:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case SIX:
            for(int i = 0; i < 5; i++) {
                if(throw[i] == 1) {
                    score+=throw[i];
                }
            }
            break;
        case FULLHOUSE:
            bool hasthree = 0;
            bool hastwo = 0;
            int* timesofoccurence = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurence[j-1] = 0;
            }
            for(int i = 0; i < 5; i++) {
                timesofoccurence[i]+=1;
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
                timesofoccurencethree[j-1] = 0;
            }for(int i = 0; i < 5; i++) {
                timesofoccurencethree[i]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencethree[k] == 3) {
                    hasthreesome = 1;
                }
            }
            if(hasthree) {
                for(int l = 0; l < 5; l++) {
                    score += throw[l];
                }
            }
            break;
        case FOURSOME:
            bool hasfoursome = 0;
            int* timesofoccurencefour = malloc(sizeof(int)*6);
            for(int j = 0; j < 6; j++) {
                timesofoccurencefour[j-1] = 0;
            }for(int i = 0; i < 5; i++) {
                timesofoccurencefour[i]+=1;
            }
            for(int k = 0; k < 6; k++) {
                if(timesofoccurencefour[k] == 4) {
                    hasthree = 1;
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
            if(currentstreaklittle == 4) {
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
                    break;
                }
            }
            score = 50;
            break;
        case CHANCE:
            for(int i = 1; i < 5; i++) {
                score += throw[i];
            }
    }
    if(score == 0) {
        score = -1;
    }
    return score;
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

void findemptyrows(Sheet playersheet) {
    if(playersheet.ones == 0) {
        printf("Einser\n");
    }
    if(playersheet.twos == 0) {
        printf("Zweier\n");
    }
    if(playersheet.threes == 0) {
        printf("Dreier\n");
    }
    if(playersheet.fours == 0) {
        printf("Vierer\n");
    }
    if(playersheet.fives == 0) {
        printf("Fünfer\n");
    }
    if(playersheet.sixes == 0) {
        printf("Sechser\n");
    }
    if(playersheet.threesome == 0) {
        printf("Dreierpasch\n");
    }
    if(playersheet.foursome == 0) {
        printf("Viererpasch\n");
    }
    if(playersheet.fullhouse == 0) {
        printf("Full House\n");
    }
    if(playersheet.littlestreet == 0) {
        printf("Kleine Straße\n");
    }
    if(playersheet.bigstreet == 0) {
        printf("Große Straße\n");
    }
    if(playersheet.kniffel == 0) {
        printf("Kniffel\n");
    }
    if(playersheet.chance == 0) {
        printf("Chance\n");
    }
}

char* convertscoretotext(int score) {

    char* zahl = malloc(sizeof(char) * 3);

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

int findsmallestnumberindex(int* list) {
    int smallestnumber = list[0];
    int smallestnumberindex = 0;
    for(int i = 1; i < sizeof(list) / sizeof(int); ) {
        if(list[i] < smallestnumber) {
            smallestnumber = list[i];
            smallestnumberindex = i;
        }
    }
    return smallestnumberindex;
}