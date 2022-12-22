#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include <sys/wait.h>

#include "sicd.h"
#include "siecho.h"
#include "siexit.h"

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
    while(true) {
        if (!cflag) {
            printf("-> ");
            input = fgets(input, BUFSIZ, stdin);
            input[strlen(input) - 1] = '\0';
            if (strncmp(input, "exit", strlen("exit")) == 0) {
                siexit();
            }
            if (strncmp(input, "cd", strlen("cd")) == 0) {
                char* dir = strtok(input, " ");
                dir = strtok(NULL, " ");
                sicd(dir);
                continue;
            }
        }
        if ((pid = fork()) == -1) {
            perror("Could not fork");
            continue;
        }
        /* Child process*/
        else if (pid == 0) {
            char* args[BUFSIZ];
            char* command = strtok(input, " ");
            char* argument = strtok(NULL, " ");
            if (strncmp(command, "echo", strlen("echo")) == 0) {
                siecho(argument);
                continue;
            }
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
    siexit();
    return 0;
}