/*

   Tortoise graphics

   A 25x25 square map with the tortoise moving on it.
   Tortoise's default position is the top left corner of the map [0, 0].
   Tortoise's default direction of movement is down.
   The tortoise holds a marker. The marker can be up or down. Marker`s default
   position is up.
   When moving with the marker down, the tortoise draws lines of it's route.
   When moving with the marker up, the tortoise does not draw any lines.
   The user should input a list of commands.
   Each one must be separated with a space.
   

   Examples of commands sequences:
   #1 [Square]: 5 6 4 5 6 2 5 10 3 5 10 3 5 10 3 5 10 1 6 7
   #2 [Smile Face]: 5 8 4 5 8 3 2 5 1 1 4 5 3 4 2 5 1 1 3 5 2 3 5 4 2 1 5 1 3 5 1 2 5 5 1 3 5 1 4 5 1 2 1 6 7
   // TODO 
   #3 [Triangle]: 
            
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 25
#define MAX_COMMANDS 1000

// Directions of tortoise's movement relative to the *center of map*
typedef enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN
} Dirs;

void help(void);
void read_commands(unsigned short[MAX_COMMANDS]);
void print_commands(unsigned short[MAX_COMMANDS]);
void execute_commands(unsigned short[MAX_COMMANDS], unsigned short[MAP_SIZE][MAP_SIZE]);
void draw_map(unsigned short[MAP_SIZE][MAP_SIZE]);

int main(void)
{
    help();

    unsigned short commands[MAX_COMMANDS] = {0};
    unsigned short map[MAP_SIZE][MAP_SIZE] = {0};

    read_commands(commands);
    print_commands(commands);
    execute_commands(commands, map);

    return 0;
}

void help(void)
{
    printf("Tortoise commands:\n\t\
    1 - Put the marker up\n\t\
    2 - Put the marker down\n\t\
    3 - Turn right\n\t\
    4 - Turn left\n\t\
    5, N - Move N squares forward\n\
    \rGeneral commands:\n\t\
    6 - Draw the map with tortoise's route\n\t\
    7 - End of command sequence\n");
}

void read_commands(unsigned short commands[MAX_COMMANDS])
{
    puts("Input commands separated by spaces:");
    for (unsigned int i = 0; i < MAX_COMMANDS; i++)
    {
        scanf("%hu", &commands[i]);
        // No commands below 1. Also cannot move out of MAP_SIZE for command 5
        if (commands[i] < 1 || commands[i] > MAP_SIZE)
        {
            puts("Invalid command!");
            exit(EXIT_FAILURE);
        }
        // Stop reading commands if it's the end of the sequence
        if (i > 1 && commands[i] == 7 && commands[i - 1] != 5)
        {
            return;
        }
    }
}

void print_commands(unsigned short commands[MAX_COMMANDS])
{
    puts("Commands are:");
    for (unsigned int i = 0; i < MAX_COMMANDS; i++)
    {
        printf("%hu ", commands[i]);
        if (commands[i] == 7)
        {
            return;
        }
    }
    puts("");
}

void draw_map(unsigned short map[MAP_SIZE][MAP_SIZE])
{
    printf("\n%20s%s%20s\n", "", "RESULT", "");
    for (unsigned short row = 0; row < MAP_SIZE - 1; row++)
    {
        for (unsigned short col = 0; col < MAP_SIZE - 1; col++)
        {
            switch (map[row][col])
            {
            case 0:
                printf("%c ", '.');
                break;
            case 1:
                printf("%c ", '*');
                break;
            }
        }
        puts("");
    }
}

void execute_commands(unsigned short commands[MAX_COMMANDS], unsigned short map[MAP_SIZE][MAP_SIZE])
{
    puts("\nExecuting commands...");
    // Default position of the tortoise
    unsigned short t_x = 0, t_y = 0;
    // Default direction of the tortoise
    Dirs t_dir = DOWN;
    // Default position of the marker
    bool marker_up = true;
    for (unsigned int i = 0; i < MAX_COMMANDS; i++)
    {
        switch (commands[i])
        {
        // Marker up
        case 1:
            marker_up = true;
            break;
        // Marker down
        case 2:
            marker_up = false;
            // Mark current square as part of the route
            map[t_y][t_x] = 1;
            break;
        // Turn right
        case 3:
            switch (t_dir)
            {
            case DOWN:
                t_dir = LEFT;
                break;
            case UP:
                t_dir = RIGHT;
                break;
            case LEFT:
                t_dir = UP;
                break;
            case RIGHT:
                t_dir = DOWN;
                break;
            }
            break;
        // Turn left
        case 4:
            switch (t_dir)
            {
            case DOWN:
                t_dir = RIGHT;
                break;
            case UP:
                t_dir = LEFT;
                break;
            case LEFT:
                t_dir = DOWN;
                break;
            case RIGHT:
                t_dir = UP;
                break;
            }
            break;
        // Move forward
        case 5:
            // Number of squares to move
            unsigned short dist = commands[i + 1];
            switch (t_dir)
            {
            case DOWN:
                if (t_y + dist > MAP_SIZE)
                {
                    puts("Out of map!");
                    exit(EXIT_FAILURE);
                }
                for (unsigned short step = 1; step <= dist; step++)
                {
                    t_y++;
                    if (!marker_up)
                        map[t_y][t_x] = 1;
                }
                break;
            case UP:
                if (t_y - dist < 0)
                {
                    puts("Out of map!");
                    exit(EXIT_FAILURE);
                }
                for (unsigned short step = 1; step <= dist; step++)
                {
                    t_y--;
                    if (!marker_up)
                        map[t_y][t_x] = 1;
                }
                break;
            case LEFT:
                if (t_x - dist < 0)
                {
                    puts("Out of map!");
                    exit(EXIT_FAILURE);
                }
                for (unsigned short step = 1; step <= dist; step++)
                {
                    t_x--;
                    if (!marker_up)
                        map[t_y][t_x] = 1;
                }
                break;
            case RIGHT:
                if (t_x + dist > MAP_SIZE)
                {
                    puts("Out of map!");
                    exit(EXIT_FAILURE);
                }
                for (unsigned short step = 1; step <= dist; step++)
                {
                    t_x++;
                    if (!marker_up)
                        map[t_y][t_x] = 1;
                }
                break;
            }
            // Next command after 5 should not be processed any more
            i++;
            break;
        // Draw map
        case 6:
            draw_map(map);
            break;
        // Exit
        case 7:
            return;
        }
    }
}