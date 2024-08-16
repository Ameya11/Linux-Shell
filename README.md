# Linux Shell: Building a Simple Shell

## Objective

The primary objective of this project is to implement a custom shell that can handle basic Linux commands, manage processes, handle signals, and support background execution. The shell is built incrementally with various features added step by step.

## Features Implemented

### Part A: A Simple Shell
- **Command Execution**: The shell reads user input, tokenizes it, forks a child process, and executes the command using `exec`. The parent process waits for the child to finish and then reaps it.
- **Custom Prompt**: The shell displays a custom prompt `"$ "` for user input.
- **Error Handling**: The shell handles errors gracefully, notifying users of any issues and continuing to prompt for input.

### Part B: Background Execution
- **Background Processes**: Commands followed by `&` are executed in the background, allowing the shell to continue accepting new commands without waiting for the previous one to finish.
- **Child Process Reaping**: The shell periodically checks and reaps terminated background processes, printing a message when a background process finishes.

### Part C: Exit Command
- **Graceful Exit**: The shell supports an `exit` command that terminates the shell. Before exiting, the shell ensures all background processes are terminated and cleans up resources.

### Part D: Ctrl+C Signal Handling
- **Signal Handling**: The shell handles the `SIGINT` signal (triggered by `Ctrl+C`) to terminate only the foreground process, without affecting the shell itself or any background processes.

### Part E: Serial and Parallel Execution
- **Serial Execution**: Commands separated by `&&` are executed one after the other in the foreground. The next command is only executed after the previous one completes.
- **Parallel Execution**: Commands separated by `&&&` are executed simultaneously in the foreground. The shell returns to the prompt after all commands have finished.

## Usage

To compile and run the shell:

```bash
gcc my_shell.c -o my_shell
./my_shell
```

### Commands Supported
- **Basic Commands**: `ls`, `cat`, `echo`, `sleep`, etc.
- **Change Directory**: `cd <directory>`
- **Background Execution**: `<command> &`
- **Exit Shell**: `exit`
- **Serial Execution**: `<command1> && <command2>`
- **Parallel Execution**: `<command1> &&& <command2>`

### Error Handling
- The shell will notify the user of incorrect commands or arguments and prompt for the next input without crashing.

## Testing

The shell was thoroughly tested with various Linux commands in both foreground and background modes. Commands such as `sleep`, `ps`, and `ls` were used to verify the correct execution and management of processes.

## Submission

- The solution is contained within the file `my_shell.c`.

## Author

This solution was implemented as part of the Operating Systems course assignments. If you have any questions or suggestions, feel free to reach out via GitHub.
