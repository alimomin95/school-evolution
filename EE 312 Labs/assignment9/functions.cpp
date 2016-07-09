
#include "functions.hh"
#include <stdio.h>
#include <stdlib.h>

Poly addPolynomials(Poly p1, Poly p2){
    int length1 = p1.getListLength();
    int length2 = p2.getListLength();
    Poly p;
    Node* head1 = p1.getHead();
    Node* head2 = p2.getHead();
    
    if(head1 == 0){
        if(head2 == 0){
            return p;
        }
        else {
            return p2;
        }
    }
    else if(head2 == 0){
        return p1;
    }
    
    if (length1 > length2){
        int diff = length1 - length2;
        for (int i = 0; i<diff; i++) {
            p.append(head1->value);
            head1 = head1->next;
        }
    }
    else if (length2 > length1){
        int diff = length2 - length1;
        for (int i = 0; i<diff; i++) {
            p.append(head2->value);
            head2 = head2->next;
        }
    }
    while(head1 != 0 && head2 != 0){
        p.append(head1->value + head2->value);
        head1 = head1->next;
        head2 = head2->next;
    }
	
    Node* temp = p.getHead();
    
    if(temp->value == 0){
        while(temp->next != 0 && temp->value == 0){
            Node* n = temp->next;
            p.removeFromHead();
            temp = n;
        }
    }
    
    return p;
}


Poly subtractPolynomials(Poly p1, Poly p2){
    int length1 = p1.getListLength();
    int length2 = p2.getListLength();
    Poly p;
    Node* head1 = p1.getHead();
    Node* head2 = p2.getHead();
    
    if(head1 == 0){
        if(head2 == 0){
            return p;
        }
        else {
            int diff = length2 - length1;
            for (int i = 0; i<diff; i++) {
                p.append(- head2->value);
                head2 = head2->next;
            }
            return p;
        }
    }
    else if(head2 == 0){
        return p1;
    }
    
    if (length1 > length2){
        int diff = length1 - length2;
        for (int i = 0; i<diff; i++) {
            p.append(head1->value);
            head1 = head1->next;
        }
    }
    else if (length2 > length1){
        int diff = length2 - length1;
        for (int i = 0; i<diff; i++) {
            p.append(head2->value);
            head2 = head2->next;
        }
    }
    while(head1 != 0 && head2 != 0){
        p.append(head1->value - head2->value);
        head1 = head1->next;
        head2 = head2->next;
    }
    
    Node* temp = p.getHead();
    
    if(temp->value == 0){
        while(temp->next != 0 && temp->value == 0){
            Node* n = temp->next;
            p.removeFromHead();
            temp = n;
        }
    }
    
    return p;

}

Poly multiplyPolynomials(Poly p1, Poly p2){
    int length1 = p1.getListLength();
    int length2 = p2.getListLength();
    Poly p;
    Node* head1 = p1.getHead();
    Node* head2 = p2.getHead();
    
    if(head1 == 0){
        if(head2 == 0){
            return p;
        }
        else {
            return p2;
        }
    }
    else if(head2 == 0){
        return p1;
    }

    
    double * arr1 = (double*)calloc(length1, sizeof(double));
    double * arr2 = (double*)calloc(length2, sizeof(double));
    
    int index = length1-1;
    Node* temp = p1.getHead();
    while(index >= 0){
        arr1[index] = temp->value;
        index --;
        temp = temp->next;
    }
    
    index = length2-1;
    temp = p2.getHead();
    while(index >= 0){
        arr2[index] = temp->value;
        index --;
        temp = temp->next;
    }
    
    double * result = (double*)calloc(length1+length2-1, sizeof(double));
    
    for (int i = 0; i<length1; i ++) {
        for(int j = 0; j<length2; j++){
            result[i+j] += (arr1[i]) * (arr2[j]);
        }
    }
	
    index = length1 + length2 - 1;
    
    while(index > 0){
        p.append(result[index - 1]);
        index --;
    }
    
    free(arr1);
    free(arr2);
    free(result);
    
    temp = p.getHead();
    
    if(temp->value == 0){
        while(temp->next != 0 && temp->value == 0){
            Node* n = temp->next;
            p.removeFromHead();
            temp = n;
        }
    }
    
    return p;
}
