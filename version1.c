#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define PROMPT "PUCITshell:-"

void display_prompt() {
    char cwd[MAX_LINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s%s$ ", PROMPT, cwd);
    } else {
        perror("getcwd() error");
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_LINE / 2 + 1]; // assuming each token will be at least 2 characters on average
    pid_t pid;
    int status;

    while (1) {
        // Display the prompt
        display_prompt();

        // Get the input line from the user
        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nExiting shell...\n");
            break; // Exit on Ctrl+D
        }

        // Remove the newline character from the end of the input
        line[strcspn(line, "\n")] = '\0';

        // Parse the line into tokens
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // NULL-terminate the array of tokens

        // Check for an empty command
        if (args[0] == NULL) {
            continue;
        }

        // Fork a new process
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            continue;
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) < 0) {
                perror("exec failed");
                exit(1);
            }
        } else {
            // Parent process
            waitpid(pid, &status, 0); // Wait for the child to finish
        }
    }
    return 0;
}

