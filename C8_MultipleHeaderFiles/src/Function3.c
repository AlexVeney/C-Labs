#include <stdio.h>
#include <stdlib.h>
#include "Function3.h"
#include "Lab8.h"


void Function3(){
	int i = 0;
        int *p = (int *) malloc(sizeof(int) * ARRAY_SIZE);
        if (p == NULL)
        {
           fprintf(stderr, "function3(): Error allocating p\n");
           exit(1);
        }

        printf("In function3()...\n");

        // Initialize the array
        for (i=0; i<ARRAY_SIZE; i++)
        {
            p[i]=i;
        }

        // Print part of the array
        for (i=0; i<PARTIAL_SIZE; i++)
        {
            printf("function3(): %s = %d,%s = %d ", PR(i),i,PR(p[i]), p[i]);
           printf("\n");
        }
   
        free(p); 
}

