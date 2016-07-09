/* 
Momin, Ali Ziyaan 
AZM259,
15975
EE312-Assignment 3
*/

#include <stdio.h>
#include <string.h>

/*
 * return 1 if the ASCII interpretation of 
 * c is an upper case letter.  
 * return 0 otherwise
 */
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1; 
	} else {
		return 0; 
	}
}

/*
 * return 1 if the ASCII interpretation of
 * c is a lower case letter.
 * return 0 otherwise
 */
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	} else {
		return 0;
	}
}

/*
 * return 1 c is an Alphabet.  
 * return 0 otherwise
 */
int isAlphabet(char c){
	return isUpperCase(c) || isLowerCase(c);
}

/*
 * if the ASCII interpretation of c is a letter, then
 * return a number between 0 and 25 indicating which letter of 
 * the alphabet c represents.  For example, if c is the ASCII
 * encoding for 'A', then we should return 0.  If c is the
 * ASCII encoding for 'e', then we should return 4.
 * if the ASCII interpretation of c is not a letter, then
 * return -1.
 */
int ASCII2Int(char c) {
	if (isUpperCase(c)) {
		return c - 'A';
	} else if (isLowerCase(c)) {
		return c - 'a';
	} else { 
		return -1;
	}
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2UpperCase(int i){
	char c = 'A'+i;
	return c;
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2LowerCase(int i){
	char c = 'a'+i;
	return c;
}

/*
* This function takes in a message and computes the frequencies of all the alphabets
*/
void buildHistogram(char message[], int messageLength, int histogram[], int histogramLength)
{
	for(int j = 0; j<histogramLength; j++)
	{
		histogram[j] = 0;
	}
	for(int i = 0; i<messageLength; i++)
	{
		if(isAlphabet(message[i]))
		{
			if(isUpperCase(message[i]))
			{
				char alpha = message[i];
				histogram[alpha - 'A'] ++;
			}
			if(isLowerCase(message[i]))
			{
				char alpha = message[i];
				histogram[alpha - 'a'] ++;
			}
		}
	}
}

/*
* This function computes the maximum value in an array and returns the index location\
* for which the maximum value occured
*/

int maxIndex(int myArray[], int arrayLength)
{
	int max = 0, index = 0;
	for (int i = 0; i < arrayLength; i++)
	{
		if(max<myArray[i])
		{
			max = myArray[i];
			index = i;
		}
	}
	return index;
}

/*
 * Encrypt the string s using the rotation cypher
 * Each letter in s should be shifted "shift" letters to the 
 * right.  For example, if "shift" is 2, then "a zebra" should be
 * changed to "c bgdtc".  Note that when shifting past the end
 * of the alphabet, we wrap around again to a.
 *
 * Only change the letters in s.  Do not change spaces, punctuation
 * or numbers in s.  
 * For full credit, you should keep upper case letters as 
 * upper case, and leave lower case letters as lower case.  So, if
 * s had been the string "a ZeBra", you should change s to be
 * "c BgDtc".
 */
void encrypt(char message[], int messageLength, int shift) 
{
	for (int i = 0; i < messageLength; i++)
	{
		char letter = message[i];
		if(isAlphabet(letter))
		{
//			letter = letter + shift;
			if(isUpperCase(letter))
			{
				message[i] = 'A' + ((letter - 'A' + shift) % 26);
				if(message[i] < 'A')
				{
					message[i] = message[i] + 26;
				}
			}
			if(isLowerCase(letter))
			{
				message[i] = 'a' + ((letter - 'a' + shift) % 26);
				if(message[i] < 'a')
				{
					message[i] = message[i] + 26;
				}
			}
		}
	}
}

/*
 * return a number between 0 and 25 indicating which letter
 * of the alphabet is most common in the string s
 */
int mostFrequentLetter(char message[], int messageLength) 
{
	int hist [26];
	buildHistogram(message, messageLength, hist, 26);
	int maxInd = hist[maxIndex(hist, 26)];
	int maxCypher = 0;
	bool foundMax = false;
	char maxCharacter = ' ';
	char string [messageLength];
	strcpy (string, message);
	for (int k = 0; k < messageLength; ++k)
	{

		if(isUpperCase(string[k]))
		{
			string[k] = string[k] + 32;
		}
		
	}
	
	for (int i = 0; i < messageLength; ++i)
	{
		if(isAlphabet(string[i]))
		{
			maxCharacter = string[i];
			maxCypher = 0;
			for (int j = 0; j < messageLength; ++j)
			{
				if(string[i] == string[j])
				{
					maxCypher ++;
				}
				if(maxInd == maxCypher)
				{
					foundMax = true;
					break;
				}
			}
			if(foundMax)
			{
				break;
			}
		}

	}
	int max = maxCharacter - 'a';
	return max;
}
/*
 * Build the histogram and get the index of most frequent alphabet
 */
void decrypt(char cypher[],int cypherLength, int common)
{
	int comindex = mostFrequentLetter(cypher, cypherLength); 
	//printf("%d\n", comindex);
	//printf("%d\n", common);
	int shift = common - comindex;
	//printf("%d\n", shift);
	encrypt(cypher, cypherLength, shift);
}

