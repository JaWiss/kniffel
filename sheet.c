
typedef struct {
    char* playername;
    int ones;
    int twos;
    int threes;
    int fours;
    int fives;
    int sixes;
    int fullhouse;
    int threesome;
    int foursome;
    int littlestreet;
    int bigstreet;
    int kniffel;
    int chance;
    int totalScore;
}Sheet;

Sheet createSheet(char* playerName) {
    Sheet sheet;
    sheet.playername = playerName;
    sheet.ones = 0;
    sheet.twos = 0;
    sheet.threes = 0;
    sheet.fours = 0;
    sheet.fives = 0;
    sheet.sixes = 0;
    sheet.threesome = 0;
    sheet.foursome = 0;
    sheet.fullhouse = 0;
    sheet.littlestreet = 0;
    sheet.bigstreet = 0;
    sheet.kniffel = 0;
    sheet.chance = 0;
    sheet.totalScore = 0;
    return sheet;
}
