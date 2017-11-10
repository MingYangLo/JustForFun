#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#define MaxWords 2048
#define MaxWordLenght 64

int main()
{
    srand(time(NULL));
    char guessWords[MaxWords][MaxWordLenght];
    int WordsReadIn = 0;

/*讀取目標檔案*/
    FILE *pToFile = fopen("C:\\Users\\user\\Desktop\\germanwords.txt","r");

    if(pToFile == NULL)
    {
        printf("檔案開啟失敗\n");
        return 0;
    }

    char input[64];

    while(fgets(input, 63, pToFile))
    {
        sscanf(input, "%s", guessWords[WordsReadIn]);
        printf("Scanned: input: %s guessWords[%d]: %s\n", input, WordsReadIn, guessWords[WordsReadIn]);
        WordsReadIn++;
    }

    printf("Total words read in: %d\n\n",WordsReadIn);
    fclose(pToFile);

    int randomIndex = rand() % WordsReadIn;

	int numLives = 5;
	int numCorrect = 0;
	int oldCorrect = 0;
	int lengthOfWord = strlen(guessWords[randomIndex]);
	int letterGuessed[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int quit = 0;
	int loopIndex = 0;
	char guess[16];
	char letterEntered;

	while ( numCorrect < lengthOfWord )
    {
        for(loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
        {
            if (letterGuessed[loopIndex] == 1)
            {
                printf("%c",guessWords[randomIndex][loopIndex]);
            }
            else
            {
                printf("-");
            }
        }
        printf("\n");

        printf("生命值: %d\n", numLives);
        printf("目前猜對次數:%d\n",numCorrect);
		printf("輸入一個字母:");
		fgets(guess, 16, stdin);

		if( strncmp(guess, "quit", 4) == 0)
		{
			quit = 1;
			break;
		}

		letterEntered = guess[0];

		printf("輸入的字母:%c\n",letterEntered);

		oldCorrect = numCorrect;

		for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++)
		{

			if(letterGuessed[loopIndex] == 1)
			{
				continue;
			}

			if( letterEntered == guessWords[randomIndex][loopIndex] )
			{
				letterGuessed[loopIndex] = 1;
				numCorrect++;
			}
		}

/*猜錯、猜對之判斷*/
		if(oldCorrect == numCorrect)
        {
            numLives--;
            printf("\n猜錯了\n");

            if(numLives == 0)
            {
                printf("\n重新再試一次吧\n");
                break;
            }
        }
        else
        {
            printf("\n猜對了!\n");
        }

	}

	if( quit == 1 ) {
		printf("\n太早放棄了\n");
	}
	else if(numLives == 0)
    {
        printf("\n這個單字是: %s\n", guessWords[randomIndex]);
    }
    else
    {
        printf("\n單字猜對了!再玩一次吧\n");
    }


	return 0;
}

