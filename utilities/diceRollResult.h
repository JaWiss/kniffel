#ifndef DICEROLLRESULT
#define DICEROLLRESULT

#define REROLL 0
#define ENTER 1

typedef struct diceRollResult
{
    int status;
    union {
            int field;   // gültig wenn status == ENTER
            int* dice;   // gültig wenn status == REROLL
    } data;
} diceRollResult;

#endif
