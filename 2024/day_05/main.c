#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    // First array is each number
    // Second array is the numbers that must occur before the first
    int rules[100][100] = {};
    int summed_middle_pages = 0;

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        if (buffer[0] == '\n')
        {
            continue;
        }

        char separator = buffer[2];
        if (separator == '|')
        {
            const char sep[2] = "|";
            int first_num = atoi(strtok(buffer, sep));
            int second_num = atoi(strtok(NULL, sep));

            rules[second_num][first_num] = 1;
            continue;
        }

        printf("Checking line: %s", buffer);

        int page_order[30] = {};
        int page_count = 0;

        const char sep[2] = ",";
        char *token = strtok(buffer, sep);
        while (token != NULL)
        {
            page_count++;
            page_order[page_count - 1] = atoi(token);
            token = strtok(NULL, sep);
        }

        int is_correct_order = 1;
        for (int page_i = 0; page_i < page_count; page_i++)
        {
            for (int future_page_i = page_i + 1; future_page_i < page_count; future_page_i++)
            {
                int page = page_order[page_i];
                int future_page = page_order[future_page_i];
                // printf("Checking %d against %d\n", page, future_page);
                if (rules[page][future_page])
                {
                    is_correct_order = 0;
                }
            }
        }

        if (is_correct_order)
        {
            printf("Correct\n");
            int middle_page_index = ((page_count + 1) / 2) - 1;
            int middle_val = page_order[middle_page_index];
            printf("Adding %d\n", middle_val);
            summed_middle_pages += page_order[middle_page_index];
        }
        else
        {
            printf("Incorrect\n");
        }
    }

    printf("Summed correct middle pages: %d", summed_middle_pages);

    fclose(file);
    return 0;
}