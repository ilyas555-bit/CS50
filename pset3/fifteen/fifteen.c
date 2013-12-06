/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// define underscore ASCII 
#define UNDERSCORE 95

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

// my prototypes
bool can_move();
bool move_tile();

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // for-loop to initialize the board    
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = pow(d, 2) - (d * i + j + 1);
        }
    }
    if ((int) (pow(d, 2)) % 2 == 0)
    {
        // swaps 1 and 2 if even number board
        int first = board[d - 1][d - 3];
        board[d - 1][d - 3] = board[d - 1][d - 2];
        board[d - 1][d - 2] = first;        
    }      
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // for-loop to draw the board
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if (board[i][j] < 10 && board[i][j] != 0)
            {
                // adds space before single digit numbers
                printf("%2d ", board[i][j]);
            }
            else if (board[i][j] == 0)
            {
                printf("%2c ", UNDERSCORE);
            }
            else
            {
                // print numbers
                printf("%d ", board[i][j]);
            }
        }
        printf("\n"); 
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // declaration of variables
    int i_location = 0;
    int j_location = 0; 
    int zero_i = 0;
    int zero_j = 0;
    
    // for-loop to move the tiles
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                i_location = i;
                j_location = j;            
            }
            if (board[i][j] == 0)
            {
                zero_i = i; 
                zero_j = j; 
            }    
        }
    }   
    // if-loop to swap the tiles
    return (move_tile(i_location,j_location,zero_i,zero_j)) ? true : false;
}

// boolean function to swap tiles
bool move_tile(int col, int row, int zero_col, int zero_row)
{
    if (can_move(col, row, zero_col, zero_row))
    {
        // declares swap variable
        int swap = board[col][row]; 
        board[col][row] = board[zero_col][zero_row];
        board[zero_col][zero_row] = swap;
        return true;
    }
    return false;
}

// boolean function to check if tile can move
bool can_move(int col, int row, int zero_col, int zero_row)
{
    // tile's current number
    if ((abs(col - zero_col) == 1 && abs(row - zero_row) == 0) || 
      (abs(col - zero_col) == 0 && abs(row - zero_row) == 1))
    {
        // if true, return true
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // declaration of variables
    bool check; 
    int perfect[d][d];
    
    // for-loop to make the perfect board
    for (int col = 0; col < d; col++)
    {
        for(int row = 0; row < d; row++)
        {
            perfect[col][row] = d * col + row + 1;
        }
    }
    perfect[d - 1][d - 1] = 0;
    
    // for-loop to check the perfect with users board 
    for (int col = 0; col < d; col++)
    {
        for (int row = 0; row < d; row++)
        {    
            if (board[col][row] == perfect[col][row])
            {
                check = true;                 
            }
            else
            {
                return false;
            }
        }
    }
    return check;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
	    fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
