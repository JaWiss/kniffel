#include "botRegistry.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>

static BotEntry botTable[] = {
    { "randomBot", randomBot },
    { "improvedRandomBot", improvedRandomBot },
    { "greedyRandomBot", greedyRandomBot },
    { "baseBot", baseBot }
};

#define BOT_COUNT (sizeof(botTable) / sizeof(botTable[0]))

BotMoveFunc findBotByName(const char* name) {
    for(int i = 0; i < (int)(sizeof(botTable) / sizeof(botTable[0])); i++) {
        if(strcmp(botTable[i].name, name) == 0) {
            return botTable[i].func;
        }
    }
    return NULL;
}

void printBotNames() {
    for(int i = 0; i < BOT_COUNT; i++) {
        printf("%s\n", botTable[i].name);
    }
}

int numberOfBots() {
    return BOT_COUNT;
}

char* getBotNameAtIndex(int index) {
    return botTable[index].name;
}