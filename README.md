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


