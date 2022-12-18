#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

void
sig_int(int signo) {
	perror("Caught sigint somehow");
	(void)fflush(stdout);
}


int main(int argc, char** argv) {
    pid_t pid;
    char input[BUFSIZ] = "";
    int status;
    char* optstr = "c:x";
    int opt;
    int enable_trace = 0;
    bool cflag = false;
    while ((opt = getopt(argc, argv, optstr)) != -1) {
        switch (opt) {
            case 'c':
                cflag = true;
                if (strncpy(input, optarg, strlen(optarg)) == NULL) {
                    perror("String copy");
                }
                break;
            case 'x':
                enable_trace = 1;
                break;
            default:
                printf("Option not supported!\n");
                exit(0);
        }
    }
    if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("Signal error");
		exit(1);
	}
    while(strncmp(input, "exit", 4) != 0) {
        if (!cflag) {
            printf("-> ");
            scanf("%s", input);
        }
        if ((pid = fork()) == -1) {
            perror("Could not fork");
            continue;
        }
        /* Child process*/
        else if (pid == 0) {
            execlp(input, input, (char*) 0);
        }
        if (cflag) {
            break;
            if ((pid = waitpid(pid, &status, 0)) < 0 && errno != SIGCHLD) {
        }
                perror("Parent could not wait");
                continue;
            }
    }
    return 0;
}