#include <stdio.h>

int main() {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    int floor = 0;
    int char_index = 0;
    int basement_index = 0;

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        char_index++;
        if (ch == '(') {
            floor++;
        } else if (ch == ')') {
            floor--;
        }

        if (floor < 0 && basement_index == 0) {
            basement_index = char_index;
        }
    }

    printf("Floor: %d\n", floor);
    printf("Basement enter index: %d\n", basement_index);

    fclose(file);
    return 0;
}