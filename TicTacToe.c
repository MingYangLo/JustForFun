#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Broad position setting:

	:,:,:,:,:,
	:,O,O,O,:,
	:,O,O,O,:,
	:,O,O,O,:,
	:,:,:,:,:,

	 0, 1, 2, 3, 4,
	 5, 6, 7, 8, 9,
	10,11,12,13,14,
	15,16,17,18,19,
	20,21,22,23,24
*/

enum { Noughts, Crosses, Border, Empty };
enum { HumanWins, CompWins, Draw };

const int Directions[4] = { 1, 5, 4, 6 };

const int ConvertToMiddle[9] =
{
	6, 7, 8,
	11,12,13,
	16,17,18
};

const int InMiddle = 4;
const int Corners[4] = { 0, 2, 6, 8 };

int Steps = 0;
int positions = 0;
int MaxSteps = 0;

int GetNumForDir(int startSq, const int dir, const int *board, const int us)
{
	int found = 0;
	while(board[startSq] != Border)
        {
            if(board[startSq] != us)
            {
                break;
            }
            found++;
            startSq += dir;
        }
	return found;
}

int FindThreeInARow(const int *board, const int ourindex, const int us)
{

	int DirIndex = 0;
	int Dir = 0;
	int threeCount = 1;

	for(DirIndex = 0; DirIndex < 4; ++DirIndex)
        {
            Dir = Directions[DirIndex];
            threeCount += GetNumForDir(ourindex + Dir, Dir, board, us);
            threeCount += GetNumForDir(ourindex + Dir * -1, Dir * -1, board, us);

            if(threeCount == 3)
            {
                break;
            }
            threeCount = 1;
        }
	return threeCount;
}

int FindAllBoard(const int *board, const int us)
{
	int threeFound = 0;
	int index;
	for(index = 0; index < 9; ++index)
        {
            if(board[ConvertToMiddle[index]] == us)
            {
                if(FindThreeInARow(board, ConvertToMiddle[index], us) == 3)
                {
                    threeFound = 1;
                    break;
                }
            }
        }
	return threeFound;
}

int WinOrLoss(const int *board, const int us)
{

	if(FindAllBoard(board, us) != 0)
		return 1;
	if(FindAllBoard(board, us ^ 1) != 0)
		return -1;

	return 0;
}

int MiniMax(int *board, int other) {

	/*
	Check status and Aim to get best result 
	*/
	int MoveList[9];
	int MoveCount = 0;
	int bestScore = -2;
	int Score = -2;
	int bestMove = -1;
	int Move;
	int index;

	if(Steps > MaxSteps) MaxSteps = Steps;
	positions++;

	if(Steps > 0)
        {
            Score = WinOrLoss(board, other);
            if(Score != 0)
            {
                return Score;
            }
        }


	for(index = 0; index < 9; ++index)
        {
            if( board[ConvertToMiddle[index]] == Empty)
            {
                MoveList[MoveCount++] = ConvertToMiddle[index];
            }
        }


	for(index = 0; index < MoveCount; ++index)
        {
            Move = MoveList[index];
            board[Move] = other;

            Steps++;
            Score = -MiniMax(board, other^1);
            if(Score > bestScore)
                {
                    bestScore = Score;
                    bestMove = Move;
                }
            board[Move] = Empty;
		Steps--;
	 }

        if(MoveCount==0)
            {
                bestScore = FindAllBoard(board, other);
            }

	if(Steps!=0)
		return bestScore;
	else
		return bestMove;
}

void StartBoard(int *board)
{
	int index = 0;

	for(index = 0; index < 25; ++index)
        {
            board[index] = Border;
        }

	for(index = 0; index < 9; ++index)
        {
            board[ConvertToMiddle[index]] = Empty;
        }
}

void PrintBoard(const int *board)
{
	int index = 0;
	char pceChars[] = "OX|-";

	printf("\n\nGame Broad:\n\n");
	for(index = 0; index < 9; ++index)
        {
            if(index!=0 && index%3==0)
            {
                printf("\n\n");
            }
            printf("%4c",pceChars[board[ConvertToMiddle[index]]]);
        }
	printf("\n");
}

int HasEmpty(const int *board)
{
	int index = 0;

	for(index = 0; index < 9; ++index)
        {
            if( board[ConvertToMiddle[index]] == Empty) return 1;
        }
	return 0;
}

void MakeMove(int *board, const int sq, const side)
{
	board[sq] = side;
}

int GetNextBest(const int *board)
{

	int ourMove = ConvertToMiddle[InMiddle];
	if(board[ourMove] == Empty)
        {
            return ourMove;
        }

	int index = 0;
	ourMove = -1;

	for(index = 0; index < 4; index++)
        {
            ourMove = ConvertToMiddle[Corners[index]];
            if(board[ourMove] == Empty) {
			break;
		}
		ourMove = -1;
	}

	return ourMove;
}

int GetWinningMove(int *board, const int side)
{

	int ourMove = -1;
	int winFound = 0;
	int index = 0;

	for(index = 0; index < 9; ++index)
        {
            if( board[ConvertToMiddle[index]] == Empty)
            {
                ourMove = ConvertToMiddle[index];
                board[ourMove] = side;

                if(FindThreeInARow(board, ourMove, side) == 3)
                    {
                        winFound = 1;
                    }
                board[ourMove] = Empty;
                if(winFound == 1)
                    {
                        break;
                    }
                ourMove = -1;
            };
        }
	return ourMove;
}

int LetComputerMove(int *board, const int side)
{

	Steps=0;
	positions=0;
	MaxSteps=0;
	int best = MiniMax(board, side);
	printf("All posibility:%d Maxsteps:%d ",positions,MaxSteps);
	if(0<best&&best<9)
        printf("Best step: %d\n",best-5);
    else if (9<best&&best<14)
        printf("Best step: %d\n",best-7);
    else
        printf("Best step: %d\n",best-9);
	return best;

}

int LetHumanMove(const int *board)
{

	char userInput[4];

	int moveOk = 0;
	int move = -1;

	while (moveOk == 0)
        {

            printf("Enter Number 1 to 9:");
            fgets(userInput, 3, stdin);
            fflush(stdin);

            if(strlen(userInput) != 2)
                {
                    printf("Enter Number 1 to 9\n");
                continue;
                }

            if( sscanf(userInput, "%d", &move) != 1)
                {
                    move = -1;
                    printf("Enter Number 1 to 9\n");
                    continue;
                }

            if( move < 1 || move > 9)
                {
                    move = -1;
                    printf("Enter Number 1 to 9\n");
                    continue;
                }

            move--; // Zero indexing

            if( board[ConvertToMiddle[move]]!=Empty)
                {
                    move=-1;
                    printf("Repeated entering\n");
                    continue;
                }
            moveOk = 1;
        }
	printf("Proceeding...%d\n",(move+1));
	return ConvertToMiddle[move];
}

void RunGame()
{

	int GameOver = 0;
	int Side = Noughts;
	int LastMove = 0;
	int board[25];

	StartBoard(&board[0]);
	PrintBoard(&board[0]);

	while(!GameOver)
        {
            if(Side==Noughts)
            {
                LastMove = LetHumanMove(&board[0]);
                MakeMove(&board[0],LastMove,Side);
                Side=Crosses;
            } else
            {
                LastMove = LetComputerMove(&board[0], Side);
                MakeMove(&board[0],LastMove,Side);
                Side=Noughts;
                PrintBoard(&board[0]);
            }

		if( FindThreeInARow(board, LastMove, Side ^ 1) == 3)
            {
                printf("End of Game!\n");
                GameOver = 1;
                if(Side==Noughts)
                {
                    printf("Bot wins!\n");
                } else
                {
                    printf("You win!\n");
                }
            }

/*如不能再進行動作即是平手*/
		if(!HasEmpty(board))
            {
                printf("End of Game!\n");
                GameOver = 1;
                printf("Tie!\n");
            }
	}


	PrintBoard(&board[0]);
}

int main()
{

	srand(time(NULL));
	RunGame();

	return 0;
}
