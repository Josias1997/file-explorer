#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void list_files(const char *path);

int main(const int argc, char *argv[])
{
    const char *path = argc > 1 ? argv[1] : ".";

    printf("Exploring directory: %s\n\n", path);

    list_files(path);

    return 0;
}


void list_files(const char *path) {
    struct dirent *entry;
    struct stat fileStat;

    DIR *directory = opendir(path);

    if(directory == NULL) {
        perror("Unable to open directory.");
        exit(EXIT_FAILURE);
    }

    char fullPath[512];

    while ((entry = readdir(directory)) != NULL) {
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (stat(fullPath, &fileStat) == -1) {
            perror("stat() error");
        }

        printf("Name: %s\n", entry->d_name);

        if(S_ISDIR(fileStat.st_mode)) {
            printf("Type: Directory\n");
        } else {
            printf("Type: File\n");
        }

        printf("Size: %lld bytes\n", fileStat.st_size);

        char timeBuffer[80];

        struct tm *timeInfo = localtime(&fileStat.st_mtime);

        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%m:%s", timeInfo);

        printf("Last modified: %s\n\n", timeBuffer);

    }

    closedir(directory);
}