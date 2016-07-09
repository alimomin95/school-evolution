//
//  main.cpp
//  assignment8xcode
//
//  Created by Ali Ziyaan Momin on 4/14/16.
//  Copyright © 2016 Ali Ziyaan Momin. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include "linkedlist.hh"

void test1(){
    int value = 1;
    int postion = 0;
    LinkedList l;
    l.addToListAtPosition(postion, value);
    assert(l.getListLength() == 1);
    printf("Test1 Passed!\n");
}

void test2(){
    int value = 1;
    int postion = 0;
    LinkedList l;
    l.addToListAtPosition(postion, value);
    assert(l.getListLength() == 1);
    assert(l.getHead()->value == 1);
    printf("Test2 Passed!\n");
}

void test3(){
    int value = 2;
    LinkedList l;
    l.addToHead(value);
    assert(l.getListLength() == 1);
    assert(l.getHead()->value == 2);
    printf("Test3 Passed!\n");
}

void test4(){
    LinkedList l;
    l.addToHead(1);
    l.addToHead(2);
    assert(l.getListLength() == 2);
    assert(l.getHead()->value == 2);
    assert(l.getHead()->next->value == 1);
    printf("Test4 Passed!\n");
}

void test5(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    assert(l.getListLength() == 2);
    assert(l.getHead()->value == 1);
    assert(l.getHead()->next->value == 2);
    printf("Test5 Passed!\n");
}

void test6(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    assert(l.find(1) == true);
    assert(l.find(2) == true);
    printf("Test6 Passed!\n");
}

void test7(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.removeFromListAtPosition(1);
    assert(l.getHead()->value == 1);
    assert(l.getHead()->next == 0);
    printf("Test7 Passed!\n");
}

void test8(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.removeFromListAtPosition(0);
    assert(l.getHead()->value == 2);
    assert(l.getHead()->next == 0);
    printf("Test8 Passed!\n");
}

void test9(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.removeFromHead();
    assert(l.getHead()->value == 2);
    assert(l.getHead()->next == 0);
    printf("Test9 Passed!\n");
}

void test10(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.removeFromEnd();
    assert(l.getHead()->value == 1);
    assert(l.getHead()->next == 0);
    printf("Test10 Passed!\n");
}


void test11(){
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.reverseList();
    assert(l.getHead()->value == 2);
    assert(l.getHead()->next->value == 1);
    printf("Test11 Passed!\n\n\n");
}

void test12(){
    LinkedList l;
    int limit = 9;
    for (int i = 0; i<=limit; i++) {
        l.addToHead(limit - i);
    }
    printf("List is:   ");
    l.printList();
    printf("Should be: 0 1 2 3 4 5 6 7 8 9 \n\n\n");
    
    l.addToListAtPosition(1, 0);
    l.addToListAtPosition(3, 1);
    l.addToListAtPosition(5, 2);
    l.addToListAtPosition(7, 3);
    l.addToListAtPosition(9, 4);
    l.addToListAtPosition(11, 5);
    l.addToListAtPosition(13, 6);
    l.addToListAtPosition(15, 7);
    l.addToListAtPosition(17, 8);
    l.addToListAtPosition(19, 9);
    printf("List is:   ");
    l.printList();
    printf("Should be: 0 0 1 1 2 2 3 3 4 4 5 5 6 6 7 7 8 8 9 9 \n\n\n");
    
    l.removeFromListAtPosition(19);
    l.removeFromListAtPosition(17);
    l.removeFromListAtPosition(15);
    l.removeFromListAtPosition(13);
    l.removeFromListAtPosition(11);
    l.removeFromListAtPosition(9);
    l.removeFromListAtPosition(7);
    l.removeFromListAtPosition(5);
    l.removeFromListAtPosition(3);
    l.removeFromListAtPosition(1);
    printf("List is:   ");
    l.printList();
    printf("Should be: 0 1 2 3 4 5 6 7 8 9 \n\n\n");
    
    l.reverseList();
    printf("List is:   ");
    l.printList();
    printf("Should be: 9 8 7 6 5 4 3 2 1 0\n\n\n");
    
    l.removeFromHead();
    l.removeFromEnd();
    l.removeFromHead();
    l.removeFromEnd();
    l.removeFromHead();
    l.removeFromEnd();
    l.removeFromHead();
    l.removeFromEnd();
    l.removeFromHead();
    l.removeFromEnd();
    printf("List is: \n");
    l.printList();
    printf("Should be: \n\n\n");
    
}

void myTEST1() {
    LinkedList l;
    l.addToListAtPosition(0, 0);
    assert(l.getHead()->value == 0);
    printf("myTEST1 Passed!\n");
    
}
void myTEST2() {
    LinkedList l;
    l.addToHead(38);
    assert(l.getHead()->value == 38);
    printf("myTEST2 Passed!\n");
    
}

void myTEST3() {
    LinkedList l;
    l.appendToList(77);
    assert(l.getHead()->value == 77);
    printf("myTEST3 Passed!\n");
    
}

void myTEST4() {
    LinkedList l;
    l.removeFromListAtPosition(30);
    l.removeFromListAtPosition(0);
    assert(l.getHead() == NULL);
    printf("myTEST4 Passed!\n");
    
}

void myTEST5() {
    LinkedList l;
    l.removeFromHead();
    assert(l.getHead() == NULL);
    printf("myTEST5 Passed!\n");
    
}


void myTEST6() {
    LinkedList l;
    l.removeFromEnd();
    assert(l.getHead() == NULL);
    printf("myTEST6 Passed!\n");
    
}

void myTEST7() {
    LinkedList l;
    assert(l.find(99) == false);
    printf("myTEST7 Passed!\n");
    
}

void myTEST8() {
    LinkedList l;
    l.reverseList();
    assert(l.getHead() == NULL);
    printf("myTEST8 Passed!\n");
    
}

void myTEST9() {
    LinkedList l;
    assert(l.getListLength() == 0);
    printf("myTEST9 Passed!\n");
    
}
void myTEST19() {//CHECKS IF THE ADD TO LIST IS WORKING PROPERLY,THE FIND WORKS PROPERLY, AND THE REVERSE WORKS PROPERLY
    LinkedList l;
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.addToListAtPosition(2, 3);
    l.addToListAtPosition(3, 4);
    l.addToListAtPosition(4, 5);
    l.addToListAtPosition(5, 6);
    l.reverseList();
    assert(l.getHead()->value == 6);
    assert(l.getHead()->next->value == 5);
    assert(l.find(4) == true);
    assert(l.find(0) == false);
    printf("myTEST19 Passed!\n");
    
}
void myTEST20() {			//CHECKS IF THE APPEND_TO_LIST IS WORKING PROPERLY, REVERSE_LIST DOES THE PROPER REVERSE,
    LinkedList l;			//AND FIND GETS RIGHT VALUE
    l.addToListAtPosition(0, 1);
    l.addToListAtPosition(1, 2);
    l.addToListAtPosition(2, 3);
    l.addToListAtPosition(3, 4);
    l.appendToList(5);
    l.appendToList(6);
    l.reverseList();
    assert(l.getHead()->value == 6);
    assert(l.getHead()->next->value == 5);
    assert(l.find(1) == true);
    assert(l.find(538) == false);
    printf("myTEST20 Passed!\n");
}

void myTEST13() {
    
    LinkedList l;
    int limit = 9;
    for (int i = 0; i <= limit; i++) {
        l.addToHead(limit - i);
    }
    printf("List is:   ");
    l.printList();
    printf("Should be: 0 1 2 3 4 5 6 7 8 9 \n\n\n");
    
    l.reverseList();
    printf("List is:   ");
    l.printList();
    printf("Should be: 9 8 7 6 5 4 3 2 1 0 \n\n\n");
    
    l.removeFromListAtPosition(5);
    l.removeFromListAtPosition(3);
    
    printf("List is:   ");
    l.printList();
    printf("Should be: 9 8 7 5 3 2 1 0 \n\n\n");
    
    l.reverseList();
    printf("List is:   ");
    l.printList();
    printf("Should be: 0 1 2 3 5 7 8 9 \n\n\n");
    
    l.appendToList(38);
    l.addToHead(99);
    printf("List is:   ");
    l.printList();
    printf("Should be: 99 0 1 2 3 5 7 8 9 38 \n\n\n");
    
    l.reverseList();
    printf("List is:   ");
    l.printList();
    printf("Should be: 38 9 8 7 5 3 2 1 0 99 \n\n\n");
    
    l.reverseList();
    printf("List is:   ");
    l.printList();
    printf("Should be: 99 0 1 2 3 5 7 8 9 38 \n\n\n");
    
    printf("myTEST13 Passed!\n");
    
    
    
}

int main(){
    
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    myTEST1();
    myTEST2();
    myTEST3();
    myTEST4();
    myTEST5();
    myTEST6();
    myTEST7();
    myTEST8();
    myTEST9();
    myTEST19();
    myTEST20();
    myTEST13();
    LinkedList l;
    l.addToListAtPosition(-1, 0);
    
}