#include<stdio.h>
#include<string.h>

#define BEGIN_FCN {
#define END_FCN }
#define MAX_LINE_LENGTH 200
#define FUNC_START 1
#define FUNC_END 2
#define FUNC_BODY 3
#define OUT_OF_FUNC 4
#define MAX_TABLE_SIZE 10


void slocCount(char sourcefileName[]);
int detectFunction(const char fileLine[]);
void extractFunctionName(char sFuncName[MAX_LINE_LENGTH]);
int readSource(char fileLine[],FILE *fp);
void countLOC(char fLine[],int *semiColonCount);
void checkQuotes(char fileLine[]);
void checkComments(char fileLine[],int *inCom);
void printTable(char sFileName[],char funcName[MAX_TABLE_SIZE][MAX_LINE_LENGTH],int *lineCount,int noOfEntries,FILE *out);
/*******************************************************************
* NAME :            void main(void)
*
* DESCRIPTION :     Main function
*
* INPUTS :
*       Nil
* OUTPUTS :
*       Nil
* PROCESS :
*                   [1]  Asks the user for file name
*                   [2]  Calls the SLOC function
*                   [3]  Repeats until user terminates
*******************************************************************/
int main(void)
BEGIN_FCN
	char fileName[20],userOption;
	int validOption;
	do
	{
		printf("\nEnter the name of the source file:");
		fflush(stdin);
		scanf("%s",fileName);
		slocCount(fileName);
		do
		{
			validOption=1;
			printf("Do you want to continue:(y or n)");
			fflush(stdin);
			scanf("%c",&userOption);
			if(userOption == 'N' || userOption == 'n')
			{
				printf("\nGood Bye!!\n");
				getchar();
				return 0;
			}
			else if(userOption == 'Y' ||userOption == 'y' )
			{
				validOption=1;
			}
			else
			{
				printf("\nInvalid Option\n");
				validOption=0;
			}
		}while(!validOption);
	}while(1);

END_FCN
/*******************************************************************
* NAME :            void slocCount(char sourceFileName[])
*
* DESCRIPTION :     slocCount is an independent sub-module that calculates SLOC given the file name
*
* INPUTS :
*       PARAMETERS:
*           char	sourceFileName			Source code file name in string format
*       PREPROCESSORS :
*					MAX_LINE_LENGTH			Function processes source code line by line, MAX_LINE_LENGTH defines the line buffer size
*					FUNC_START				Used as a flag to mark the start of a function
*					FUNC_END				Used as a flag to mark the end of a function
*					FUNC_BODY				Used as a flag to indicate the body of a function
*					OUT_OF_FUNC				Used as a flag to indicate the SLOC is a processing lines outside the function
*					MAX_TABLE_SIZE			Maximum number of functions that can be processed
* OUTPUTS :
*       PARAMETERS:
*           Nil
* PROCESS :
*                   [1]  Opens the source file
*                   [2]  Processes source code line by line
*                   [3]  Neglects comments, preprocessors, and string literals
*                   [4]  Updates the source code summary as it encounters semicolons,"END_FCN" and "BEGIN_FCN"
*                   [5]  Repeats until EOF
*	PRE CONDITIONS:
*					#define BEGIN_FCN {  and
*					#define END_FCN } should be used for marking begin and end of functions instead of braces
*******************************************************************/
void slocCount(char sourceFileName[])
BEGIN_FCN
	char line[MAX_LINE_LENGTH],prevLine[MAX_LINE_LENGTH],*linePointer,lineLength,funcName[MAX_TABLE_SIZE][MAX_LINE_LENGTH],hashCheck[2];
	int triggerEOFFlag,funcCount,funcFlag,funcStatus,funcLineCount[10],insideComments=0;
	FILE *sourceFilePointer,*out;

	funcCount=0;
	insideComments=0;
	funcStatus=OUT_OF_FUNC;
	sourceFilePointer = fopen(sourceFileName,"r");
	out = fopen("output.txt","w");
	if(out == NULL)
	{
		printf("\a\nException: Output File cannot be opened\n");	
		return;
	}
	if(sourceFilePointer == NULL )
	{
		printf("\a\nException: Source File cannot be opened\n");
		fprintf(out,"\a\nException: Source File cannot be opened\n");
		return;
	}
	

	triggerEOFFlag=0;
	while(1)
	{
		if(!readSource(line,sourceFilePointer))
			triggerEOFFlag=1;				/*Stops the loop when the source line contains EOF*/

		/*Checking for preprocessor directives*/
		sscanf(line,"%1s",hashCheck);		/*preprocessor command must start as first nonwhite space*/
		if(strstr(hashCheck,"#"))
			continue;						/*Neglect preprocessor directives*/

		checkQuotes(line);					/*Zero the string literals in a line*/

		checkComments(line,&insideComments);/*Zero the comments*/
		/*printf("\nSuccessful read: %s\n",line);*/

		/*Detect the functions and function names*/
		funcFlag=detectFunction(line);
		if(funcFlag==1)
		{
			if(funcStatus==FUNC_BODY)
			{
				printf("\a\nException: Unmatched begin and end of function\n");
				fprintf(out,"\a\nException: Unmatched begin and end of function\n");
				fclose(sourceFilePointer);
				return;
			}
			funcStatus=FUNC_START;
		}
		else if(funcFlag==-1)
		{
			if(funcStatus==OUT_OF_FUNC)
			{
				printf("\a\nException: Unmatched begin and end of function\n");
				fprintf(out,"\a\nException: Unmatched begin and end of function\n");
				fclose(sourceFilePointer);
				return;
			}
			funcStatus=FUNC_END;
		}
		switch(funcStatus)
		{
		case FUNC_START:
			extractFunctionName(prevLine);
			strcpy(funcName[funcCount],prevLine);
			funcLineCount[funcCount]=0;				/*make the line count for the function zero*/
			funcStatus=FUNC_BODY;
			break;
		case FUNC_END:
			funcStatus=OUT_OF_FUNC;
			funcCount++;
			break;
		case FUNC_BODY:
			countLOC(line,&funcLineCount[funcCount]);
			break;
		case OUT_OF_FUNC:
			break;
		}

		strcpy(prevLine,line);
		if(triggerEOFFlag==1)
		{
			if(funcStatus==FUNC_BODY)
			{
				printf("\a\nException: Unmatched begin and end of function\n");
				fprintf(out,"\a\nException: Unmatched begin and end of function\n");
				fclose(sourceFilePointer);
				return;
			}
			break;
		}
	}

	printTable(sourceFileName,funcName,funcLineCount,funcCount,out);
	fclose(sourceFilePointer);
	fclose(out);
	return;
END_FCN
/*******************************************************************
* NAME :            signed int detectFunction(const char fileLine[])
*
* DESCRIPTION :     Checks the occurrence of "BEGIN_FCN" and "END_FCN" in the given line
*
* INPUTS :
*       PARAMETERS:
*           const char	fileLine[]  Line to be processed
*       GLOBALS :
*           nil
*       PREPROCESSORS :
*			MAX_LINE_LENGTH			Function processes source code line by line, MAX_LINE_LENGTH defines the line buffer size
* OUTPUTS :
*       PARAMETERS:
*			Nil
*       GLOBALS :
*           Nil
*       RETURN :
*			Type:	signed int						-1	if it encounters end of function
*													1	if it encounters beginning of function
*													0	None of the above
* PROCESS :
*                   [1]  Checks the occurrence of "BEGIN_FCN","END_FCN" using branching statement
*	PRE CONDITIONS:
*					strings "#define BEGIN_FCN {"  and
*					"#define END_FCN }" should not be passed to this function
*******************************************************************/
signed int detectFunction		(const char fileLine[])
BEGIN_FCN
	if(strstr(fileLine,"BEGIN_FCN"))
		return 1;
	else if(strstr(fileLine,"END_FCN"))
		return -1;
	else 
		return 0;
END_FCN
/*******************************************************************
* NAME :            void extractFunctionName(char sFuncName[MAX_LINE_LENGTH])
*
* DESCRIPTION :     Extracts the function name given the first line of a function definition
*
* INPUTS :
*       PARAMETERS:
*           char	sFuncName[MAX_LINE_LENGTH]              Line to be processed
*       GLOBALS :
*           nil
*       PREPROCESSORS :
*					MAX_LINE_LENGTH							defines the line buffer size
* OUTPUTS :
*       PARAMETERS:
*			char	sFuncName[MAX_LINE_LENGTH]              Name of the function
*       GLOBALS :
*           Nil
*       RETURN :
*			Nil
* PROCESS :
*                   [1]  Truncate the line before the occurrence of '('.
*					[2]  Delete any spaces or tabs at the end of the line. For instance "signed int detectFunction  "
*						 would become "signed int detectFunction".
*					[3]  Delete the return type fields and retrieve the last word in the line
*						 which would be "detectFunction" in our example.
*					[4]  The retrieved function name is passed back using the sFuncName, input parameter of the function.
*PRE CONDITIONS:
*					The line passed must be a valid function definition with '(' at the end of the function name with 
*					or without any spaces between them
*******************************************************************/
void extractFunctionName(char sFuncName[MAX_LINE_LENGTH])
BEGIN_FCN
	char tempString1[MAX_LINE_LENGTH];

	sscanf(sFuncName,"%[^(]s",sFuncName);

	/* delete white space characters and tabs if any at the end*/
	while(sFuncName[strlen(sFuncName)-1]==' '||sFuncName[strlen(sFuncName)-1]=='\t')
	{
		sFuncName[strlen(sFuncName)-1]='\0';
	}
	/* retrieve the last word*/
	while((sscanf(sFuncName,"%s %[^\0]s",tempString1,sFuncName))==2)
	{
	}

	return;
END_FCN
/*******************************************************************
* NAME :            int readSource(char fileLine[],FILE *fp)
*
* DESCRIPTION :     Pulls out lines as strings from a file and checks for EOF
*
* INPUTS :
*       PARAMETERS:
*			char	fileLine[]             Pointer to the line returned
*			FILE	*fp						Pointer to the source code file
*       GLOBALS :
*           Nil
* OUTPUTS :
*       PARAMETERS:
*           char    * pKbdBuf               -> buffer for keyboard chars
*       GLOBALS :
*            None
*       RETURN :
*            Type:   int                   
*            Values: greater than 0			for valid lines
*					0						for EOF
* PROCESS :
*                   [1]  Retrieves a line
*                   [2]  Flushes the newline character
*                   [3]  Checks the EOF
*******************************************************************/
int readSource(char fileLine[],FILE *fp)
BEGIN_FCN
	if(!fgets(fileLine,MAX_LINE_LENGTH,fp))
		strcpy(fileLine,"");

	if(!feof(fp))
		return strlen(fileLine);
	else
		return 0;
END_FCN
/*******************************************************************
* NAME :            void countLOC(char fLine[],int *semiColonCount)
*
* DESCRIPTION :     Adds up the number of semicolons in the given line
*
* INPUTS :
*       PARAMETERS:
*           int		*semiColonCount        Pointer to the variable which saves the lines of code
*			char	fLine[]					Line to be processed without any comments,string literal and hashes
*       GLOBALS :	
*           Nil
*		OUTPUTS :
*			Nil
* PROCESS :
*                   [1]  Search for semicolons
*                   [2]  Increment semiColonCount
*                   [3]  Zero the semicolon found and repeat the process
*	PRE CONDITIONS:
*					Contents inside comments and
*******************************************************************/
void countLOC(char fLine[],int *semiColonCount)
BEGIN_FCN
	char *semiColonPointer;
	while(semiColonPointer==strstr(fLine,";"))
	{
		(*semiColonCount)++;
		*semiColonPointer='0';
	}
	return;
END_FCN
/*******************************************************************
* NAME :			void printTable(char sFileName[],char funcName[MAX_TABLE_SIZE][MAX_LINE_LENGTH],int *lineCount,int noOfEntries)
*
* DESCRIPTION :     Prints the summary of SLOC
*
* INPUTS :
*       PARAMETERS:
*           char	sFileName[]             Source file name
*			char	funcName[MAX_TABLE_SIZE][MAX_LINE_LENGTH]	array of function names
*			int		*lineCount				Line count for the functions as an array
*			int		noOfEntries				size of the table
*       GLOBALS :
			Nil
*       PREPROCESSORS :
*			MAX_LINE_LENGTH			Function processes source code line by line, MAX_LINE_LENGTH defines the line buffer size
*			FUNC_START				Used as a flag to mark the start of a function
*			MAX_TABLE_SIZE			Maximum number of functions that can be processed
*	OUTPUTS :
*       PARAMETERS:
*           Nil
*       GLOBALS :
*			Nil
*       RETURN :
*           Nil
*******************************************************************/
void printTable(char sFileName[],char funcName[MAX_TABLE_SIZE][MAX_LINE_LENGTH],int *lineCount,int noOfEntries,FILE *out)
BEGIN_FCN
	int i,j,totalLines=0;
	if(!noOfEntries)
	{
		printf("\a\nException: No functions found in the file\n");
		fprintf(out,"\a\nException: No functions found in the file\n");
	}
	printf("\n/*-------File Counting Summary Table-------\n\n");
	fprintf(out,"\n-------File Counting Summary Table-------\n\n");
	printf("Filename:%s\n",sFileName);
	fprintf(out,"Filename:%s\n",sFileName);
	printf("\n%-20s%s\n\n","Function Name" ,"# Lines of Code");
	fprintf(out,"\n%-20s%s\n\n","Function Name" ,"# Lines of Code");
	for(i=0;i<noOfEntries;i++)
	{
		printf("%-20s%10d\n",funcName[i],lineCount[i]);
		fprintf(out,"%-20s%10d\n",funcName[i],lineCount[i]);
		totalLines=totalLines+lineCount[i];
	}
	printf("\nTotal Functions:%d\n",noOfEntries);
	fprintf(out,"\nTotal Functions:%d\n",noOfEntries);
	printf("Total Lines of Code:%d\n\n",totalLines);
	fprintf(out,"Total Lines of Code:%d\n\n",totalLines);
	return;
END_FCN
/*******************************************************************
* NAME :            void checkComments(char fileLine[],int *inCom)
*
* DESCRIPTION :     Zeroes the contents inside the comments of a given 
*					line to avoid confusion during execution of countLOC,detectFunction.
*
* INPUTS :
*       PARAMETERS:
*			char	fLine[]					Line to be processed without any comments,string literal and hashes
*			int		*inCom					It records the previous occurrence of start of comments symbol
*											It is one if the lines supplied are inside comments
*											else it is zero
*       GLOBALS :
*			Nil
* OUTPUTS :
*       PARAMETERS:
*           Nil
*       GLOBALS :
*            Nil
*       RETURN :
*            Nil
* PROCESS :
*                   [1]  Scan character by character and Zero the characters inside comments 
*                   [2]  Record the end of comments and start of comments in *inCom
*******************************************************************/

void checkComments(char fileLine[],int *inCom)
BEGIN_FCN
	int i;
	
	for(i=0;fileLine[i+1]!='\0';i++)
	{
		if (*inCom)
		{
			if(fileLine[i]=='*'&&fileLine[i+1]=='/')
			{
				*inCom=0;
			}
			else
				fileLine[i]='0';
		}
		else
		{
			if(fileLine[i]=='/'&&fileLine[i+1]=='*')
			{
				*inCom=1;
				i++;
			}
		}
	}
	return;
END_FCN
/*******************************************************************
* NAME :            void checkQuotes(char fileLine[],int *inQuo)
*
* DESCRIPTION :     Zeroes the contents inside the quotes of a given 
*					line to avoid confusion during execution of countLOC,detectFunction.
*
* INPUTS :
*       PARAMETERS:
*			char	fLine[]					Line to be processed without any comments,string literal and hashes
*			int		*inQuo					It records the previous occurrence of start of quotes
*											It is one if the lines supplied are inside quotes
*											else it is zero
*       GLOBALS :
*			Nil
* OUTPUTS :
*       PARAMETERS:
*           Nil
*       GLOBALS :
*            Nil
*       RETURN :
*            Nil
* PROCESS :
*                   [1]  Scan character by character and Zero the characters inside quotes
*                   [2]  Record the end of quotes and start of quotes in *inQuo
*******************************************************************/

void checkQuotes(char fileLine[])
BEGIN_FCN
	int i,inQuo=0;
	for(i=0;fileLine[i]!='\0';i++)
	{
		if(fileLine[i]=='\\')
		{
			fileLine[i]='0';		/*Neglecting escape sequence characters*/
			fileLine[i+1]='0';
		}
		if (inQuo)
		{
			if(fileLine[i]=='\"')
			{
					inQuo=0;
			}
			else
			{
				fileLine[i]='0';
			}
		}
		else
		{
			if(fileLine[i]=='\"')
			{
				inQuo=1;
			}
		}
	}
	return;
END_FCN
