#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERRMSG(x) do {                                                  \
        fprintf( stderr, "ERR %d @ line %d: %s\n", errno, __LINE__, x); \
        exit(1);                                                        \
  } while (0)

int
main(int argc, char *argv[])
{
    DIR *dir = NULL;
    struct dirent *dir_info;

    (void) argc;
    (void) argv;

    if (!(dir = opendir("/usr")))
        ERRMSG( "opendir");

    do {
        dir_info = readdir(dir);
        if (dir_info) {
            printf("%s\n", dir_info->d_name);
        }
    } while (dir_info);

    if (closedir(dir)) {
        ERRMSG( "closedir");
    }

    return 0;
}
