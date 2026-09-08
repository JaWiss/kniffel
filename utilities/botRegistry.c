#include "botRegistry.h"
#include <string.h>
#include <stddef.h>

static BotEntry botTable[] = {
    { "randomBot", randomBot }
};

BotMoveFunc findBotByName(const char* name) {
    for(int i = 0; i < (int)(sizeof(botTable) / sizeof(botTable[0])); i++) {
        if(strcmp(botTable[i].name, name) == 0) {
            return botTable[i].func;
        }
    }
    return NULL;
}
