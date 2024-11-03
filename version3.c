#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_LINE 1024
#define PROMPT "PUCITshell@"
#define READ_END 0
#define WRITE_END 1

void display_prompt() {
    char cwd[MAX_LINE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s%s$ ", PROMPT, cwd);
    } else {
        perror("getcwd() error");
    }
}

// Signal handler for SIGCHLD to clean up terminated background processes
void handle_sigchld(int sig) {
    (void)sig; // Suppress unused variable warning
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

// Helper function to parse the command line
int parse_command(char *line, char **args, char **input_file, char **output_file, int *pipe_flag, int *background_flag) {
    *input_file = NULL;
    *output_file = NULL;
    *pipe_flag = 0;
    *background_flag = 0;

    int i = 0;
    char *token = strtok(line, " ");
    
    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) *input_file = token;
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) *output_file = token;
        } else if (strcmp(token, "|") == 0) {
            *pipe_flag = 1;
            args[i++] = NULL; // End of first command
        } else if (strcmp(token, "&") == 0) {
            *background_flag = 1;
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Null-terminate the array of arguments

    return i;
}

void execute_command(char **args, char *input_file, char *output_file) {
    // Input redirection
    if (input_file != NULL) {
        int fd_in = open(input_file, O_RDONLY);
        if (fd_in < 0) {
            perror("Input file error");
            exit(1);
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
    }

    // Output redirection
    if (output_file != NULL) {
        int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0) {
            perror("Output file error");
            exit(1);
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
    }

    if (execvp(args[0], args) < 0) {
        perror("Execution failed");
        exit(1);
    }
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_LINE / 2 + 1];
    char *input_file, *output_file;
    int pipe_flag, background_flag;
    pid_t pid;

    // Set up signal handler for SIGCHLD to avoid zombie processes
    signal(SIGCHLD, handle_sigchld);

    while (1) {
        display_prompt();

        if (fgets(line, sizeof(line), stdin) == NULL) {
            printf("\nExiting shell...\n");
            break; // Exit on Ctrl+D
        }

        line[strcspn(line, "\n")] = '\0'; // Remove newline character

        // Parse command line input
        parse_command(line, args, &input_file, &output_file, &pipe_flag, &background_flag);

        if (args[0] == NULL) continue; // Empty command, skip

        pid = fork();
        if (pid < 0) {
            perror("Fork error");
        } else if (pid == 0) { // Child process
            // If it's a background process, we disassociate it from the terminal
            if (background_flag) {
                printf("[%d] %d\n", 1, getpid()); // Background job info
                setpgid(0, 0); // Move child to a new process group
            }
            execute_command(args, input_file, output_file);
        } else { // Parent process
            if (background_flag) {
                // Don't wait for background processes
                printf("[%d] %d\n", 1, pid); // Print job ID and PID for background process
            } else {
                waitpid(pid, NULL, 0); // Wait for foreground process to complete
            }
        }
    }
    return 0;
}

