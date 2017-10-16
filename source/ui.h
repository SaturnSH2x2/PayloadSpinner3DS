#ifndef UI_H
#define UI_H

typedef struct uistruct {
    char** entries;
    int entryCount;
    int entryIndex;
    
    int holdTimer;
} uistruct;

void cls();
void uiInit(uistruct* us);
int uiPrompt(const char* prompt);
void uiRun(uistruct* us);

#endif