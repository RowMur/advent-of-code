#include <stdio.h>

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

struct Cell
{
    int is_wall;
    // up, right, down, left
    int visited_in_directions[4];
};

int main()
{
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 1;
    }

    static const int grid_size = 130;

    struct Cell grid[grid_size][grid_size] = {};
    int current_x = 0;
    int current_y = 0;
    enum Direction dir = UP;

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    int line_i = 0;
    while (fgets(buffer, MAX_LENGTH, file))
    {
        for (int i = 0; i < grid_size; i++)
        {
            char cell = buffer[i];
            if (cell == '.')
            {
                struct Cell new_cell = {0, {}};
                grid[line_i][i] = new_cell;
            }
            else if (cell == '#')
            {
                struct Cell new_cell = {1, {}};
                grid[line_i][i] = new_cell;
            }
            else if (cell == '^')
            {
                struct Cell new_cell = {0, {}};
                new_cell.visited_in_directions[dir] = 1;
                grid[line_i][i] = new_cell;
                current_x = i;
                current_y = line_i;
            }
        }
        line_i++;
    }

    printf("Starting at (%d, %d)\n", current_x, current_y);

    int loop_counter = 0;
    while (1)
    {
        loop_counter++;
        printf("New loop: %d\n", loop_counter);

        int next_x = current_x;
        int next_y = current_y;
        if (dir == UP)
        {
            next_y--;
        }
        else if (dir == RIGHT)
        {
            next_x++;
        }
        else if (dir == DOWN)
        {
            next_y++;
        }
        else if (dir == LEFT)
        {
            next_x--;
        }

        if (!(0 <= next_x && next_x < grid_size) || !(0 <= next_y && next_y < grid_size))
        {
            printf("Hit the edge at (%d, %d)\n", next_x, next_y);
            break;
        }

        printf("Trying to move to (%d, %d)\n", next_x, next_y);

        struct Cell next_cell = grid[next_y][next_x];
        if (!next_cell.is_wall)
        {
            grid[next_y][next_x].visited_in_directions[dir] = 1;
            current_x = next_x;
            current_y = next_y;
            continue;
        }
        else if (next_cell.is_wall)
        {
            if (dir == UP)
            {
                dir = RIGHT;
            }
            else if (dir == RIGHT)
            {
                dir = DOWN;
            }
            else if (dir == DOWN)
            {
                dir = LEFT;
            }
            else if (dir == LEFT)
            {
                dir = UP;
            }
        }
    }

    printf("Looped %d times\n", loop_counter);

    int visited_counter = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (grid[i][j].visited_in_directions[k])
                {
                    visited_counter++;
                    break;
                }
            }
        }
    }

    printf("Visited %d cells\n", visited_counter);

    return 0;
}