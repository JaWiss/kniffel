#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <stdbool.h>

#include "sheet.h"

int checkscore(int score);
int calculatetotalscore(Sheet playersheet);
bool enterpointstosheet(Sheet* playersheet, int* throw);
int checkpointsforturn(int place, int* throw);

#endif