
int dicethrow() {
    return (rand() % 6) + 1; 
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
    char* zahl = malloc(sizeof(char) * 10);

    if(score == 0) {
        return "offen";
    }
    if(score == -1) {
        return "gestrichen";
    }
    sprintf(zahl, "%d", score);
    return zahl;
}