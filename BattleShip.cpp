#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

const int ROWS = 5;
const int COLS = 5;
void printBoard(char board[][COLS]);
void generateShip(char board[][COLS], int size);
void checkBoard(char board[][COLS], bool &victory);

int main(void)
{
    srand(time(NULL));
    char board[ROWS][COLS], playerBoard[ROWS][COLS];
    int sizeShip, nShips;

/*Initial board*/
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '.';
            playerBoard[i][j] = '.';
        }
    }

/*Set number of ships*/
    cout << "\nWellcome!!\n\n";
    do
    {
        cout << "Enter Numbers of YOUR Ships (<=3): ";
        cin >> nShips;
    } while (nShips < 1 || nShips > 3);

/*Set size of ships*/
    for (int i = 1; i <= nShips; i++)
    {
        do
        {
            cout << "Size of " << i << "th of YOUR ship (1~3): ";
            cin >> sizeShip;
        } while (sizeShip < 1 || sizeShip > 3);
        generateShip(board, sizeShip);
    }

/*Start Game*/
    int nBombs = 20, iGuess, jGuess;
    bool victory = false;

    if (nShips != 1)
        cout << "\nThere are " << nShips << " ships in the area.\n";
    else
        cout << "\nThere are " << nShips << " ships in the area.\n";
    cout << "Enter the row and column position to aim\n"
    << "For example, enter 1,5 for upper corner\n"
    << "\".\" be empty area\n"
    << "\"*\" be hit missile\n"
    << "\"o\" be missed missile\n"
    << "\"S\" be ship's position that was missed at the end of game"
    << "You got 20 missiles\n"
    << "Let's begin!\n\n";

/*determine the missile*/
    for (int n = 1; n <= nBombs && !victory; n++)
        {
            printBoard(playerBoard);
            cout << "\nFor the " << n << "th missile, enter the row and column position to aim: ";
            cin >> iGuess;
            cin >> jGuess;

            if (board[iGuess - 1][jGuess - 1] == 'S')
            {
                cout << "HIT!!\n";
                board[iGuess - 1][jGuess - 1] = '*';
                playerBoard[iGuess - 1][jGuess - 1] = '*';
            }
            else if (board[iGuess - 1][jGuess - 1] == '.')
            {
                cout << "Missed...\n";
                board[iGuess - 1][jGuess - 1] = 'o';
                playerBoard[iGuess - 1][jGuess - 1] = 'o';
            }
            victory = true;
        checkBoard(board, victory);
        }

/*End result*/
    cout << "\nEnd:\n";
    printBoard(board);

    if (victory)
        cout << "\nHooray! You hit all the ships!\n\n";
    else
        cout << "\nMissed some ships! Try again!\n\n";
    return 0;
}

    void printBoard(char board[][COLS])
    {
        for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLS; j++)
                {
                cout << board[i][j];
                }
                cout << endl;
            }
        return;
    }

/*Position of enemy's ships*/
void generateShip(char board[][COLS], int size)
{
    int iStart,jStart,ort;
    Randomize:
    do
    {
        iStart = rand()%ROWS;
        jStart = rand()%COLS;
        ort = rand()%2;
    } while (board[iStart][jStart] == 'S');

/*Horizon*/
    if (ort == 0)
    {
/*Make sure in grid*/
        while (jStart + size >= COLS)
            {
                jStart = rand()%COLS;
            }
/*Make sure not in repeat area*/
        for (int j = jStart; j < jStart + size; j++)
            {
                if (board[iStart][j] == 'S')
                goto Randomize;
            }
/*Place ships*/
        for (int j = jStart; j < jStart + size; j++)
            {
                        board[iStart][j] = 'S';
            }
    }
/*Verticle*/
    if (ort == 1)
    {
        while (iStart + size >= ROWS)
            {
                iStart = rand()%ROWS;
            }
        for (int i = iStart; i < iStart + size; i++)
            {
                if (board[i][jStart] == 'S')
                goto Randomize;
            }
        for (int i = iStart; i < iStart + size; i++)
            {
                board[i][jStart] = 'S';
            }
    }

    return;
}
void checkBoard(char board[][COLS], bool &victory)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 'S')
            victory = false;
        }
    }
}
