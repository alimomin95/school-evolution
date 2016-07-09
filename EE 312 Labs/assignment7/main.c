//
//  main.c
//  assignment7xcode
//
//  Created by Ali Ziyaan Momin on 4/5/16.
//  Copyright © 2016 Ali Ziyaan Momin. All rights reserved.
//

#include <stdio.h>

void generateAllMatchedParens(int n);
void generateAllPalindromicDecompositions(char str[]);

int main(int argc, const char * argv[]) {
    //generateAllMatchedParens(6);
    //generateAllPalindromicDecompositions("a a a a ");
    
    int x;
    printf("Enter a positive integer to generate all matched Parens: \n");
    scanf("%d", &x);
    generateAllMatchedParens(x);
    
    char arr[1000];
    printf("Enter a string to generate all matched Palindromes: \n");
    scanf("%s", arr);
    generateAllPalindromicDecompositions(arr);
    
    return 0;
}
