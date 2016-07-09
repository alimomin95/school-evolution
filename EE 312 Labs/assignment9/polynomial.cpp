#include "polynomial.hh"
#include <stdio.h>

Node::Node(){
    value = 0;
    next = 0;
}

Node::Node(double v, Node* n){
    value = v;
    next = n;
}

Node* Poly::getHead(){
	return head;
}

Poly::Poly(){
    head = 0;
    temp = 0;
}

void Poly::append(double v){
    Node* n = new Node;
    n->value = v;
    n->next = NULL;
    
    if(head != NULL){
        Node* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = n;
    }
    else{
        head = n;
    }
}

void Poly::removeFromHead(){
    if(head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
}

int Poly::getListLength(){
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

void Poly::print(){
	Node* temp = getHead();
	while(temp!=0){
		printf("%.2f", temp->value);
		temp = temp->next;
	}
}

Poly::~Poly(){
    clear();
}

void Poly::clear(){
    Node* temp = head;
    while(temp!=0){
        Node* n = temp->next;
        delete temp;
        temp = n;
    }
}

Poly::Poly(const Poly& obj){
    Node* temp = obj.head;
    //clear();
    head = 0;
    while(temp != 0){
        append(temp->value);
        temp = temp->next;
    }
}

Poly& Poly::operator=(const Poly& obj){
    Node* temp = obj.head;
    clear();
    head = 0;
    while(temp != 0){
        append(temp->value);
        temp = temp->next;
    }
    return *this;
}

