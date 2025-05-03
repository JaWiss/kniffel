#ifndef GAME_H
#define GAME_H

#include "sheet.h"

void turn(Sheet* playersheet);
void enterpoints(int place, int* dicethrow, Sheet* playersheet);
int checkinput(char* input, Sheet* playersheet);
void findemptyrows(Sheet playersheet, int* dicethrow);
Sheet* registerplayers(int* numberofplayers);

#endif
