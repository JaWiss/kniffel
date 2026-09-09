#ifndef DICEROLLRESULT
#define DICEROLLRESULT

#define REROLL 0
#define ENTER 1

typedef struct diceRollResult
{
    int status;
    union {
            int field;   // gültig wenn status == ENTER
            char* dice;   // gültig wenn status == REROLL
    } data;
} diceRollResult;

#endif
