#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


//Initialize the starting point of the array
void init_array(char heap[]){
    int64_t * startPT = (int64_t*) (&heap[0]);
    int64_t * endPT = (int64_t*) (&heap[9992]);
    *startPT = 2496;
    *endPT = 2496;
}

//Allocate requested memory
char *my_malloc(char heap[], int numbytes) {
    printf("My malloc called\n");
    
    int numwords = numbytes/4;
    if (numbytes%4) {
        numwords = (numbytes/4) + 1;
        numbytes = numwords * 4;
    }
    
    int64_t * retpoint;
    int64_t * temp, * temp2;
    int64_t * start = (int64_t*)(&heap[9992]);
    int startvalue = (int)(*start);
    while (start > (int64_t*)(&heap[0])) {
        if (startvalue >= numwords+4) {
            *start = (int64_t)(numwords*(-1));
            retpoint = (int64_t*)((char*)start - numbytes);
            temp = (int64_t*)((char*)retpoint - 8);
            *temp = *start;
            temp = (int64_t*)((char*)retpoint - 16);
            *temp = (int64_t)(startvalue - numwords - 4);
            int temp3 = (int)(*temp);
            temp3 = temp3 * (-4) - 8;
            char * temp4 = (char*)(temp) + temp3;
            temp2 = (int64_t*)temp4;
            *temp2 = *temp;
            return (char*)retpoint;
        }
        if (startvalue < 0){
            start = (int64_t*)((startvalue)*(4) + (char*)start - 16);
            startvalue = (int)(*start);
            continue;
        }
        break;
    }

    
    printf("Sorry nothing is available!\n");
    return NULL;
}

//Deallocate requested memory
void my_free(char slab[], char *p) {

    int flag = 0;
    
    int64_t * toppointer;
    int64_t * bottompointer;
    int64_t * currenttop;
    int64_t * currentbottom;
    
    currenttop = (int64_t*)(p - 8);
    currentbottom = (int64_t*)((*currenttop)*(-4) + p);
    
    int64_t * temp1 = (int64_t*)((char*)currenttop - 8);
    if (*temp1 >= 0 && *temp1 < (int64_t*)(&slab[0])) {
        flag = 1;
        toppointer = (int64_t*)((*temp1)*(-4) + (char*)(temp1) - 8);
    }
    
    int64_t * temp2 = (int64_t*)((char*)currentbottom + 8);
    if (*temp2 >= 0 && *temp2 < (int64_t*)(&slab[9999])) {
        if (flag == 1) {
            flag = 3;
        }
        else if (flag == 0){
            flag = 2;
        }
        bottompointer = (int64_t*)((*temp2)*(4) + (char*)(temp2) + 8);
    }
    
    if (flag == 0) {
        *currenttop = (-1)*(*currenttop);
        *currentbottom = (-1)*(*currentbottom);
    }
    if (flag == 1) {
        int64_t x = *toppointer + (*currentbottom)*(-1) + 4;
        *toppointer = x;
        *currentbottom = x;
    }
    if (flag == 2) {
        int64_t x = *bottompointer + (*currenttop)*(-1) + 4;
        *bottompointer = x;
        *currenttop = x;
    }
    if (flag == 3) {
        int64_t x = *toppointer + *bottompointer + (*currenttop)*(-1) + 8;
        *toppointer = x;
        *bottompointer = x;
    }
    

}
