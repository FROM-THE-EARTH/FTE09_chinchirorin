#include "SDCard.h"
 
SDCard::SDCard(PinName miso, PinName mosi, PinName sck, PinName cs) : __blockDevice(miso, mosi, sck, cs), __fileSystem("fs")
{
    __cs = cs;
}
 
int SDCard::mounting(){
    // Try to mount the filesystem
    printf("Mounting the filesystem... \r\n");
    fflush(stdout);
 
    __err = __fileSystem.mount(&__blockDevice);
    printf("%s\r\n", (__err ? "Fail :(" : "OK"));
    if (__err) {
        // Reformat if we can't mount the filesystem
        // this should only happen on the first boot
        printf("No filesystem found... \r\n");
        fflush(stdout);
        /*
        err = fileSystem.reformat(&blockDevice);
        my_pc.printf("%s\r\n", (err ? "Fail :(" : "OK"));
        if (err) {
            error("error: %s (%d)\r\n", strerror(-err), err);
        }
        */
        return -1;
    }
    return 1;
} 
 
 
int SDCard::opening_file(char *path, char* filename){
    char filetoopen[100];
    // Open the numbers file
    strcpy(filetoopen, path); 
    strcat(filetoopen, filename);
    printf("Opening FILE %s ... \r\n", filetoopen);
    fflush(stdout);
    __f = fopen(filetoopen, "r+");
    printf("%s\r\n", (!__f ? "Fail :(" : "OK"));
    if (!__f) {
        // Create the numbers file if it doesn't exist
        printf("No file found... \r\n");
        fflush(stdout);
        return -1;
    }
    return 1;
}
 
int SDCard::closing_file(void){
    // Close the file which also flushes any cached writes
    printf("Closing FILE ... \r\n");
    fflush(stdout);
    __err = fclose(__f);
    printf("%s\r\n", (__err < 0 ? "Fail :(" : "OK"));
    if (__err < 0) {
        error("error: %s (%d)\r\n", strerror(errno), -errno);
        return -1;
    }
    return 1;
}
 
int SDCard::unmounting(){
    printf("Unmounting... \r\n");
    fflush(stdout);
    __err = __fileSystem.unmount();
    printf("%s\r\n", (__err < 0 ? "Fail :(" : "OK"));
    if (__err < 0) {
        error("error: %s (%d)\r\n", strerror(-__err), __err);
        return -1;
    }
    printf("Deinitializing the block device... \r\n");
    fflush(stdout);
    __err = __blockDevice.deinit();
    printf("%s\r\n", (__err ? "Fail :(" : "OK"));
    if (__err) {
        error("error: %s (%d)\r\n", strerror(-__err), __err);
        return -1;
    }
    return 1;
}
 
FILE * SDCard::getFile(void){
    return __f;
}
            