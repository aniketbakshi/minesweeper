// Include files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Definitions
#define BOARDSIZE 11
#define TRUE 1
#define FALSE 0

// Global variables
char board[BOARDSIZE][BOARDSIZE];
char gboard[BOARDSIZE][BOARDSIZE];

// Function prototypes
void build_board();
void build_gboard();
void print_board();
void print_gboard();
int findnearbymines(int, int);
void flushoutnearbymines(int, int);
void loss();
void win();
int checkforwin();
void playagain();
void display_welcome();
void start_game();

/**********************************************
 * Main function. Handles gameplay.
 **********************************************/
int main()
{

    display_welcome();
    puts("\n");
    system("pause");/*stops display screen until any key is pressed*/
    start_game();


    return 0;
}


/* Simply prints the full board with mines when you step on it*/
void print_board()
{
    int i, j;

    // Print the first row of numbers.
    printf("    ");
    for(i = 1; i < BOARDSIZE - 1; i++)
        printf("%d ", i);
    printf("\n");

    // Print actual board w/ column numbers.
    for(i = 0; i < BOARDSIZE; i++)
    {
        if(i > 0 &&  i < BOARDSIZE - 1)
        printf("%d ", i);
        for(j = 0; j < BOARDSIZE; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}

/*********************************************
 * Prints the board used for most in-game
 * functions.
 *********************************************/
void print_gboard()
{
    int i, j;

    system("cls");
    // Print the first row of numbers.
    printf("   ");
    for(i = 1; i < BOARDSIZE - 1; i++)
        printf("%d ", i);
    printf("\n");

    // Hide the first and last rows along
    // with the first and last columns.
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    // Print the actual board w/ column numbers.
    for(i = 0; i < BOARDSIZE; i++)
    {
        if(i > 0 &&  i < BOARDSIZE - 1)
        printf("%d", i);
        for(j = 0; j < BOARDSIZE; j++)
        {
            printf("%c ", gboard[i][j]);
        }
        printf("\n");
    }
}

/**********************************************
 * Builds the board with the mines. Uses two
 * extra rows and two extra columns with no
 * mines for checks performed later.
 **********************************************/
void build_board()
{
    int i, j;

    // Set all elements in the board to '-'
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            board[i][j] = '-';

    /* Seeds srand() with time(), otherwise random function will always
      generate same sequence*/
    srand(time(NULL));

    // Place random mines (marked with '*')
    for(j = 0; j < BOARDSIZE; j++)
    {
        int r1 = rand() % (BOARDSIZE - 1) + 1;
        int r2 = rand() % (BOARDSIZE - 1) + 1;
        board[r1][r2] = '*';
        //  if(r1 == 0 || r1 == BOARDSIZE - 1 ||r2 == 0 || r2 == BOARDSIZE - 1)
          //j--;
    }

    // Make sure the first & last row, along with
    // the first and last column contain no mines.
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                board[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                board[i][j] = ' ';
}

/**********************************************
 * Builds the board for user interaction. Same
 * dimensions as the first board, just without
 * the mines. Every element will be a '-'
 * character except for the extra rows and cols.
 ************************************************/
void build_gboard()
{
    int i, j;

    // Set all elements in the board to '-'
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            gboard[i][j] = '-';


    // Make sure the first & last row, along with
    // the first and last column contain no mines.
    for(i = 0; i < BOARDSIZE; i++)
        for(j = 0; j < BOARDSIZE; j++)
            if(i == 0 || i == BOARDSIZE - 1)
                gboard[i][j] = ' ';

    for(j = 0; j < BOARDSIZE; j++)
        for(i = 0; i < BOARDSIZE; i++)
            if(j == 0 || j == BOARDSIZE - 1)
                gboard[i][j] = ' ';
}

/************************************************
 * Finds nearby mines, checks in all 8 directions.
 * Returns the number of nearby mines found.
 *************************************************/
int findnearbymines(int row, int col)
{
    int mines = 0;

    // Check up, down, left, right.
    if(board[row - 1][col] == '*')
        mines++;
    if(board[row + 1][col] == '*')
        mines++;
    if(board[row][col - 1] == '*')
        mines++;
    if(board[row][col + 1] == '*')
        mines++;

    // Check all diagonal directions
    if(board[row - 1][col + 1] == '*')
        mines++;
    if(board[row - 1][col - 1] == '*')
        mines++;
    if(board[row + 1][col + 1] == '*')
        mines++;
    if(board[row + 1][col - 1] == '*')
        mines++;

    return mines;
}

/************************************************
 * Handles a loss and asks if the user wishes
 * to play again..
 ************************************************/
void loss()
{
    char ans;

    printf("\nYou've lost the game!");
    printf("\nWould you like to play again? (y/n)--> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start_game();
    }

    else
        exit(0);
}
/************************************************
 * Handles a winning game, asks user if they
 * wish to play again..
 ************************************************/
void win()
{
    char ans;

    printf("\nYou've won the game!");
    printf("\nWould you like to play again? (y/n)--> ");
    scanf(" %c", &ans);

    if(toupper(ans) == 'Y')
    {
        system("cls");
        start_game();
    }

    else
        exit(0);
}

/*************************************************
 * Flushes out all the nearby mines. First checks
 * the current user position for nearby mines,
 * then checks in all eight directions for other
 * locations without nearby mines until it finds
 * a position with a mine touching that position.
 *
 * It updates the game board with the number of
 * mines touching that position.
 *************************************************/
void flushoutnearbymines(int row, int col)
{
    int nearbymines = 0;
    int i = 0;

        nearbymines = findnearbymines(row, col);
        gboard[row][col] = (char)(((int)'0') + nearbymines);

        nearbymines = 0;
        // Checking nearby mines going up
        while(nearbymines < 1 && i < row)
        {
            nearbymines = findnearbymines(row - i, col);
            gboard[row - i][col] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going down
        while(nearbymines < 1 && row + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row + i, col);
            gboard[row + i][col] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going left
        while(nearbymines < 1 && i < col)
        {
            nearbymines = findnearbymines(row, col - i);
            gboard[row][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going right
        while(nearbymines < 1 && col + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row, col + i);
            gboard[row][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going up-right
      /*  while(nearbymines < 1 && col + i < BOARDSIZE - 2 && i < row)
        {
            nearbymines = findnearbymines(row - i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going up-left
        while(nearbymines < 1 && i < row && i < row && i < col)
        {
            nearbymines = findnearbymines(row - i, col - i);
            gboard[row - i][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going down-right
        while(nearbymines < 1 && row + i < BOARDSIZE - 2 && col + i < BOARDSIZE - 2)
        {
            nearbymines = findnearbymines(row + i, col + i);
            gboard[row + i][col + i] = (char)(((int)'0') + nearbymines);
            i++;
        }
        i = 0;
        nearbymines = 0;
        // Checking nearby mines going down-left
        while(nearbymines < 1 && row + i < BOARDSIZE - 2 && i < col)
        {
            nearbymines = findnearbymines(row + i, col - i);
            gboard[row + i][col - i] = (char)(((int)'0') + nearbymines);
            i++;
        }*/
}
/*************************************************
 * Checks for a game that has been won. Searches
 * the entire game board for a position without a
 * mine that still has a '-' symbol indicating
 * that the user still has plays to make. If there
 * are no locations with a '-' symbol that does
 * not contain a mine at that cooresponding position,
 * the player has won.
 **************************************************/
int checkforwin()
{
    int i, j;

    for(i = 1; i < BOARDSIZE - 1; i++)
        for(j = 1; j < BOARDSIZE - 1; j++) {
            if(gboard[i][j] == '-' && board[i][j] != '*')
                return FALSE;
        }

    return TRUE;
}

/***********************************************
 * Starts the game and handles the loop to
 * either continue playing or quitting.
 ***********************************************/
void start_game()
{
    int row, col;

    // Build both game boards
    build_board();
    build_gboard();
    print_gboard();

    for(;;)
    {
        do {
        printf("Enter selection:\n");
        printf("Row--> ");
        scanf("%d", &row);
        printf("Col--> ");
        scanf("%d", &col);
        } while(row < 1 || row > BOARDSIZE - 2 || col < 1 || col > BOARDSIZE - 2);


        if(board[row][col] == '*')
        {
            printf("You hit a MINE!\n");
            print_board();
            loss();
        }
        else
            flushoutnearbymines(row, col);

        print_gboard();

        if(checkforwin() == TRUE)
            win();


        //-----------[DEBUG]----------------
        // Prints the full board with mines
        // after every turn.
        // [For debugging only]. Comment out
        // for actual gameplay.
        //----------------------------------

        // printf("\n[DEBUG]\n");
        // print_board();
    }
}

// Displays the welcome message, and the GNU License
void display_welcome()
{
    puts("-----------------------Welcome to Minesweeper!---------------------------");
    puts("By Aniket Bakshi");
    puts("\n");
}
