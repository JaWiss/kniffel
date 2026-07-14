#ifndef SHEET_H
#define SHEET_H


typedef struct {
    char playername[20];
    char status[8];
    int ones;
    int twos;
    int threes;
    int fours;
    int fives;
    int sixes;
    int fullhouse;
    int threesome;
    int foursome;
    int smallstraight;
    int bigstraight;
    int kniffel;
    int chance;
    int totalScore;
}Sheet;

Sheet createSheet(char* playerName, char* status);

#endif
