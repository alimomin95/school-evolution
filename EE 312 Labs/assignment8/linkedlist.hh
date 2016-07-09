//
//  linkedlist.hh
//  assignment8xcode
//
//  Created by Ali Ziyaan Momin on 4/14/16.
//  Copyright © 2016 Ali Ziyaan Momin. All rights reserved.
//

#ifndef linkedlist_h
#define linkedlist_h

typedef struct node{
    int value;
    node* next;
}* nodePtr;

class LinkedList{

private:

    void recursiveReverse(nodePtr n);
    
    nodePtr head;
    nodePtr curr;
    nodePtr temp;

public:
    LinkedList();
    ~LinkedList();
    void addToListAtPosition(int position,int value);
    void addToHead(int value);
    void appendToList(int value);
    void removeFromListAtPosition(int position);
    void removeFromHead();
    void removeFromEnd();
    int find(int value);
    void reverseList();
    int getListLength();
    void printList();
    nodePtr getHead();
};

#endif /* linkedlist_h */
