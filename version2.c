#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define INPUT_SIZE 1024
#define DELIM " \t\r\n\a"

// Function to display prompt
void display_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("PUCITshell@%s:- ", cwd);
}

// Function to execute commands
void execute_command(char **args) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        if (execvp(args[0], args) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);  // Exit child process if exec fails
    } else if (pid < 0) {  // Forking error
        perror("Fork failed");
    } else {  // Parent process
        waitpid(pid, NULL, 0);  // Wait for the child to complete
    }
}

// Function to handle input/output redirection
void handle_redirection(char **args) {
    int in = -1, out = -1;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            in = open(args[i + 1], O_RDONLY);
            if (in == -1) {
                perror("Error opening input file");
                return;
            }
            dup2(in, STDIN_FILENO);  // Redirect stdin to input file
            close(in);
            args[i] = NULL;  // Remove redirection operator and filename from args
        } else if (strcmp(args[i], ">") == 0) {
            out = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (out == -1) {
                perror("Error opening output file");
                return;
            }
            dup2(out, STDOUT_FILENO);  // Redirect stdout to output file
            close(out);
            args[i] = NULL;  // Remove redirection operator and filename from args
        }
    }
}

// Function to execute piped commands
void handle_pipe(char **args) {
    int pipefd[2];
    pid_t pid;
    char *cmd1[64], *cmd2[64];
    int i, j = 0;

    // Split the args into two commands for piping
    for (i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            args[i] = NULL;
            break;
        }
        cmd1[i] = args[i];
    }
    cmd1[i] = NULL;

    // Remaining args go to cmd2
    i++;
    for (; args[i] != NULL; i++, j++) {
        cmd2[j] = args[i];
    }
    cmd2[j] = NULL;

    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return;
    }

    pid = fork();
    if (pid == 0) {
        // First child executes cmd1, output goes to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        if (execvp(cmd1[0], cmd1) == -1) {
            perror("Error executing command 1");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        pid = fork();
        if (pid == 0) {
            // Second child executes cmd2, input comes from pipe
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[1]);
            close(pipefd[0]);
            if (execvp(cmd2[0], cmd2) == -1) {
                perror("Error executing command 2");
                exit(EXIT_FAILURE);
            }
        } else if (pid < 0) {
            perror("Fork failed");
        } else {
            // Parent closes pipe and waits
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid, NULL, 0);
        }
    }
}

int main() {
    char input[INPUT_SIZE];
    char *args[64];

    while (1) {
        display_prompt();

        if (fgets(input, INPUT_SIZE, stdin) == NULL) {
            printf("\nExiting shell...\n");
            break;
        }

        // Tokenize input
        int i = 0;
        args[i] = strtok(input, DELIM);
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, DELIM);
        }

        if (args[0] == NULL) continue;

        // Check for redirection
        int redirection = 0, piping = 0;
        for (i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "<") == 0 || strcmp(args[i], ">") == 0) {
                redirection = 1;
            } else if (strcmp(args[i], "|") == 0) {
                piping = 1;
            }
         }

        if (piping) {
            handle_pipe(args);
        } else if (redirection) {
            pid_t pid = fork();
            if (pid == 0) {
                handle_redirection(args);
                execute_command(args);
                exit(EXIT_SUCCESS);
            } else if (pid > 0) {
                waitpid(pid, NULL, 0);
            }
        } else {
            execute_command(args);
        }
    }
    return 0;
}

































