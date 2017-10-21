#ifndef BACKUP_H
#define BACKUP_H
  
void rebootSystem() {
    APT_HardwareResetAsync();
}

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
    if (result == 0) {
        result = uiPrompt("boot.firm replaced. Reboot now?");
        if (result == 0)
            rebootSystem();
    } else
        uiError("Replacement failed.");
    
    return result;
}
      


#endif