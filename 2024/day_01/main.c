#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int int_a = *((int *)a);
    int int_b = *((int *)b);

    if (int_a == int_b)
        return 0;
    else if (int_a < int_b)
        return -1;
    else
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

    const char s[2] = " ";
    char *token;
    int left_list[1000] = {};
    int right_list[1000] = {};
    int list_size = 0;

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        int left_item = atoi(strtok(buffer, s));
        int right_item = atoi(strtok(NULL, s));

        // printf("Adding to left list %d at index %d\n", left_item, list_size);

        left_list[list_size] = left_item;
        right_list[list_size] = right_item;
        list_size++;
    }

    int similarity_score = 0;
    for (int i = 0; i < 1000; i++)
    {
        int left_item = left_list[i];
        int second_list_occurances = 0;
        for (int j = 0; j < 1000; j++)
        {
            int right_item = right_list[j];
            if (left_item == right_item)
            {
                second_list_occurances++;
            }
        }

        similarity_score += left_item * second_list_occurances;
    }

    printf("Similarity score: %d\n", similarity_score);

    // qsort(left_list, 1000, sizeof(int), compare);
    // qsort(right_list, 1000, sizeof(int), compare);

    // int summed_distance = 0;
    // printf("Size of list: %d", sizeof(left_list));
    // for (int i = 0; i < 1000; i++)
    // {
    //     int diff = left_list[i] - right_list[i];
    //     int pos_diff = abs(diff);
    //     summed_distance += pos_diff;
    // }

    // printf("Summed distance: %d", summed_distance);

    fclose(file);
    return 0;
}