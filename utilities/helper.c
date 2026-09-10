#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "sheet.h"
#include "calculations.h"
#include <time.h>

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

void enterTime(FILE* filePointer);
void enterPlayerDataToFile(Sheet* sheet, FILE* filePointer);
int isFileEmpty(FILE *fp);

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
    case TWO:
    case THREE:
    case FOUR:
    case FIVE:
    case SIX:
    case THREESOME:
    case FOURSOME:
    case FULLHOUSE:
    case SMALLSTRAIGHT: 
    case BIGSTRAIGHT: 
    case KNIFFEL:
    case CHANCE:
    default:
        break;
    }
    return 0.0;
}

void enterGameDataTOCSV(Sheet* listOfSheets, int numberOfPlayers) {
    FILE* filePointer = fopen("second_run_data.csv","a+");
    if (filePointer == NULL) {
       perror("Fehler beim Öffnen der Datei");
       return;
    }
    if(isFileEmpty(filePointer)) {
        fprintf(filePointer, "date,time");
        for(int i = 0; i < numberOfPlayers; i++) {
            fprintf(filePointer, ",Playername,Playerstatus,Einser,Zweier,Dreier,Vierer,Fünfer,Sechser,Oben,Dreierpasch,Viererpasch,Full-House,kleine-Straße,große-Straße,Kniffel,Chance,Unten,Total");
        }
        fprintf(filePointer,"\n");
    }
    enterTime(filePointer);
    for(int j = 0; j < numberOfPlayers; j++) {
        enterPlayerDataToFile(&listOfSheets[j], filePointer);
    }
    fprintf(filePointer,"\n");
    fclose(filePointer);
}

void enterTime(FILE* filePointer) {
    time_t now = time(NULL);
    struct tm* timeInfo = localtime(&now);
    fprintf(filePointer, "%d-%02d-%02d,%02d:%02d:%02d",timeInfo->tm_year+1900,timeInfo->tm_mon+1,timeInfo->tm_mday,timeInfo->tm_hour,timeInfo->tm_min,timeInfo->tm_sec);
}

void enterPlayerDataToFile(Sheet* sheet, FILE* filePointer) {
    int upperScore = calculateupperscore(sheet);
    int lowerScore = calculatelowerscore(sheet);
    int totalScore = upperScore + lowerScore;
    fprintf(filePointer, ",%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",sheet->playername,sheet->status,sheet->ones,sheet->twos,sheet->threes,sheet->fours,sheet->fives,sheet->sixes,upperScore,
    sheet->threesome, sheet->foursome, sheet->fullhouse, sheet->smallstraight, sheet->bigstraight, sheet->kniffel, sheet->chance, lowerScore, totalScore); 
}

int isFileEmpty(FILE *fp) {
    long aktuelle_position = ftell(fp);  // aktuelle Position merken

    fseek(fp, 0, SEEK_END);   // ans Ende springen
    long groesse = ftell(fp); // Position = Dateigröße in Bytes

    fseek(fp, aktuelle_position, SEEK_SET); // zurück zur ursprünglichen Position

    return groesse == 0;
}

