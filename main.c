#include <linux/limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#include "third_party/cjson/cJSON.h"

int main(int argc, char* argv[])
{
    char resolve[PATH_MAX];
    const char *input = (argc <= 1) ? "." : argv[1];
    if (!realpath(input, resolve))
    {
        perror("realpath");
        return(1);
    }

    cJSON *json = cJSON_CreateObject();
    cJSON *files = cJSON_AddObjectToObject(json, resolve);

    DIR *d = opendir(resolve);
    if (!d)
    {
        perror("opendir");
        return(1);
    }

    struct dirent *entry;

    while((entry = readdir(d)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }

        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", resolve, entry->d_name);


        cJSON *file_object = cJSON_AddObjectToObject(files, entry->d_name);

        struct stat sb;
        if (lstat(full_path, &sb) == -1)
        {
            perror("lstat");
            exit(EXIT_FAILURE);
        }
        char permissions[8];
        snprintf(permissions, sizeof(permissions), "%o", sb.st_mode & 0777);

        cJSON_AddNumberToObject(file_object, "is_dir", S_ISDIR(sb.st_mode));
        cJSON_AddStringToObject(file_object, "permissions", permissions);
        cJSON_AddNumberToObject(file_object, "mode", sb.st_mode);
        cJSON_AddNumberToObject(file_object, "inode", sb.st_ino);
        cJSON_AddNumberToObject(file_object, "link_count", sb.st_nlink);
        cJSON_AddNumberToObject(file_object, "uid", sb.st_uid);
        cJSON_AddNumberToObject(file_object, "gid", sb.st_gid);
        cJSON_AddNumberToObject(file_object, "block_size", sb.st_blksize);
        cJSON_AddNumberToObject(file_object, "file_size", sb.st_size);
        cJSON_AddNumberToObject(file_object, "blocks", sb.st_blocks);
        cJSON_AddNumberToObject(file_object, "ctime", sb.st_ctime);
        cJSON_AddNumberToObject(file_object, "atime", sb.st_atime);
        cJSON_AddNumberToObject(file_object, "mtime", sb.st_mtime);

    }


    char *output = cJSON_Print(json);
    printf("%s\n", output);
    free(output);
    closedir(d);

    return(0);
}

