#include <iostream>
#include <cstdlib>
#include "linkedlist.hh"

using namespace std;

LinkedList::LinkedList(){
    head = 0;
    curr = 0;
    temp = 0;
}

LinkedList::~LinkedList(){
    temp = head;
    nodePtr next = 0;
    
    while(temp != NULL){
        next = temp->next;
        delete temp;
        temp = next;
    }
}

void LinkedList::addToHead(int value){
    nodePtr n = new node;
    n->value = value;
    
    if(head == NULL){
        head = n;
        n->next = NULL;
    }
    else{
        n->next = head;
        head = n;
    }
}

void LinkedList::addToListAtPosition(int position,int value){
    if(position < 0){
    	return;
    }
    
    if(position == 0){
        addToHead(value);
        return;
    }
    
    nodePtr previous = 0;
    temp = head;
    for (int count = 0; count < position; count ++) {
        if(temp != NULL){
            previous = temp;
            temp = temp->next;
        }
        else{
            return;
        }
    }
    nodePtr n = new node;
    n->value = value;
    n->next = temp;
    previous->next = n;
}

void LinkedList::appendToList(int value){
    nodePtr n = new node;
    n->value = value;
    n->next = NULL;
    
    if(head != NULL){
        temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = n;
    }
    else{
        head = n;
    }
}

void LinkedList::removeFromListAtPosition(int position){
    if(position == 0){
        removeFromHead();
        return;
    }
    
    nodePtr previous = 0;
    temp = head;
    for (int count = 0; count < position; count ++) {
        if(temp != NULL){
            previous = temp;
            temp = temp->next;
        }
        else{
            return;
        }
    }
    previous->next = temp->next;
    delete temp;
}

void LinkedList::removeFromHead(){
    if(head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::removeFromEnd(){
    if(head != NULL){
        nodePtr previous = 0;
        temp = head;
        while(temp->next != NULL){
            previous = temp;
            temp = temp->next;
        }
        if(previous != NULL){
            previous->next = NULL;
        }
        else{
            head = NULL;
        }
        delete temp;
    }
}

int LinkedList::find(int value){
    temp = head;
    while(temp != NULL){
        if(temp->value == value){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void LinkedList::recursiveReverse(nodePtr n){
    nodePtr previous = NULL;
    nodePtr next;
    
    while(head){
        next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    head = previous;
}

void LinkedList::reverseList(){
    if(head != NULL){
        recursiveReverse(head);
    }
}

int LinkedList::getListLength(){
    int count = 1;
    temp = head;
    
    if(temp == NULL){
        return 0;
    }
    
    while(temp->next != NULL){
        count ++;
        temp = temp->next;
    }
    return count;
}
void LinkedList::printList(){
    if(head != NULL){
        temp = head;
        while(temp != NULL){
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

nodePtr LinkedList::getHead(){
    return head;
}