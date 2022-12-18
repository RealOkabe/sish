#include<string.h>
#include <stdio.h>

void processtokens(char* inputstring) {
    char* currentcommand;
    currentcommand = strtok(inputstring, "|");
    currentcommand[strlen(currentcommand) - 1] = '\0';
    if (currentcommand[strlen(currentcommand) - 1] == ' ') {
        printf("Found a space!\n");
    }
    printf("%s\n", currentcommand);
}

int main(void) {
    char commands[100] = "find . -name Android.mk | grep Taimen";
    processtokens(commands);
    return 0;
}