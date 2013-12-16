#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *dir_info;

    dir = opendir("/usr");

    printf("0x%lX\n\n", dir);
    dir_info = readdir(dir);
    //printf("0x%lX\n: %s\n", dir, dir_info->d_name);

    closedir(dir);

    return 0;
}
