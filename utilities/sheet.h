#ifndef SHEET_H
#define SHEET_H


typedef struct {
    char* playername;
    char* status;
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
    int chance;
    int kniffel;
    int totalScore;
}Sheet;

Sheet createSheet(char* playerName, char* status);

#endif
