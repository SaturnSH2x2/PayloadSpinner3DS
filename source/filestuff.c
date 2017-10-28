#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <3ds.h>

#include "filestuff.h"

#define MAXDIRSIZE 255


char** listAllFiles(const char* path, int* entryC) {
    char** entries;
    int arrSize = 2;
    int arrIndex = 0;
    entries = malloc(arrSize * sizeof(*entries));
    if (entries == NULL) {
        printf("failed to allocate memory\n");
        return NULL;
    }
    
    struct dirent* dEnt;
    DIR* d = opendir(path);
    if ( d == NULL )
        return NULL;
    
    while ( (dEnt = readdir(d)) != NULL ) {
        entries[arrIndex] = malloc(MAXDIRSIZE * sizeof(char*));
        snprintf(entries[arrIndex], MAXDIRSIZE, dEnt->d_name);
        
        arrIndex++;
        if (arrIndex >= arrSize) {
            arrSize++;
            entries = realloc(entries, arrSize * sizeof(*entries));
            if (entries == NULL) {
                printf("failed to allocate memory\n");
                return NULL;
            }
        }
    }
    
    if (arrIndex == 0)
        return NULL;
    
    closedir(d);
    arrSize--;
    
    *entryC = arrIndex;
    
    return entries;
}

int copyFile(const char* src, const char* dst) {
    int buf;
    
    FILE* s = fopen(src, "rb");
    FILE* d = fopen(dst, "w+");
    if (s == NULL)
        return -1;
    
    while ((buf = fgetc(s)) != EOF) {
        fputc(buf, d);
    }
    
    fclose(s);
    fclose(d);
    
    return 0;
}