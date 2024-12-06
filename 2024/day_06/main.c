#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int grid_size = 130;

enum Direction
{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

enum Direction turn(enum Direction current_direction)
{
    if (current_direction == UP)
    {
        return RIGHT;
    }
    else if (current_direction == RIGHT)
    {
        return DOWN;
    }
    else if (current_direction == DOWN)
    {
        return LEFT;
    }
    else
    {
        return UP;
    }
}

struct Coords
{
    int x;
    int y;
};

struct Coords move(struct Coords coords, enum Direction dir)
{
    struct Coords new_coords = coords;
    if (dir == UP)
    {
        new_coords.y--;
    }
    else if (dir == RIGHT)
    {
        new_coords.x++;
    }
    else if (dir == DOWN)
    {
        new_coords.y++;
    }
    else if (dir == LEFT)
    {
        new_coords.x--;
    }

    return new_coords;
}

int valid_coords(struct Coords coords)
{
    return (0 <= coords.x && coords.x < grid_size) && (0 <= coords.y && coords.y < grid_size);
}

struct Cell
{
    int is_wall;
    // up, right, down, left
    int visited_in_directions[4];
};

int main()
{
    int infinite_loop_counter = 0;
    for (int a = 0; a < grid_size; a++)
    {
        for (int b = 0; b < grid_size; b++)
        {
            char *filename = "input.txt";
            FILE *file = fopen(filename, "r");
            if (file == NULL)
            {
                printf("Could not open file %s\n", filename);
                return 1;
            }

            struct Cell grid[grid_size][grid_size] = {};
            struct Coords current_coords = {0, 0};
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
                        current_coords.x = i;
                        current_coords.y = line_i;
                    }
                }
                line_i++;
            }

            if (grid[a][b].is_wall || (b == current_coords.x && a == current_coords.y))
            {
                continue;
            }

            struct Cell new_wall = {1, {}};
            grid[a][b] = new_wall;

            printf("Starting at (%d, %d)\n", current_coords.x, current_coords.y);

            int loop_counter = 0;
            while (1)
            {
                loop_counter++;
                // printf("New loop: %d\n", loop_counter);

                struct Coords new_coords = move(current_coords, dir);
                if (!valid_coords(new_coords))
                {
                    printf("Hit the edge at (%d, %d)\n", new_coords.x, new_coords.y);
                    break;
                }

                // printf("Trying to move to (%d, %d)\n", new_coords.x, new_coords.y);

                struct Cell next_cell = grid[new_coords.y][new_coords.x];
                enum Direction direction_after_turn = turn(dir);

                if (next_cell.is_wall)
                {
                    grid[current_coords.y][current_coords.x].visited_in_directions[dir] = 1;
                    dir = direction_after_turn;
                    continue;
                }

                if (grid[new_coords.y][new_coords.x].visited_in_directions[dir] == 1)
                {
                    printf("Exiting out of infinite loop\n");
                    infinite_loop_counter++;
                    break;
                }

                grid[new_coords.y][new_coords.x].visited_in_directions[dir] = 1;
                current_coords = new_coords;
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
            fclose(file);
        }
    }

    printf("Infinite loop counter: %d\n", infinite_loop_counter);

    return 0;
}