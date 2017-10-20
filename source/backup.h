#ifndef BACKUP_H
#define BACKUP_H

int backup(const char* path) {
    int result;
    remove("/boot.firm.bak");
    result = rename("/boot.firm", "/boot.firm.bak");
    if (result != 0) {
       result = uiPrompt("Could not back up boot.firm. Continue?");
       if (result == -1)
           return result;
    }
    
    result = copyFile(path, "/boot.firm");
    if (result == 0)
        uiError("Replacement successful.");
    else
        uiError("Replacement failed.");
    
    return result;
}
        

#endif