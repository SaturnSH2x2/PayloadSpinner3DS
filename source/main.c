#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>
#include "ui.h"
#include "jsondata.h"
#include "pp2d/pp2d.h"

int main(int argc, char **argv) {
    char error[256];

    aptInit();
    romfsInit();
    //pp2d_init();
    consoleInit(GFX_TOP, NULL);
    

    uistruct* us = malloc(sizeof(uistruct));
    int result = loadJsonData(error, us->entries);
    if (result == -1){
        printf("error loading json data, press any key to exit\n");
        
        while (aptMainLoop()) {
            if (hidKeysUp())
                break;
            
            gfxFlushBuffers();
            gfxSwapBuffers();
            gspWaitForVBlank();
        }
        
        return 1;
    }
    
    //uiInit(us);
    //uiRun(us);
    
    //free(us);

    //pp2d_exit();
    romfsExit();
    aptExit();
    return 0;
}
