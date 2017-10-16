#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <3ds.h>
#include "ui.h"

int main(int argc, char **argv) {

	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	printf("Hello 3DS World!");

    uistruct* us = malloc(sizeof(uistruct));
    
    uiInit(us);
    uiRun(us);
    
    free(us);

	gfxExit();
	return 0;
}
