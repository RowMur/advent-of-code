#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int extract_items(int *list, char *string)
{
    int item_count = 0;

    const char s[2] = " ";
    char *token = strtok(string, s);
    while (token != NULL)
    {
        item_count++;
        list[item_count - 1] = atoi(token);
        token = strtok(NULL, s);
    }

    return item_count;
}

int is_safe(int *list, int list_size)
{
    int is_increasing = -1;

    for (int i = 1; i < list_size; i++)
    {
        int prev_val = list[i - 1];
        int curr_val = list[i];

        if (curr_val == 0)
        {
            return 1;
        }

        if (is_increasing == -1)
        {
            is_increasing = curr_val > prev_val;
        }

        int is_direction_bad = is_increasing ? curr_val < prev_val : curr_val > prev_val;
        if (is_direction_bad)
        {
            printf("Exiting out on isIncreasing\n");
            return 0;
        }

        int step = abs(curr_val - prev_val);
        if (step > 3 || step < 1)
        {
            printf("Exiting out on step\n");
            return 0;
        }
    }

    return 1;
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
        int items[20] = {};
        int item_count = extract_items(items, buffer);

        // int is_line_safe = is_safe(items, item_count);
        int is_line_safe = 0;
        for (int i = 0; i < item_count; i++)
        {
            if (is_line_safe)
            {
                break;
            }

            int items_with_dropped[20] = {};
            for (int j = 0; j < item_count; j++)
            {
                if (j < i)
                {
                    items_with_dropped[j] = items[j];
                }
                else if (j > i)
                {
                    items_with_dropped[j - 1] = items[j];
                }
            }

            is_line_safe = is_safe(items_with_dropped, item_count - 1);
        }

        if (is_line_safe)
        {
            printf("Line %d was safe.\n", line_count);
            safe_count++;
        }
        else
        {
            printf("Line %d was unsafe.\n", line_count);
        }

        line_count++;
    }

    printf("Safe Count: %d\n", safe_count);

    return 0;
}