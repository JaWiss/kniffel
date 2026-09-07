#ifndef SHEET_H
#define SHEET_H

typedef struct diceRollResult
{
    int status;
    union {
            int field;   // gültig wenn status == ENTER
            int* dice;   // gültig wenn status == REROLL
    } data;
};

#endif
