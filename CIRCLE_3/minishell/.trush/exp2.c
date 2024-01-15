#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

char* expand_home_directory(char* input) {
  char* output = (char*)malloc(sizeof(char) * strlen(input));
  char* start = input;
  char* end = NULL;
  char* tilde = NULL;
  char* home_dir = NULL;
  int output_index = 0;

  while ((tilde = strchr(start, '~')) != NULL) {
    // copy the characters before the ~
    strncpy(output + output_index, start, tilde - start);
    output_index += tilde - start;

    // get the user's home directory
    home_dir = getenv("HOME");
    if (home_dir == NULL) {
      home_dir = getpwuid(getuid())->pw_dir;
    }

    // copy the home directory into the output string
    strncpy(output + output_index, home_dir, strlen(home_dir));
    output_index += strlen(home_dir);

    // move the start pointer past the ~
    start = tilde + 1;
  }

  // copy the remaining characters
  strncpy(output + output_index, start, strlen(start));
  output_index += strlen(start);
  output[output_index] = '\0';

  return output;
}

int main(int ac, char **av) {

    // char* expanded_path1 = expand_tilde("~");
    // char* expanded_path2 = expand_tilde(path2);
    char *triple;
    int i = 0;
    while (++i < ac)
    {
        if (!strncmp(av[i], "/Users", 6))
            triple = av[i];
    }


    printf("av_%d :\t %s\n", i, getpwuid(getuid())->pw_dir);
    // printf("Expanded path 1: %s\n", expand_home_directory("~"));
    // printf("Expanded path 2: %s\n", expanded_path2);
    // free(expanded_path1);
    // free(expanded_path2);
    return 0;
}
