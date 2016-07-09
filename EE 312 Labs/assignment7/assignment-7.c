//
//  assignment-7.c
//  assignment7xcode
//
//  Created by Ali Ziyaan Momin on 4/5/16.
//  Copyright © 2016 Ali Ziyaan Momin. All rights reserved.
//
//  EE 312 F10-11am
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parens(int open, int close, char str[]);
int checkPalindrome(char string[], int low, int high);
void allPalindrome(char orig[], char new[]);

void generateAllMatchedParens(int n){
    if (n >= 0) {
        char * container = (char*)malloc((2*n)+1);
        parens(n, n, container);
        free(container);
    }
}

void parens(int open, int close, char str[]){
    if(open == 0 && close ==0){
        printf("%s\n", str);
        return;
    }
    if(open > 0){
        char * copy = (char*)malloc(strlen(str)+1);
        strcpy(copy, str);
        strcat(copy, "(");
        parens(open-1, close, copy);
        free(copy);
    }
    if(open < close){
        char * temp = (char*)malloc(strlen(str)+1);
        strcpy(temp, str);
        strcat(temp, ")");
        parens(open, close-1, temp);
        free(temp);
    }
}

void generateAllPalindromicDecompositions(char str[]){
    char new[] = {0};
    allPalindrome(str, new);
}

void allPalindrome(char orig[], char new[]){
    if(*orig == '\0'){
        printf("%s\n", new);
        return;
    }
    for(int i =0; i<strlen(orig);i++){
        if(checkPalindrome(orig,0, i))
           {
               char * n = (char*)calloc(strlen(new)+strlen(orig)+1, 1);
               char * o = (char*)calloc(strlen(orig), 1);
               strcpy(o, (orig+i+1));
               strcpy(n, new);
               long size = strlen(n);
               for (int j = 0; j<=i; j++) {
                   n[size + j] = orig[j];
               }
               strcat(n, " ");
               allPalindrome(o, n);
               free(n);
               free(o);
           }
    }
}

int checkPalindrome(char string[], int low, int high){
    for(int i = low; i<high; i ++){
        if(string[i] != string[high - i]){
            return 0;
        }
    }
    return 1;
}