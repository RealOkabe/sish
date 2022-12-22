#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sicd(char* arg) {
    if (arg == NULL) {
        printf("NULL");
        uid_t uid = getuid();
        struct passwd *pw;
        if ((pw = getpwuid(uid)) == NULL) {
            perror("Could not get user data");
            exit(EXIT_FAILURE);
        }
        arg = pw->pw_dir;
    }
  if (chdir(arg) != 0) {
    perror("cd: can't cd");
    exit(EXIT_FAILURE);
  }
}

