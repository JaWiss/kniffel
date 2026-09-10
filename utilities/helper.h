#ifndef HELPER_H
#define HELPER_H


int generatedicethrow();
int findsmallestnumberindex(int* listofnumbers);
char* convertscoretotext(int score);
void initrandom();
void enterGameDataTOCSV(Sheet* listOfSheets, int numberOfPlayers);
void enterPlayerDataToFile(Sheet* sheet, FILE* filePointer);
int isFileEmpty(FILE *fp);


#endif
