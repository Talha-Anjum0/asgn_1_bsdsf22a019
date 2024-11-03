#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For chdir and fork
#include <signal.h> // For kill signal
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAX_HISTORY 10
#define HISTORY_FILE ".my_shell_history"
#define MAX_PROCESSES 100

// Array to store the history of commands
char *history[MAX_HISTORY];
int history_count = 0;

// Array to store background processes
pid_t background_processes[MAX_PROCESSES];
int bg_process_count = 0;

// Load history from the history file
void load_history() {
    FILE *file = fopen(HISTORY_FILE, "r");
    if (!file) return;

    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1 && history_count < MAX_HISTORY) {
        line[strcspn(line, "\n")] = 0; // Remove newline character
        history[history_count++] = strdup(line);
    }
    free(line);
    fclose(file);
}

// Save history to the history file
void save_history() {
    FILE *file = fopen(HISTORY_FILE, "w");
    if (!file) return;

    for (int i = 0; i < history_count; i++) {
        fprintf(file, "%s\n", history[i]);
    }
    fclose(file);
}

// Add command to history
void add_to_history(const char *command) {
    if (history_count == MAX_HISTORY) {
        free(history[0]); // Free the oldest command
        for (int i = 1; i < MAX_HISTORY; i++) {
            history[i - 1] = history[i]; // Shift commands up
        }
        history_count--; // Reduce history count
    }
    history[history_count++] = strdup(command); // Add new command
}

// Get command from history based on index
char *get_command(int index) {
    if (index < 1 || index > history_count) return NULL; // Index out of bounds
    return history[index - 1]; // Return the command at the specified index
}

// List background processes
void list_jobs() {
    if (bg_process_count == 0) {
        printf("No background jobs running.\n");
        return;
    }
    
    printf("Background jobs:\n");
    for (int i = 0; i < bg_process_count; i++) {
        printf("[%d] %d\n", i + 1, background_processes[i]);
    }
}

// Change directory command
void cd_command(const char *path) {
    if (chdir(path) != 0) {
        perror("cd failed"); // Handle errors if chdir fails
    }
}

// Terminate background process by PID
void kill_command(int pid) {
    if (kill(pid, SIGKILL) == 0) {
        printf("Process %d killed.\n", pid);
    } else {
        perror("kill failed");
    }
}

// Execute built-in commands
int execute_builtin_command(const char *command) {
    if (strncmp(command, "cd ", 3) == 0) {
        const char *path = command + 3; // Get the path after "cd "
        cd_command(path);
        return 1; // Built-in command executed
    } else if (strcmp(command, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "jobs") == 0) {
        list_jobs();
        return 1; // Built-in command executed
    } else if (strncmp(command, "kill ", 5) == 0) {
        int pid = atoi(command + 5); // Get the PID to kill
        kill_command(pid);
        return 1; // Built-in command executed
    } else if (strcmp(command, "help") == 0) {
        printf("Built-in commands:\n");
        printf("  cd <path>      Change the current working directory\n");
        printf("  exit           Terminate the shell\n");
        printf("  jobs           List background jobs\n");
        printf("  kill <pid>     Terminate the specified background process\n");
        printf("  help           Show this help message\n");
        return 1; // Built-in command executed
    }
    return 0; // Not a built-in command
}

// Execute external commands
void execute_external_command(char *command) {
    pid_t pid = fork();
    if (pid == 0) {
        // In child process
        char *args[2];
        args[0] = command;
        args[1] = NULL;
        execvp(args[0], args); // Execute the command
        perror("Execution failed"); // If execvp fails
        exit(1); // Exit child process
    } else if (pid > 0) {
        // In parent process
        background_processes[bg_process_count++] = pid; // Store PID of background process
        waitpid(pid, NULL, 0); // Wait for child process to finish
    } else {
        perror("Fork failed"); // If fork fails
    }
}

// Execute the command
void execute_command(const char *command) {
    if (!execute_builtin_command(command)) {
        execute_external_command((char *)command); // Treat as an external command
    }
}

int main() {
    load_history(); // Load previous commands from history file

    char *input;
    while (1) {
        input = readline("> "); // Prompt user for input
        if (!input) {
            printf("\n"); // Handle Ctrl+D (EOF)
            break;
        }

        // Check for command repetition using history
        if (input[0] == '!') {
            int index = atoi(input + 1); // Get the index from the input
            if (index == -1) index = history_count; // Last command
            char *command = get_command(index); // Retrieve command from history
            if (command) {
                execute_command(command); // Execute retrieved command
            } else {
                printf("No such command in history.\n");
            }
        } else {
            add_to_history(input); // Add new command to history
            execute_command(input); // Execute the new command
        }

        save_history(); // Save history after each command
        free(input); // Free memory allocated by readline
    }

    // Free the history memory before exit
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }

    return 0;
}
