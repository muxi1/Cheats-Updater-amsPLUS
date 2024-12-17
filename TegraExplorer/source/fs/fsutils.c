#include <mem/heap.h>
#include <string.h>
#include "fsutils.h"
#include "../utils/utils.h"
#include <utils/sprintf.h>
#include <libs/fatfs/ff.h>
#include "readers/folderReader.h"

char *CombinePaths(const char *current, const char *add){
    char *ret;

    size_t size = strlen(current) + strlen(add) + 2;
    ret = (char*) malloc (size);

    s_printf(ret, (current[strlen(current) - 1] == '/') ? "%s%s" : "%s/%s", current, add);

    return ret;
}

char *EscapeFolder(const char *current){
    char *ret;
    char *temp;

    ret = CpyStr(current);
    temp = strrchr(ret, '/');

    if (*(temp - 1) == ':')
        temp++;

    *temp = '\0';

    return ret;
}

FSEntry_t GetFileInfo(const char *path){
    FILINFO fno;
    f_stat(path, &fno);
    FSEntry_t entry = {.optionUnion = fno.fattrib, .name = strrchr(path, '/') + 1};
    if (!(*entry.name))
        entry.name = "Root";
    return entry;
}

char *GetFileAttribs(FSEntry_t entry){
    char *ret = CpyStr("RHSVDA");
    MaskIn(ret, entry.optionUnion, '-');
    return ret;
}

// Returns 1 if a file exists, 0 if it does not
bool FileExists(const char* path){
    FRESULT fr;
    FILINFO fno;

    fr = f_stat(path, &fno);

    return !(fr & FR_NO_FILE);
}
