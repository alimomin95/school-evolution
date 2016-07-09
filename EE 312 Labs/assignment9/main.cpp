#include "functions.hh"
#include <stdio.h>
#include <cassert>


void test00(){
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = addPolynomials(p1, p2);
	assert(result.getHead()->value ==1);
	assert(result.getHead()->next->value == 5);
}

void test01(){
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = subtractPolynomials(p1, p2);
	assert(result.getHead()->value ==1);
	assert(result.getHead()->next->value == -1);
}

void test02(){
	Poly p1;
	Poly p2;
	p1.append(1);
	p1.append(2);
	p2.append(3);

	Poly result = multiplyPolynomials(p1, p2);
	assert(result.getHead()->value ==3);
	assert(result.getHead()->next->value == 6);
}

void test03(){
	Poly p1;
	Poly p2;
	p1.append(1);
	p2.append(1);
	Poly result = addPolynomials(p1, p2);
	assert(result.getHead()->value == 2);
	Poly p3;
	p3.append(2);
	result = addPolynomials(p1, p3);
	assert(result.getHead()->value == 3);
}

void test04(){
    Poly p1;
    Poly p2;
    
    p1.append(10);
    p1.append(0);
    p1.append(-5);
    p1.append(-300);
    
    p2.append(15.4);
    p2.append(0);
    p2.append(0);
    p2.append(0);
    p2.append(-3.33);
    
    Poly result = multiplyPolynomials(p1, p2);
    assert(result.getHead()->value ==154);
    assert(result.getHead()->next->value == 0);
    assert(result.getHead()->next->next->value == -77);
    assert(result.getHead()->next->next->next->value == -4620);
    assert(result.getHead()->next->next->next->next->value == -33.3);
    assert(result.getHead()->next->next->next->next->next->value == 0);
    assert(result.getHead()->next->next->next->next->next->next->value == 16.65);
    assert(result.getHead()->next->next->next->next->next->next->next->value == 999);
    
    Poly p3;
    
    Poly result2 = subtractPolynomials(p3, result);
    assert(result2.getHead()->value == -154);
    assert(result2.getHead()->next->value == 0);
    assert(result2.getHead()->next->next->value == 77);
    assert(result2.getHead()->next->next->next->value == 4620);
    assert(result2.getHead()->next->next->next->next->value == 33.3);
    assert(result2.getHead()->next->next->next->next->next->value == 0);
    assert(result2.getHead()->next->next->next->next->next->next->value == -16.65);
    assert(result2.getHead()->next->next->next->next->next->next->next->value == -999);
    
    p3.append(154);
    p3.append(0);
    p3.append(-77);
    p3.append(-4620);
    p3.append(-33.3);
    p3.append(0);
    p3.append(16.65);
    p3.append(0);
    
    Poly result3 = addPolynomials(p3, result2);
    assert(result3.getHead()->value == -999);
    assert(result3.getHead()->next == 0);
}

void myTEST1() {	//ADDITION, BOTH POLYS EMPTY
    Poly p1;
    Poly p2;
    Poly result = addPolynomials(p1, p2);
    assert(result.getHead() == NULL);
    printf("myTEST1 Passed!\n");
}

void myTEST2() {	//ADDITION, FIRST POLY EMPTY
    Poly p1;
    Poly p2;
    p1.append(3.5);
    Poly result = addPolynomials(p1, p2);
    assert(result.getHead()->value == 3.5);
    assert(result.getHead()->next == NULL);
    printf("myTEST2 Passed!\n");
}

void myTEST3() {	//ADDITION, SECOND POLY EMPTY
    
    Poly p1;
    Poly p2;
    p2.append(-7.6);
    Poly result = addPolynomials(p1, p2);
    assert(result.getHead()->value == -7.6);
    assert(result.getHead()->next == NULL);
    printf("myTEST3 Passed!\n");
    
}

void myTEST4() {	//ADDITION, GETS RID OF LEADING ZEROS
    Poly p1;
    Poly p2;
    p1.append(-1.5);
    p1.append(2.3);
    p1.append(7.8);
    p1.append(0.0);
    p1.append(8.9);
    
    p2.append(1.5);
    p2.append(-2.3);
    p2.append(7.8);
    p2.append(0.0);
    p2.append(8.9);
    
    Poly result = addPolynomials(p1, p2);
    
    assert(result.getHead()->value == 15.6);
    assert(result.getHead()->next->value == 0);
    assert(result.getHead()->next->next->value == 17.8);
    assert(result.getHead()->next->next->next == NULL);
    printf("myTEST4 Passed!\n");
    
}

void myTEST5() {	//ADDITION OF NEGATIVE NUMBERS CORRECTLY
    Poly p1;
    Poly p2;
    p1.append(-2.1);
    p2.append(-4.9);
    Poly result = addPolynomials(p1, p2);
    assert(result.getHead()->value == -7.0);
    assert(result.getHead()->next == NULL);
    printf("myTEST5 Passed!\n");
    
}

void myTEST6() {	//ADDITION, THE RESULT IS ONLY THE CONSTANT 0
    Poly p1;
    Poly p2;
    p1.append(-20.321);
    p2.append(20.321);
    p1.append(-98.456);
    p2.append(98.456);
    Poly result = addPolynomials(p1, p2);
    assert(result.getHead()->value == 0);
    assert(result.getHead()->next == NULL);
    printf("myTEST6 Passed!\n");
    
    
}

//BELOW ARE THE TESTS FOR SUBTRACTION

void myTEST7() {			//SUBTRACTION, BOTH POLYS ARE EMPTY
    Poly p1;
    Poly p2;
    Poly result = subtractPolynomials(p1, p2);
    assert(result.getHead() == NULL);
    printf("myTEST7 Passed!\n");
}

void myTEST8() {			//SUBTRACTION, ONLY THE SECOND POLY IS EMPTY
    Poly p1;
    Poly p2;
    p1.append(3.5);
    Poly result = subtractPolynomials(p1, p2);
    assert(result.getHead()->value == 3.5);
    assert(result.getHead()->next == NULL);
    printf("myTEST8 Passed!\n");
    
}

void myTEST9() {		//SUBTRACTION, ONLY THE FIRST POLY IS EMPTY
    Poly p1;
    Poly p2;
    p2.append(-3.5);
    Poly result = subtractPolynomials(p1, p2);
    assert(result.getHead()->value == 3.5);
    assert(result.getHead()->next == NULL);
    printf("myTEST9 Passed!\n");
    
}

void myTEST10() {		//SUBTRACTION, WITH LEADING ZEROS
    Poly p1;
    Poly p2;
    p1.append(-3.5);
    p1.append(5.8);
    p1.append(4);
    p1.append(3);
    
    
    p2.append(-3.5);
    p2.append(5.8);
    p2.append(3.5);
    p2.append(1.5);
    
    Poly result = subtractPolynomials(p1, p2);
    
    assert(result.getHead()->value == 0.5);
    assert(result.getHead()->next->value == 1.5);
    assert(result.getHead()->next->next == NULL);
    printf("myTEST10 Passed!\n");
}

void myTEST11() {	//ADDITION, THE RESULT IS ONLY THE CONSTANT 0
    Poly p1;
    Poly p2;
    p1.append(20.3);
    p2.append(20.3);
    p1.append(10.5);
    p2.append(10.5);
    Poly result = subtractPolynomials(p1, p2);
    assert(result.getHead()->value == 0);
    assert(result.getHead()->next == NULL);
    printf("myTEST11 Passed!\n");
    
}

//BELOW ARE THE TESTS FOR MULTIPLY

void myTEST12() {	//MULTIPLY, BOTH POLYS EMPTY
    Poly p1;
    Poly p2;
    Poly result = multiplyPolynomials(p1, p2);
    assert(result.getHead() == NULL);
    printf("myTEST12 Passed!\n");
}

void myTEST13() {	//MULTIPLY , SECOND POLY ONLY EMPTY
    Poly p1;
    Poly p2;
    p1.append(3.5);
    
    
    Poly result = multiplyPolynomials(p1, p2);
    assert(result.getHead()->value == 3.5);
    printf("myTEST13 Passed!\n");
    
    
}

void myTEST14() {	//MULTIPLY , SECOND POLY EMPTY
    Poly p1;
    Poly p2;
    p2.append(3.5);
    
    
    Poly result = multiplyPolynomials(p1, p2);
    assert(result.getHead()->value == 3.5);
    printf("myTEST14 Passed!\n");
    
}

void myTEST15() {		//MULTIPLY, RESULT IS CONSTANT 0
    Poly p1;
    Poly p2;
    p1.append(0);
    p2.append(3.5);
    p2.append(7.6);
    p2.append(100.301);
    
    Poly result = multiplyPolynomials(p1, p2);
    assert(result.getHead()->value == 0);
    assert(result.getHead()->next == NULL);
    printf("myTEST15 Passed!\n");
    
    
    
}
int main(){
	test00();
	test01();
	test02();
	test03();
    test04();
    myTEST1();
    myTEST2();
    myTEST3();
    myTEST4();
    myTEST5();
    myTEST6();
    myTEST7();
    myTEST8();
    myTEST9();
    myTEST10();
    myTEST11();
    myTEST12();
    myTEST13();
    myTEST14();
    myTEST15();
}
