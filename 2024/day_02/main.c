#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_safe(char *list)
{
    const char s[2] = " ";

    int prev_is_increasing = -1;
    int is_increasing = -1;
    int is_safe = 1;

    int prev_val = atoi(strtok(list, s));
    char *curr_val = strtok(NULL, s);
    while (curr_val != NULL)
    {
        prev_is_increasing = is_increasing;

        if (!is_safe)
        {
            curr_val = strtok(NULL, s);
            continue;
        }

        int int_curr_val = atoi(curr_val);

        if (is_increasing == -1)
        {
            is_increasing = int_curr_val > prev_val;
        }

        int is_direction_bad = is_increasing ? int_curr_val < prev_val : int_curr_val > prev_val;
        if (is_direction_bad)
        {
            is_safe = 0;
            curr_val = strtok(NULL, s);
            is_safe = 0;
            printf("Exiting out on isIncreasing\n");
            continue;
        }

        int step = abs(int_curr_val - prev_val);
        // printf("Step: %d\n", step);
        if (step > 3 || step < 1)
        {
            is_safe = 0;
            curr_val = strtok(NULL, s);
            is_safe = 0;
            printf("Exiting out on step\n");
            continue;
        }

        prev_val = int_curr_val;
        curr_val = strtok(NULL, s);
    }

    return is_safe;
}

int main()
{
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    int safe_count = 0;

    int line_count = 1;

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        int is_line_safe = is_safe(buffer);
        if (is_line_safe)
        {
            printf("Line %d was safe.\n", line_count);
            safe_count++;
        }

        line_count++;
    }

    printf("Safe Count: %d\n", safe_count);

    return 0;
}