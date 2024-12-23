#include <stdio.h>

int validate_coord(int coord)
{
    return coord >= 0 && coord < 140;
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

    char grid[140][140] = {};

    const unsigned MAX_LENGTH = 1000000;
    char buffer[MAX_LENGTH];
    int line_count = 0;
    while (fgets(buffer, MAX_LENGTH, file))
    {
        for (int i = 0; i < 140; i++)
        {
            grid[line_count][i] = buffer[i];
        }

        line_count++;
    }

    // int directions[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    int match_count = 0;
    // char expected[4] = "XMAS";

    int cross_vectors[2][2] = {{1, 1}, {1, -1}};

    for (int i = 0; i < 140; i++)
    {
        for (int j = 0; j < 140; j++)
        {
            if (grid[i][j] != 'A')
            {
                continue;
            }

            int is_match = 1;

            for (int cross_dir = 0; cross_dir < 2; cross_dir++)
            {
                printf("Cross dir: %d\n", cross_dir);
                int x_comp = cross_vectors[cross_dir][0];
                int y_comp = cross_vectors[cross_dir][1];

                int x_coord = i + x_comp;
                if (!validate_coord(x_coord))
                {
                    is_match = 0;
                    break;
                }

                int y_coord = j + y_comp;
                if (!validate_coord(y_coord))
                {
                    is_match = 0;
                    break;
                }

                printf("First char at %d : %d\n", x_coord, y_coord);
                char first_char = grid[x_coord][y_coord];

                if (first_char != 'M' && first_char != 'S')
                {
                    is_match = 0;
                    break;
                }

                x_comp = cross_vectors[cross_dir][0] * -1;
                y_comp = cross_vectors[cross_dir][1] * -1;

                x_coord = i + x_comp;
                if (!validate_coord(x_coord))
                {
                    is_match = 0;
                    break;
                }

                y_coord = j + y_comp;
                if (!validate_coord(y_coord))
                {
                    is_match = 0;
                    break;
                }

                printf("Second char at %d : %d\n", x_coord, y_coord);
                char second_char = grid[x_coord][y_coord];
                if (second_char != 'M' && second_char != 'S')
                {
                    is_match = 0;
                    break;
                }

                if (first_char == second_char)
                {
                    is_match = 0;
                    break;
                }
            }

            if (is_match)
            {
                printf("Found match starting at x: %d, y: %d\n", i, j);
                match_count++;
            }
            else
            {
                printf("Wasn't a match starting at x: %d, y: %d\n", i, j);
            }

            // for (int dir_i = 0; dir_i < 8; dir_i++)
            // {
            //     int is_match = 1;
            //     for (int char_i = 0; char_i < 4; char_i++)
            //     {
            //         int x_coord = i + directions[dir_i][0] * char_i;
            //         if (x_coord < 0 || x_coord >= 140)
            //         {
            //             is_match = 0;
            //             break;
            //         }
            //         int y_coord = j + directions[dir_i][1] * char_i;
            //         if (y_coord < 0 || y_coord >= 140)
            //         {
            //             is_match = 0;
            //             break;
            //         }

            //         char expected_char = expected[char_i];
            //         char grid_char = grid[x_coord][y_coord];
            //         if (expected_char != grid_char)
            //         {
            //             printf("Invalid char with starting point x: %d, y: %d in direction %d. Expected: %c, got: %c\n", i, j, dir_i, expected_char, grid_char);
            //             is_match = 0;
            //             break;
            //         }
            //     }

            //     if (is_match)
            //     {
            //         printf("Found match starting at x: %d, y: %d in direction: %d\n", i, j, dir_i);
            //         match_count++;
            //     }
            // }
        }
    }

    printf("Match count: %d\n", match_count);

    fclose(file);
    return 0;
}