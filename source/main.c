#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>
#include "pp2d/pp2d.h"
#include "ui.h"

int main(int argc, char **argv) {
    aptInit();
    romfsInit();
    pp2d_init();

    uistruct* us = malloc(sizeof(uistruct));
    
    uiInit(us);
    uiRun(us);
    
    free(us);

    pp2d_exit();
    romfsExit();
    aptExit();
    return 0;
}
