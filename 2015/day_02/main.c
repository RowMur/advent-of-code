#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_paper_needed(int width, int height, int length)
{
    const int UNIQUE_SIDES = 3;
    int sides[UNIQUE_SIDES];
    sides[0] = width * height;
    sides[1] = width * length;
    sides[2] = length * height;

    int paper_needed = 0;
    int smallest_side = 0;

    int i;
    for (i = 0; i < UNIQUE_SIDES; i++)
    {
        int side = sides[i];
        if (smallest_side == 0 || side < smallest_side)
        {
            smallest_side = side;
        }

        paper_needed += side * 2;
    }

    paper_needed += smallest_side;
    return paper_needed;
}

int calculate_ribbon_needed(int width, int height, int length)
{
    const int NUM_DIMENSIONS = 3;
    int combos[NUM_DIMENSIONS];
    combos[0] = width + height;
    combos[1] = width + length;
    combos[2] = length + height;

    int smallest_combo = 0;
    int i;
    for (i = 0; i < NUM_DIMENSIONS; i++)
    {
        int combo = combos[i];
        if (smallest_combo == 0 || combo < smallest_combo)
        {
            smallest_combo = combo;
        }
    }

    int wrapping_ribbon = smallest_combo * 2;
    int bow_ribbon = width * height * length;
    return wrapping_ribbon + bow_ribbon;
}

int main()
{
    const char SEPARATOR = 'x';

    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    int total_paper_needed = 0;
    int total_ribbon_needed = 0;

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    while (fgets(buffer, MAX_LENGTH, file))
    {
        int width = 0;
        int length = 0;
        int height = 0;

        char current_string[16] = "";

        int i;
        for (i = 0; i < sizeof(buffer); i++)
        {
            if (height != 0)
            {
                break;
            }

            char c = buffer[i];
            if (c == SEPARATOR || c == '\n')
            {
                int dimension = atoi(current_string);
                if (width == 0)
                {
                    width = dimension;
                }
                else if (length == 0)
                {
                    length = dimension;
                }
                else if (height == 0)
                {
                    height = dimension;
                }

                current_string[0] = '\0';
            }
            else
            {
                strncat(current_string, &c, 1);
            }
        }

        int paper_needed = calculate_paper_needed(width, height, length);
        int ribbon_needed = calculate_ribbon_needed(width, height, length);
        total_paper_needed += paper_needed;
        total_ribbon_needed += ribbon_needed;
    }

    printf("Total Paper Needed: %d\n", total_paper_needed);
    printf("Total Ribbon Needed: %d\n", total_ribbon_needed);

    fclose(file);
    return 0;
}