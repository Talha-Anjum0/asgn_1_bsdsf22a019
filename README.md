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


(3) Version3


#Overview

This project is a simple shell implementation in C, designed to mimic the basic functionality of a Unix-like shell. It allows users to execute commands, handle input and output redirection, use pipes, and run background processes. The shell runs in an interactive loop, accepting user input and executing commands with custom features.

##Features

Command Execution: Executes Unix commands by using execvp, which finds and runs commands available in the system path.

###Input/Output Redirection 

Supports redirection for input (<) and output (>). Users can specify files to redirect input from and output to.

Piping (|): Detects if a pipe character is used, which allows for chaining commands (currently supports basic piping structure).

Background Execution (&): Runs processes in the background by appending & at the end of the command, allowing the shell to continue without waiting for the process to complete.

Signal Handling: Uses a signal handler to prevent zombie processes by reaping background processes with SIGCHLD.
Interactive Prompt: Shows the current working directory along with a shell prompt to create a user-friendly experience.
