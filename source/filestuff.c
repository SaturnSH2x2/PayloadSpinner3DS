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
    
    closedir(d);
    arrSize--;
    
    *entryC = arrIndex;
    
    return entries;
}

int copyFile(const char* src, const char* dst) {
    char* fileData;
    int size;
    
    FILE* s = fopen(src, "rb");
    if (s == NULL)
        return -1;
    
    fseek(s, 0, SEEK_END);
    size = ftell(s);
    printf("filesize is %d\n", size);
    fseek(s, 0, SEEK_SET);
    
    // https://stackoverflow.com/a/19247565/8732627
    fileData = malloc(size + 1);
    fread(fileData, 1, size, s);
    fileData[size] = '\0';
    fclose(s);
    
    printf("%s", fileData);
    
    FILE* d = fopen(dst, "wb");
    if (d == NULL)
        return -1;
    
    fputs(fileData, d);
    fclose(d);
    
    return 0;
}