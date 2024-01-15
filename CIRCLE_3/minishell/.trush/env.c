#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 1024

char* get_command_path(const char *command) {
    // Get the value of the "PATH" environment variable
    char *path = getenv("PATH");
    if (path == NULL) {
        printf("The PATH environment variable is not set.\n");
        return NULL;
    }

    // Split the PATH variable into individual directories
    char *dir = strtok(path, ":");
    while (dir != NULL) {
        // Construct the full path of the command
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, MAX_PATH_LENGTH, "%s/%s", dir, command);

        // Check if the command exists and is executable
        if (access(full_path, X_OK) == 0) {
            // ç
            return strdup(full_path);
        }

        // Get the next directory
        dir = strtok(NULL, ":");
    }

    // The command was not found in any directory
    return NULL;
}

int main(int ac, char **av)
{
		printf("path of command %s is: %s\n", av[1], get_command_path(av[1]));
}
