#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include <sys/wait.h>

void
sig_int(int signo) {
	perror("Caught sigint somehow");
	(void)fflush(stdout);
}


int main(int argc, char** argv) {
    pid_t pid = 1;
    char* input;
    input = malloc(BUFSIZ * sizeof(char*));
    int status;
    char* optstr = "c:x";
    int opt;
    size_t size = BUFSIZ;
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
            case '?':
                printf("Option not supported!\n");
                exit(EXIT_FAILURE);
        }
    }
    if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("Signal error");
		exit(1);
	}
    while(strncmp(input, "exit", 4) != 0) {
        if (!cflag) {
            printf("-> ");
            input = fgets(input, BUFSIZ, stdin);
            input[strlen(input) - 1] = '\0';
        }
        if ((pid = fork()) == -1) {
            perror("Could not fork");
            continue;
        }
        /* Child process*/
        else if (pid == 0) {
            char* args[BUFSIZ];
            puts(input);
            char* command = strtok(input, " ");
            char* argument = strtok(NULL, " ");
            execlp(command, command, argument, (char*)NULL);
            perror("Child could not execute properly");
            exit(EX_UNAVAILABLE);
        }
        if (cflag) {
            break;
        }
        if ((pid = waitpid(pid, &status, WNOHANG)) < 0 && errno != ECHILD) {
            perror("Parent could not wait");
            continue;
        }
    }
    return 0;
}