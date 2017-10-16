#ifndef FILESTUFF_H
#define FILESTUFF_H

char** listAllFiles(const char* path, int* entryC);
int copyFile(const char* src, const char* dst);

#endif