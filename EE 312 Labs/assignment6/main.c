#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

#define MEM_SIZE 10000


void init_array(char slab[]);
char *my_malloc(char slab[], int numbytes);
void my_free(char slab[], char *p);


int main() {

    char slab[MEM_SIZE]= {0}; // Memory that's being used
    /*Your should right your own test cases to test your program */
    init_array(slab);
    //printf("%lld \n", *(int64_t*) (&slab[0]));
    //printf("%lld \n", *(int64_t*)(&slab[9992]));
    char * temp;// = my_malloc(slab, 9968);
    temp = my_malloc(slab, 3);
    printf("%lld\n%lld\n%lld\n%lld\n", *(int64_t*)(&slab[9992]), *(int64_t*)(&slab[9980]), *(int64_t*)(&slab[9972]), *(int64_t*)(&slab[0]));
    //printf("%p\nshould be: \n%p\n", temp, &slab[9988]);
    
    char * temp2 = my_malloc(slab, 1);
    printf("%lld\n%lld\n%lld\n%lld\n", *(int64_t*)(&slab[9992]), *(int64_t*)(&slab[9980]), *(int64_t*)(&slab[9972]), *(int64_t*)(&slab[0]));
    
    my_free(slab, temp);
    printf("%lld\n%lld\n%lld\n%lld\n", *(int64_t*)(&slab[9992]), *(int64_t*)(&slab[9980]), *(int64_t*)(&slab[9972]), *(int64_t*)(&slab[0]));
    
    my_free(slab, temp2);
    printf("%lld\n%lld\n%lld\n%lld\n", *(int64_t*)(&slab[9992]), *(int64_t*)(&slab[9980]), *(int64_t*)(&slab[9972]), *(int64_t*)(&slab[0]));
    //temp = my_malloc(slab, 3);
    //printf("%lld\n", *(int64_t*)(&slab[0]));
    
    char * check1 = my_malloc(slab, 8);
    char * check2 = my_malloc(slab, 248);
    char * check3 = my_malloc(slab, 100);
    char * check4 = my_malloc(slab, 15);
    char * check5 = my_malloc(slab, 2);
    char * check6 = my_malloc(slab, 7);
    char * check7 = my_malloc(slab, 2583);
    char * check8 = my_malloc(slab, 3);
    char * check9 = my_malloc(slab, 15);
    char * check10 = my_malloc(slab, 1203);
    
    printf("********** This should print out 1408 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[0]), *(int64_t*)(&slab[5640]));
    printf("********** This should print out -301 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[5648]), *(int64_t*)(&slab[6860]));
    printf("********** This should print out -4 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[6868]), *(int64_t*)(&slab[6892]));
    printf("********** This should print out -1 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[6900]), *(int64_t*)(&slab[6912]));
    printf("********** This should print out -646 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[6920]), *(int64_t*)(&slab[9512]));
    printf("********** This should print out -2 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9520]), *(int64_t*)(&slab[9536]));
    printf("********** This should print out -1 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9544]), *(int64_t*)(&slab[9556]));
    printf("********** This should print out -4 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9564]), *(int64_t*)(&slab[9588]));
    printf("********** This should print out -25 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9596]), *(int64_t*)(&slab[9704]));
    printf("********** This should print out -62 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9712]), *(int64_t*)(&slab[9968]));
    printf("********** This should print out -2 **********\n%lld\n%lld\n\n", *(int64_t*)(&slab[9976]), *(int64_t*)(&slab[9992]));
    
    my_free(slab, check10);
    my_free(slab, check9);
    my_free(slab, check8);
    my_free(slab, check7);
    my_free(slab, check6);
    my_free(slab, check5);
    my_free(slab, check4);
    my_free(slab, check3);
    my_free(slab, check2);
    my_free(slab, check1);
    
    printf("%lld\n%lld\n", *(int64_t*)(&slab[9992]), *(int64_t*)(&slab[0]));
    
}
