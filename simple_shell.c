#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

/**
 * displayPrompt - Displays the shell prompt.
 */
void displayPrompt(void)
{
    printf("$ ");
    fflush(stdout);
}

/**
 * executeCommand - Executes a command in a child process.
 * @command: The command to execute.
 */
void executeCommand(char *command)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) /* Child process */
    {
        if (execlp(command, command, NULL) == -1)
        {
            perror("Execution error");
            exit(EXIT_FAILURE);
        }
    }
    else /* Parent process */
    {
        wait(NULL);
    }
}

/**
 * main - Main entry point of the simple shell.
 * Return: Always 0.
 */
int main(void)
{
    char input[MAX_INPUT_LENGTH];

    while (1)
    {
        displayPrompt();

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break; /* Exit on Ctrl+D */
        }

        input[strcspn(input, "\n")] = '\0'; /* Remove trailing newline */

        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting shell...\n");
            break;
        }

        executeCommand(input);
    }

    return 0;
}
