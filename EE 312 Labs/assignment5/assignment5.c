/*
 * Ali Ziyaan Momin
 * AZM259
 * assignment5.c
 * SpellCheck
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <stdlib.h>
#include <string.h>

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I strongly encourage you to avoid big functions
 * (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

//TODO:
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
 *return index to next word in message
 *return -1 otherwise
 */
int getFirstPtWord(char message[], int idx){
    int count = 0;
    for (int i = idx; message[i] != '\0'; ++i){
        if (isAlphabet(message[i])){
            count ++;
            if (isAlphabet(message[i+1])){
                count ++;
                if (count >= 2) {
                    return i;
                }
                count = 0;
            }
        }
        //idx ++;
    }
    if (count >= 2){
        if (isAlphabet(message[idx])){
            return idx;
        }
    }
    return -1;
}

int getSecondPtWord(char message[], int idx){
    while(isAlphabet(message[idx + 1])){
        idx++;
    }
    return idx;
}
/*
int getFirstPtDic(char dictionary[], int idx){
    while (dictionary[idx] == '\n') {
        idx ++;
    }
    return idx;
}
*/
int getSecondPtDic(char dictionary[], int idx){
    while (dictionary[idx+1] != '\n') {
        idx ++;
    }
    return idx;
}
//gets pointer to the next word in article
int findNextWord(char message[], int pt){
    while (isAlphabet(message[pt])) {
        pt++;
    }
    return pt;
}

/*
 *return 1 if match found
 *return 0 if no match found
 */
int checkDic (char article[], char dictionary[], int fPt, int sPt, int fPtd, int sPtd){
    int diffArticle = sPt - fPt;
    int diffDictionary = sPtd - fPtd;
    if (diffArticle != diffDictionary) {
        return 1;
    }
    while ((fPt <= sPt) && (fPtd <= sPtd)) {
        char a = article[fPt];
        if (isUpperCase(a)) {
            a = a + 32;
        }
        char d = dictionary[fPtd];
        if (isUpperCase(d)) {
            d = d + 32;
        }
        if (a == d) {
            fPt ++;
            fPtd ++;
        }
        else{
            return 1;
        }
    }
    return 0;
}

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I strongly encourage you to avoid big functions
 * (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

//TODO:

void spellCheck(char article[], char dictionary[]) {
    int fPt = 0, sPt = 0, fPtd = 0, sPtd = 0, result = 1;
    
    while (article[fPt] != '\0') {
        fPt = getFirstPtWord(article, fPt);
        if (fPt == -1) {
            return;
        }
        sPt = getSecondPtWord(article, fPt);
        result = 1;
        fPtd = 0;
        while (result) {
            sPtd = getSecondPtDic(dictionary, fPtd);
            result = checkDic(article, dictionary, fPt, sPt, fPtd, sPtd);
            fPtd = sPtd +2;
            if (dictionary[fPtd] == '\0') {
                break;
            }
        }
        if (result) {
            int temp1 = fPt, temp2 = sPt;
            while (temp1 <= temp2) {
                printf("%c", article[temp1]);
                temp1 ++;
            }
            printf("\n");
        }
        fPt = findNextWord(article, fPt);
    }
}


