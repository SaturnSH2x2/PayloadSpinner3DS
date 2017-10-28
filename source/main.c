#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <3ds.h>
#include "pp2d/pp2d.h"
#include "ui.h"

int main(int argc, char **argv) {
    aptInit();
    romfsInit();
    pp2d_init();

    uistruct* us = malloc(sizeof(uistruct)); 
    uiInit(us);
    if (us->entries == NULL) {
        uiError("No payloads were found. Refer to the README.");
        
        // create directories as nessecary
        mkdir("/3ds/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("/3ds/data/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("/3ds/data/PayloadSpinner3DS/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        mkdir("/3ds/data/PayloadSpinner3DS/payloads/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        goto exit;
    }
    
    uiRun(us);
    
    exit:
    free(us);

    pp2d_exit();
    romfsExit();
    aptExit();
    return 0;
}
