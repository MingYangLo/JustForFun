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

/*初始化方格*/
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '.';
            playerBoard[i][j] = '.';
        }
    }

/*設定敵方戰艦數量*/
    cout << "\n歡迎來到戰艦攻防戰遊戲\n\n";
    do
    {
        cout << "輸入你想要的敵方戰艦數量(不可大於3): ";
        cin >> nShips;
    } while (nShips < 1 || nShips > 3);

/*設定敵方戰艦大小*/
    for (int i = 1; i <= nShips; i++)
    {
        do
        {
            cout << "敵方第 " << i << " 號戰艦大小(輸入1到3): ";
            cin >> sizeShip;
        } while (sizeShip < 1 || sizeShip > 3);
        generateShip(board, sizeShip);
    }

/*遊戲進行*/
    int nBombs = 20, iGuess, jGuess;
    bool victory = false;

    if (nShips != 1)
        cout << "\n有 " << nShips << "艘戰艦藏在下面海域中\n";
    else
        cout << "\n有 " << nShips << "艘戰艦藏在下面海域中\n";
    cout << "輸入砲彈放置位置之橫軸及縱軸\n"
    << "例如:你想放一顆炸彈在右上角，就請輸入1,5\n"
    << "\".\" 為可空及海域\n"
    << "\"*\" 為擊中之砲彈\n"
    << "\"o\" 是未擊中之砲彈\n"
    << "\"S\" 為結束時顯示沒擊中之戰艦位置"
    << "你有20顆砲彈\n"
    << "遊戲開始!\n\n";

/*審核遊戲中之砲彈*/
    for (int n = 1; n <= nBombs && !victory; n++)
        {
            printBoard(playerBoard);
            cout << "\n第 " << n << "顆砲彈, 輸入放置位置之橫軸及縱軸: ";
            cin >> iGuess;
            cin >> jGuess;

            if (board[iGuess - 1][jGuess - 1] == 'S')
            {
                cout << "擊中了\n";
                board[iGuess - 1][jGuess - 1] = '*';
                playerBoard[iGuess - 1][jGuess - 1] = '*';
            }
            else if (board[iGuess - 1][jGuess - 1] == '.')
            {
                cout << "擊錯了\n";
                board[iGuess - 1][jGuess - 1] = 'o';
                playerBoard[iGuess - 1][jGuess - 1] = 'o';
            }
            victory = true;
        checkBoard(board, victory);
        }

/*結果呈現*/
    cout << "\n終盤:\n";
    printBoard(board);

    if (victory)
        cout << "\n恭喜!你擊沉了所有戰艦!\n\n";
    else
        cout << "\n你沒有擊沉所有戰艦!再試一次!\n\n";
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

/*敵方戰艦擺放*/
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

/*水平擺放*/
    if (ort == 0)
    {
/*確保戰艦不會超出海域*/
        while (jStart + size >= COLS)
            {
                jStart = rand()%COLS;
            }
/*確保戰艦不重疊*/
        for (int j = jStart; j < jStart + size; j++)
            {
                if (board[iStart][j] == 'S')
                goto Randomize;
            }
/*如滿足上述條件，執行放置戰艦*/
        for (int j = jStart; j < jStart + size; j++)
            {
                        board[iStart][j] = 'S';
            }
    }
/*垂直擺放*/
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
