/* Marynia Demkowicz - KEY */

#include <stdio.h>
#include <stdlib.h>

#define RANGE_MAX 100000
#define PRIMES_MAX 10000
#define NUM_COLUMNS 7

#define BEGIN_FCN {
#define END_FCN }

void doTableOutput(int arrayToPrint[]);
void findCPSPs(int arrayToUse[]);
void findPalindromes(int arrayToUse[]);

int main(void)
BEGIN_FCN
	int userInput;
	char repeatChoice = 'y';

	do
	{
		printf("Please enter a number from 2 to 100,000.\n");
		scanf("%d", &userInput);
	
		if ((userInput >= 2) && (userInput <= RANGE_MAX))
		{
			int loop, innerLoop, bCounter;
			int listA[RANGE_MAX + 1] = {0};  /* +1 ensures at least one; "sentinel" zero */
			int listB[PRIMES_MAX]= {0};

			for (loop = 0; (loop + 2) <= userInput; loop++)
			{
				listA[loop] = loop + 2;
			}
			
			bCounter = 0;
			
			printf("Printing; done.\n");

			for (loop = 0; loop <= (userInput - 2); loop++)
			{
				if (listA[loop] != 0)
				{
					listB[bCounter] = listA[loop];
					for (innerLoop = loop; innerLoop <= (userInput - 2); innerLoop++)
					{
						if (listA[innerLoop] % listB[bCounter] == 0)
						{
							listA[innerLoop] = 0;
						}
					}
					bCounter++;
				}
			}

			printf("The primes between 2 and %d are:\n", userInput);
			doTableOutput(listB);
			printf("\n\nPress enter to continue.\n");
			getchar();
			getchar();
			system("cls");
			findCPSPs(listB);
			printf("\n\nPress enter to continue.\n");
			getchar();
			system("cls");
			findPalindromes(listB);
			printf("\n\nPress enter to continue.\n");
			getchar();
			system("cls");

			printf("Would you like to input another number?\n");
			scanf(" %c", &repeatChoice);
		}

	} while ((repeatChoice == 'y') || (repeatChoice == 'Y')); 

	printf("Good bye!\n");
	getchar();
	getchar();

	return 0;
END_FCN

void doTableOutput(int arrayToPrint[])
BEGIN_FCN
	int loop = 0, innerLoop = 1;

	while (arrayToPrint[loop] != 0)
	{
		if (innerLoop > NUM_COLUMNS)
		{
			innerLoop = 1;
			printf("\n");
		}
		innerLoop++;
		printf("%10d", arrayToPrint[loop]);
		loop++;
	}
END_FCN


void findCPSPs(int arrayToUse[])
BEGIN_FCN
	int loop = 0, innerLoop, primeSum, foundPrime;
	
	printf("The following CPSP-3s were found:\n");

	while (arrayToUse[loop + 2] != 0)
	{
		foundPrime = 0;
		primeSum = arrayToUse[loop] + arrayToUse[loop + 1] + arrayToUse[loop + 2];
		for (innerLoop = loop; arrayToUse[innerLoop] != 0; innerLoop++)
		{
			if (arrayToUse[innerLoop] == primeSum)
			{
				foundPrime = 1;
			}
		}
		if (foundPrime)
		{
			printf("%d + %d + %d = %d\n", arrayToUse[loop], arrayToUse[loop + 1], arrayToUse[loop + 2], primeSum);
		}
		loop++;
	}
END_FCN

void findPalindromes(int arrayToUse[])
BEGIN_FCN
	int loop = 0, temp, pal, num, palCounter;
	int palArray[PRIMES_MAX] = {0};

	palCounter = 0;

	printf("The following palindromes were found:\n");

	while (arrayToUse[loop] != 0)
	{
		num = arrayToUse[loop];
		temp = 0;
		pal = 0;
		
		while (num != 0)
		{
			temp = num % 10;
			pal = (pal * 10) + temp;
			num = num / 10;
		}

		if (pal == arrayToUse[loop])
		{
			palArray[palCounter] = pal;
			palCounter++;
		}
		loop++;
	}

	doTableOutput(palArray);
END_FCN
