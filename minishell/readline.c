#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

// int main()
// {
// 	char* input;

// 	// Read input from the user
// 	while ((input = readline("bash$ ")) != NULL)
// 	{
// 		// Add the input to the history
// 		add_history(input);

// 		// Print the input
// 		printf("You entered: %s\n", input);

// 		// Free the input string
// 		free(input);
// 	}
// 	return 0;
// }


// using history

int main() {
    char* input;

    // Load the history file
    using_history();

    // Read input from the user
    while ((input = readline("s$ ")) != NULL) {
        // Add the input to the history
        add_history(input);

        // Print the input
        printf("You entered: %s\n\v", input);

        // Free the input string
        free(input);
    }

    // Save the history file
    write_history(".history");

    return 0;
}


// // using auto-completion

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// char* command_generator(const char* text, int state) {
//     static char* commands[] = {"echo", "ls", "cd", "pwd", NULL};
//     static int index = 0;
//     char* command;

//     if (!state) {
//         index = 0;
//     }

//     while ((command = commands[index++])) {
//         if (strncmp(command, text, strlen(text)) == 0) {
//             return strdup(command);
//         }
//     }

//     return NULL;
// }

// char** completion(const char* text, int start, int end) {
//     char** matches;

//     matches = (char**)rl_completion_matches(text, command_generator);

//     return matches;
// }

// int main() {
//     char* input;

//     // Set the completion function
//     rl_attempted_completion_function = completion;

//     // Read input from the user
//     while ((input = readline("$ ")) != NULL) {
//         // Add the input to the history
//         add_history(input);

//         // Print the input
//         printf("You entered: %s\n", input);

//         // Free the input string
//         free(input);
//     }
//     return 0;
// }


// // using custom key bindings

// #include <stdio.h>
// #include <stdlib.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// void move_to_end_of_line(int count, int key) {
//     rl_end_of_line(1, key);
// }

// int main() {
//     char* input;

//     // Bind the Ctrl-E key to move to end of line
//     rl_bind_keyseq("\\C-e", move_to_end_of_line);

//     // Read input from the user
//     while ((input = readline("$ ")) != NULL) {
//         // Add the input to the history
//         add_history(input);

//         // Print the input
//         printf("You entered: %s\n", input);

//         // Free the input string
//         free(input);
//     }

//     return 0;
// }





// -L/usr/local/lib -I/usr/local/include -lreadline
