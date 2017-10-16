#include <stdlib.h>
#include <stdio.h>
#include <3ds.h>

#include "filestuff.h"
#include "ui.h"

// thanks, Kingy    :^)
void cls() {
    printf("\e[1;1H\e[2J");
}

// initializes ui
void uiInit(uistruct* us) {
    us->entries = listAllFiles("/3ds/data/PayloadSpinner3DS/", &us->entryCount);
    us->entryIndex = 0;
    us->holdTimer = 0;
}

// prompts user for input
int uiPrompt(const char* prompt) {
    int charsInPrompt = sizeof(prompt) / sizeof(char);
    cls();
    printf("\x1b[15;%iH%s", 20 - (int)(charsInPrompt / 2), prompt);
    printf("\x1b[20;5H(A) Yes");
    printf("\x1b[20;40H(B) No");
    
    int result = -1;
    
    while (aptMainLoop()) {
        hidScanInput();
        u32 kUp = hidKeysUp();
        
        if (kUp & KEY_B) {
            result = -1;
            break;
        } else if (kUp & KEY_A) {
            result = 0;
            break;
        }
        
        gfxSwapBuffers();
        gfxFlushBuffers();
        gspWaitForVBlank();
    }
    
    return result;
}

// really, it's just the main application loop
void uiRun(uistruct* us) {
    int throwaway;
    
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        u32 kUp   = hidKeysUp();
        
        switch (kUp) {
            case KEY_UP:
                us->entryIndex--;
                break;
            case KEY_DOWN:
                us->entryIndex++;
                break;
            case KEY_A:
                throwaway = uiPrompt("BOTTOM TEXT");
                break;
            default:
                break;
        }
        
        if (us->entryIndex >= us->entryCount)
            us->entryIndex = 0;
        else if (us->entryIndex < 0)
            us->entryIndex = us->entryCount - 1;
        
        cls();
        printf("\x1b[5;0H");
        for (int i = 0; i < us->entryCount; i++) {
            if (i == us->entryIndex)
                printf("--> %s\n", us->entries[i]);
            else
                printf("    %s\n", us->entries[i]);
        }
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
}