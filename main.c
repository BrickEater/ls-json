#include <linux/limits.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <limits.h>

#include "third_party/cjson/cJSON.h"

cJSON *read_dir(const char *path);

int main()
{

    char resolved[PATH_MAX];
    realpath(".", resolved);

    cJSON *entries = read_dir(".");
    cJSON *root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, resolved, entries);

    char *output = cJSON_Print(root);
    printf("%s\n", output);

    free(output);
    cJSON_Delete(root);

    return(0);
}

cJSON *read_dir(const char *path)
{
    DIR *d = opendir(path);
    if (!d) return NULL;
    
    cJSON *entries = cJSON_CreateArray();

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL)
    {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }
        cJSON *obj = cJSON_CreateObject();
        cJSON_AddStringToObject(obj, "name", entry->d_name);

        struct stat sb;
        if (lstat(entry->d_name, &sb) == -1)
        {
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        cJSON_AddNumberToObject(obj, "inode", sb.st_ino);
        cJSON_AddNumberToObject(obj, "mode", sb.st_mode);
        cJSON_AddNumberToObject(obj, "link count", sb.st_nlink);
        cJSON_AddNumberToObject(obj, "ownership(UID)", sb.st_uid);
        cJSON_AddNumberToObject(obj, "ownership(GID)", sb.st_gid);
        cJSON_AddNumberToObject(obj, "preferred IO block size", sb.st_blksize);
        cJSON_AddNumberToObject(obj, "file size", sb.st_size);
        cJSON_AddNumberToObject(obj, "blocks allocated", sb.st_blocks);
        cJSON_AddNumberToObject(obj, "last status change", sb.st_ctime);
        cJSON_AddNumberToObject(obj, "last file access", sb.st_atime);
        cJSON_AddNumberToObject(obj, "modification", sb.st_mtime);

        cJSON_AddItemToArray(entries,  obj);
    }


    closedir(d);
    return entries;
}


