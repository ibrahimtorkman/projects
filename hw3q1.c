/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11

/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
int check_board(int n);
int intial_board(char board[N][N], int n);
int undo_situation(char board[N][N], int indexes[2][N*N], int *pcount, int place_index1);
void turn_of_1(char board[N][N], int n, int indexes[2][N*N], int *pcount);
void turn_of_2(char board[N][N], int n, int indexes[2][N*N],int *pcount);
int check_row_winner(char board[N][N], int n);
int check_col_winner(char board[N][N], int n);
int check_slant_winner1(char board[N][N], int n);
int check_slant_winner2(char board[N][N], int n);
bool full_board_case(char board[N][N], int n);
void tie_situation(char board[N][N], int n);
int choose_winner(char board[N][N], int n);
int run_the_game(char board[N][N], int n);


int main()
{
char board[N][N];
int n=0;
print_welcome();
n=check_board(n);
board[N][N]=intial_board(board, n);
print_board(board, n);
run_the_game(board, n);
return 0;
}

//check if the board has a valid size.
//8 lines.
int check_board(int n)
{
    print_enter_board_size();
    while(1)
    {
        if(scanf("%d", &n)!=1)
            exit(0);
        if((n<2) || (n>10))
        {
            print_enter_board_size();
        }

        else break;
    }
return n;
}
//intialing the board to '_'.
//4 lines.
int intial_board(char board[N][N], int n)
{
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            board[i][j]='_';
        }
    }
    return board[N][N];
}
//when a player plays negative odd number to undo the last moves.
//9 lines.
int undo_situation(char board[N][N], int indexes[2][N*N], int *pcount, int place_index1)
{
    if((-(place_index1))>(*pcount))
        return 0;
    while(place_index1<0)
    {
        board[indexes[0][(*pcount)-1]-1][indexes[1][(*pcount)-1]-1]='_';
        indexes[0][(*pcount)-1]=0;
        indexes[1][(*pcount)-1]=0;
        (*pcount)--;
        place_index1++;
    }
return 1;
}
//turn of the first player 'X'.
//18 lines.
void turn_of_1(char board[N][N], int n, int indexes[2][N*N], int *pcount)
{
    int player_index=1, place_index1, place_index2;
    print_player_turn(player_index);
    while(1)
    {
        scanf("%d", &place_index1);
        if( (place_index1<0) && (place_index1%2==(-1)) )
        {
            if((undo_situation(board, indexes, pcount, place_index1))==1)
                print_board(board, n);
            else print_error();
            return;
        }
        scanf("%d", &place_index2);
        if(board[place_index1-1][place_index2-1]!='_')
        {
            print_error();
        }
        else
        {
            indexes[0][*pcount]=place_index1;
            indexes[1][*pcount]=place_index2;
            (*pcount)++;
            board[place_index1-1][place_index2-1]='X';
            print_board(board, n);
            break;
        }
    }
}
//turn of the second player 'O'.
//18 lines.
void turn_of_2(char board[N][N], int n, int indexes[2][N*N],int *pcount)
{
    int player_index=2, place_index1, place_index2;
    print_player_turn(player_index);
    while(1)
    {
        scanf("%d", &place_index1);
        if( (place_index1<0) && (place_index1%2==(-1)) )
        {
            if((undo_situation(board, indexes, pcount, place_index1))==1)
                print_board(board, n);
            else print_error();
            return;
        }
        scanf("%d", &place_index2);
        if(board[place_index1-1][place_index2-1]!='_')
        {
            print_error();
        }
        else
        {
            indexes[0][*pcount]=place_index1;
            indexes[1][*pcount]=place_index2;
            (*pcount)++;
            board[place_index1-1][place_index2-1]='O';
            print_board(board, n);
            break;
        }
    }
}
//check if any of the players made a row of index 'X' or 'O'.
//14 lines.
int check_row_winner(char board[N][N], int n)
{
    int count_X=0, count_O=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[i][j]=='X')
            {
                count_X++;
                if(count_X==n)
                return 1;
            }
            if(board[i][j]=='O')
            {
                count_O++;
                if(count_O==n)
                    return 2;
            }
        }
        count_X=0;
        count_O=0;
    }
return 0;
}
//check if any of the players made a column of index 'X' or 'O'.
//14 lines.
int check_col_winner(char board[N][N], int n)
{
    int count_X=0, count_O=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(board[j][i]=='X')
            {
                count_X++;
                if(count_X==n)
                    return 1;
            }
            if(board[j][i]=='O')
            {
                count_O++;
                if(count_O==n)
                    return 2;
            }
        }
        count_X=0;
        count_O=0;
    }
return 0;
}
//check if any of the players made a slant of index 'X' or 'O'.
//12 lines.
int check_slant_winner1(char board[N][N], int n)
{
    int count_X=0, count_O=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if( (i==j) && (board[i][j]=='X') )
            {
                count_X++;
            }
            if( (i==j) && (board[i][j]=='O') )
            {
                count_O++;
            }
        }
    }
    if(count_X==n)
        return 1;
    if(count_O==n)
        return 2;
return 0;
}
//check if any of the players made a slant of index 'X' or 'O'.
//12 lines.
int check_slant_winner2(char board[N][N], int n)
{
    int count_X=0, count_O=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if( (i+j==n-1) && (board[i][j]=='X') )
            {
                count_X++;
            }
            if( (i+j==n-1) && (board[i][j]=='O') )
            {
                count_O++;
            }
        }
    }
    if(count_X==n)
        return 1;
    if(count_O==n)
        return 2;
return 0;
}
//check if the board is full.
//5 lines.
bool full_board_case(char board[N][N], int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            {
            if(board[i][j]=='_')
                return false;
            }

return true;
}
//if the board is full print a tie.
//3 lines.
void tie_situation(char board[N][N], int n)
{
    if(full_board_case(board, n))
        {
        print_tie();
        exit(0);
        }
}
//choosing the winner according to the rules.
//9 lines.
int choose_winner(char board[N][N], int n)
{
    if( (check_row_winner(board, n)==2) || (check_col_winner(board, n)==2)
       || (check_slant_winner1(board, n)==2) || (check_slant_winner2(board, n)==2) )
    {
        print_winner(1);
        exit(0);
    }
    if((check_row_winner(board, n)==1) || (check_col_winner(board, n)==1)
       || (check_slant_winner1(board, n)==1) || (check_slant_winner2(board, n)==1) )
    {
        print_winner(2);
        exit(0);
    }
return 0;
}
//start the game looking for a winner.
//8 lines.
int run_the_game(char board[N][N], int n)
{
    int indexes[2][N*N]={{0},{0}}, counter=0, *pcount=&counter;
    while(1)
    {
        turn_of_1(board, n, indexes, pcount);
        choose_winner(board, n);
        tie_situation(board, n);

        turn_of_2(board, n, indexes, pcount);
        choose_winner(board, n);
        tie_situation(board, n);
    }
return 0;
}
//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}
//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}
//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}
//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}
//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}
//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}
