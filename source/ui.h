#ifndef UI_H
#define UI_H

typedef struct uistruct {
    char** entries;
    int entryCount;
    int entryIndex;
    
    int holdTimer;
    int indexPos;
    
    char* currentFirm;
} uistruct;

void cls();
void uiInit(uistruct* us);
int uiPrompt(const char* prompt);
void uiRun(uistruct* us);
void uiError(const char* error);

#endif