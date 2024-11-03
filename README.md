# asgn_1_bsdsf22a019

(1) Version1

# PUCITshell

PUCITshell is a simple Unix-like shell written in C that allows users to execute commands in a command-line interface. It features basic command execution and displays the current working directory in the prompt.

## Features

- Displays the current working directory in the prompt.
- Executes commands using `execvp`.
- Handles empty commands and errors gracefully.
- Supports command execution in a child process.

## Requirements

- A C compiler (GCC recommended).
- A Unix-like operating system (Linux, macOS) for compatibility.


### Instructions for Customization
- Replace `yourusername` in the clone command with your actual GitHub username.
- Modify the features or instructions according to any additional functionalities you may implement in the future.
- Add any relevant acknowledgments or references if applicable.

Feel free to ask if you need further adjustments or additional sections!


(2) Version2


# PUCITshell

PUCITshell is a simple Unix-like shell implemented in C that supports command execution, input/output redirection, and piping between commands. It is designed to provide a basic command-line interface for users to interact with the operating system.

## Features

- **Command Execution**: Executes commands using the `execvp` function.
- **Input/Output Redirection**: Supports redirecting standard input and output using `<` and `>` operators.
- **Piping**: Allows the output of one command to be used as the input for another command using the `|` operator.
- **Current Directory Prompt**: Displays the current working directory in the shell prompt.

## Requirements

- A C compiler (GCC recommended).
- A Unix-like operating system (Linux, macOS) for compatibility.



### Instructions for Customization
- Make sure to replace `yourusername` in the clone command with your actual GitHub username.
- You can add specific acknowledgments or references if applicable.

Feel free to adjust any sections to better fit your project! Let me know if you need further modifications or additions.

(3) version3

# PUCITshell

A simple shell implementation in C that supports basic command execution, input/output redirection, and background processes.

## Features

- **Custom Prompt**: Displays a prompt with the current working directory in the format: `PUCITshell@<current_directory>$`.
- **Command Execution**: Executes commands entered by the user.
- **Input and Output Redirection**: Supports redirection of input (`<`) and output (`>`).
- **Background Execution**: Allows commands to run in the background using `&` at the end of the command.
- **Signal Handling**: Handles `SIGCHLD` signals to clean up terminated background processes and avoid zombie processes.

## Getting Started

### Prerequisites

To compile and run the shell, you need:

- A C compiler (e.g., `gcc`).
- A Unix-based operating system (Linux, macOS, etc.).

(4) version4


# Simple Shell Program

This is a simple shell program implemented in C that supports command history, allowing users to repeat previously issued commands. It uses the `readline` library for enhanced input handling, including command navigation with the up and down arrow keys.

## Features

- **Command History**: Maintains a history of the last 10 commands. Users can repeat commands using the `!number` syntax (e.g., `!-1` for the last command).
- **Change Directory**: Supports the `cd` command to change the current working directory.
- **Enhanced Input**: Utilizes the `readline` library for improved user input handling.

## Requirements

- GCC compiler
- `readline` library

### Install Readline Library

To install the `readline` library on Debian-based systems (like Ubuntu), run:

```bash
sudo apt-get install libreadline-dev

#### To compile use this

gcc version4.c -o version4 $(pkg-config --cflags --libs readline) -lncurses

#### to run 

./version4
 

(5) version5

# Simple Shell Program

This project is a simple shell implemented in C that includes both built-in and external command execution capabilities. The shell supports command history and allows users to repeat previous commands. It utilizes the `readline` library for enhanced command line input.

## Features

- **Built-in Commands**:
  - `cd <path>`: Changes the current working directory.
  - `exit`: Terminates the shell session.
  - `jobs`: Lists currently running background processes.
  - `kill <pid>`: Terminates a specified background process by its PID.
  - `help`: Displays a list of available built-in commands and their syntax.

- **Command History**: Maintains a history of the last 10 commands, which can be repeated using `!number`.

- **Enhanced Input Handling**: Uses the `readline` library for command line editing, including the ability to navigate command history with arrow keys.

## Requirements

- **GCC Compiler**: Ensure you have `gcc` installed to compile the program.
- **Readline Library**: The program requires the `readline` library. Install it using:

  ```bash
  sudo apt-get install libreadline-dev

### to compile

gcc version4.c -o version4 -lreadline -lncurses

#### to run

./version5
