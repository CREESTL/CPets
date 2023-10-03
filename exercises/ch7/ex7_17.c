/*

    Tortoise and hair race.

    Tortoise and Hair (T & H) start a race on a narrow track of 1x70 squares.
    T & H have different types of movements. The track is slippery, so sometimes
    one can even go backwards.

    =====================================================================================
    Animal      |       Movement        |       % of time       |       Squares         |

    Tortoise        Trudge fast                 50                      3 forward
                    Slip back                   20                      6 backward
                    Trudge slowly               30                      1 forward

    Hair            Sleep                       20                      None
                    Huge jump                   20                      9 forward
                    Huge slip back              10                      12 backward
                    Small jump                  30                      1 forward
                    Small slip back             20                      2 backward
    =====================================================================================

    If an animal crosses the 70-th square, it wins.
    If an animal moves behind 1-st square, it gets moved to the 1-st square.
    If T & H end up on the same square, T bites H and H says "OUCH".
    T & H positions should be displayed to the user.
    T & H might come to the finish line at the same time. Then it's a draw.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRACK_LENGTH 70
#define MIN_PROB 1
#define MAX_PROB 10

void start_race(int*, int*);
void show_track(int, int);
void race_step(int*, int*);
void t_step(int*);
void h_step(int*);
void call_winner(int, int);

int main(void)
{
    
    srand(time(NULL));

    int t_pos = 0;
    int h_pos = 0;
    start_race(&t_pos, &h_pos);
    call_winner(t_pos, h_pos);
}

/*
   Changes T & H positions until one wins the race
   Shows the track with T & H positions on it
*/
void start_race(int* t_pos, int* h_pos)
{
    int step = 1;
    while ((*t_pos <= TRACK_LENGTH) && (*h_pos <= TRACK_LENGTH))
    {
        printf("\n[STEP %d]\n", step);
        show_track(*t_pos, *h_pos);
        race_step(t_pos, h_pos);
        step++;
    }
    // Show track after the race to see winner's position
    show_track(*t_pos, *h_pos);
    
}

/*
   Shows the track with T & H positions on it
*/
void show_track(int t_pos, int h_pos)
{
    puts("");
    printf("%-20s%4d\n", "Tortoise position:", t_pos);
    printf("%-20s%4d\n\n", "Hair position:", h_pos);
    for (size_t square = 0; square <= TRACK_LENGTH + 10; square++)
    {
        if (square == t_pos && square != h_pos)
        {
            printf("%s", "T");
        }
        else if (square == h_pos && square != t_pos)
        {
            printf("%s", "H");
        }
        // T bites H
        else if (square == h_pos && h_pos == t_pos)
        {
            printf("%s", "OUCH!");
        }
        else 
        {
            // Show finish line
            if (square == TRACK_LENGTH)
            {
                printf("%s", "|");
            } else
            // Show track ground
            {
                printf("%s", "_");
            }
        }
    }
    puts("");
}

/*
   Changes T & H positions
*/
void race_step(int* t_pos, int* h_pos)
{
    
    t_step(t_pos);
    h_step(h_pos);
}

/*
   Changes T position
*/
void t_step(int* t_pos)
{
        
    // Generate a random number [1;10] to define T's next move
    int movement_type = MIN_PROB + rand() % (MAX_PROB - MIN_PROB + 1);
    if (movement_type >= 1 && movement_type <= 5)
    {
        // Trudge fast
        (*t_pos) += 3;
    } else if (movement_type >= 6 && movement_type <= 7)
    {
        // Slip back
        (*t_pos) -= 6;
        
    } else if (movement_type >= 8)
    {
        // Trudge slowly
        (*t_pos) -= 1;
    }
    // Move back to start if gone too far back
    if (*t_pos < 0)
        *t_pos = 0;
}

/*
   Changes H position
*/
void h_step(int* h_pos)
{
        
    // Generate a random number [1;10] to define H's next move
    int movement_type = MIN_PROB + rand() % (MAX_PROB - MIN_PROB + 1);
    if (movement_type >= 1 && movement_type <= 2)
    {
        // Sleep
        return;
    } else if (movement_type >= 3 && movement_type <= 4)
    {
       // Huge jump
       (*h_pos) += 9; 
    } else if (movement_type == 5)
    {
        // Huge slip back
       (*h_pos) -= 12;
    } else if (movement_type >= 6 && movement_type <=8)
    {
        // Small jump
       (*h_pos) += 1;
    } else if (movement_type >= 9)
    {
        // Small slip back
       (*h_pos) -= 2;
    }
    // Move back to start if gone too far back
    if (*h_pos < 0)
        *h_pos = 0;

}

/*
   Find out who won the race
*/
void call_winner(int t_pos, int h_pos)
{
    puts("\n===========WINNER===========");
    if (t_pos > TRACK_LENGTH && h_pos <= TRACK_LENGTH)
    {
        puts("Tortoise");
    }
    else if (h_pos > TRACK_LENGTH && t_pos <= TRACK_LENGTH)
    {
        puts("Hair");
    }
    else
    {
        puts("It's a draw!");
    }
    puts("============================");

}