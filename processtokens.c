#include<string.h>
#include <stdio.h>
#include <stdlib.h>

void processtokens(char* inputstring, char** commands) {
    char* currentcommand;
    int count = 0;
    currentcommand = strtok(inputstring, "|");
    if (currentcommand == NULL) {
        if ((commands[0] = malloc(strlen(inputstring) * sizeof(char*))) == NULL) {
            perror("Malloc failed");
            exit(EXIT_FAILURE);
        }
        if (strncpy(commands[0], inputstring, strlen(inputstring)) == NULL) {
            perror("String copying failed");
            exit(EXIT_FAILURE);
        }
        return;
    }
    while (currentcommand != NULL) {
        int commandlen = strlen(currentcommand);
        if (currentcommand[commandlen - 1] == ' ') {
            currentcommand[commandlen - 1] = '\0';
        }
        if (currentcommand[0] == ' ') {
            currentcommand = currentcommand + 1;
        }
        if ((commands[count] = malloc(commandlen * sizeof(char*))) == NULL) {
            perror("Malloc failed");
            exit(EXIT_FAILURE);
        }
        if (strncpy(commands[count], currentcommand, commandlen) == NULL) {
            perror("String copying failed");
            exit(EXIT_FAILURE);
        }
        currentcommand = strtok(NULL, "|");
        count++;
    }
}