#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int countCharacters(char** tab, int rows, int cols) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char* str = tab[i][j];
            int k = 0;

            while (str[k] != '\0') {
                count++;
                k++;
            }
        }
    }

    return count;
}

int main() {
    char* tab[3][4] = {
        {"apple", "banana", "cherry", "date"},
        {"elephant", "fox", "giraffe", "horse"},
        {"ice cream", "juice", "kiwi", "on"}
    };

    int totalCharacters = countCharacters(tab, 3, 4);
    printf("Total number of characters: %d\n", totalCharacters);

    return 0;
}
