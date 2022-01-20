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

/*Read file*/
    FILE *pToFile = fopen("C:\\Users\\user\\Desktop\\germanwords.txt","r");

    if(pToFile == NULL)
    {
        printf("Failed to open file!\n");
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

        printf("Life: %d\n", numLives);
        printf("Correct guessing count:%d\n",numCorrect);
		printf("Enter a character:");
		fgets(guess, 16, stdin);

		if( strncmp(guess, "quit", 4) == 0)
		{
			quit = 1;
			break;
		}

		letterEntered = guess[0];

		printf("Entered character:%c\n",letterEntered);

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

/*Determine guess right or wrong*/
		if(oldCorrect == numCorrect)
        {
            numLives--;
            printf("\nWrong Guess!\n");

            if(numLives == 0)
            {
                printf("\nTry again ;(\n");
                break;
            }
        }
        else
        {
            printf("\nScore!\n");
        }

	}

	if( quit == 1 ) {
		printf("\nDon't give up too early!!\n");
	}
	else if(numLives == 0)
    {
        printf("\nThe vocab is: %s\n", guessWords[randomIndex]);
    }
    else
    {
        printf("\nHoorrray!Let's play again!\n");
    }


	return 0;
}

