#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void echo(char* arg) {
    if (arg == NULL) {
        (void)printf("\n");
        return;
    }
    if (strncmp(arg, "$", strlen("$")) == 0) {
        if (strlen(arg) == 1) {
            (void)printf("%s\n", arg);
            return;
        }
        char* envvar;
        if ((envvar = getenv(arg + 1)) == NULL) {
            (void) printf("\n");
        }
        else {
        (void)printf("%s\n", envvar);
        }
    }
    else {
        (void) printf("%s\n", arg);
    }
}