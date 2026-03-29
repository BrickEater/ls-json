// I'm doing this in the wrong order. I've been ignoring that I need to retrieve the path from the user
// I should really smooth out that function before I do all this data retrieval
// I should also consider using both stat and lstat. I feel like they return different data for symlinks
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "third_party/cjson/cJSON.h"

int main()
{

    DIR *d = opendir(".");
    if (!d) return 1;

    struct dirent *entry;

    while((entry = readdir(d)) != NULL)
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }
        else
        {
            printf("%s\n", entry->d_name);
        }

    return(0);
}
