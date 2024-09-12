#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define MAX_INPUT_SIZE 1024
#define MAX_TOKENS 100
 
void parse_input(char *input, char **tokens) {
    char *token;
    int i = 0;
   
    token = strtok(input, " \t\r\n");  
    while (token != NULL && i < MAX_TOKENS) {
        tokens[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    tokens[i] = NULL;  
}
 
int main() {
    char input[MAX_INPUT_SIZE];
    char *tokens[MAX_TOKENS];
    int pid;
   
    while (1) {
   
        printf("mini-shell> ");
       
       
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break;
        }
       
        if (strcmp(input, "\n") == 0) {
            continue;
        }
 
        parse_input(input, tokens);
       
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
       
        if (pid == 0) {
            if (execvp(tokens[0], tokens) == -1) {
                perror("execvp");
                exit(1);
            }
        } else {
            wait(NULL);
        }
    }
   
    return 0;
}
 