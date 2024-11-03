#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For chdir
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_HISTORY 10
#define HISTORY_FILE ".my_shell_history"

// Array to store the history of commands
char *history[MAX_HISTORY];
int history_count = 0;

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

// Execute the command (this can be extended for more complex behavior)
void execute_command(const char *command) {
    if (strncmp(command, "cd ", 3) == 0) {
        const char *path = command + 3; // Get the path after "cd "
        if (chdir(path) != 0) {
            perror("cd failed"); // Handle errors if chdir fails
        }
    } else {
        printf("Executing: %s\n", command);
        // Here you could use system() or fork/exec to run the command
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
