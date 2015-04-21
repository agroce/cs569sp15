/* 
C program found on the web to implement priority queue.
http://www.sanfoundry.com/c-program-priority-queue/ 
*/

#include <stdio.h>
#include "priority_queue.h"

//#define MAX 5

/* Function to create an empty priority queue */

void create()
{
	front = rear = -1;

}

     

/* Function to insert value into priority queue */

void insert_by_priority(int data)
{
	if (rear >= MAX - 1) {

        	printf("\nQueue overflow no more elements can be inserted");

            	return;

        }

        if ((front == -1) && (rear == -1)) {

        	front++;

            	rear++;

            	pri_que[rear] = data;

		printf("LOG: Adding item %u, front = %d, rear = %d\n", data, front, rear);

            	return;

        }    

        else

            	check(data);

// Introduced BUG, I put front++ instead of rear++
        //rear++;
	front++;

}

     

/* Function to check priority and place element */

void check(int data)
{
	int i,j;

	printf("LOG: Adding item %u\n", data);

     	for (i = 0; i <= rear; i++) {
        	
		if (data >= pri_que[i]) {

                	for (j = rear + 1; j > i; j--) {

                    		pri_que[j] = pri_que[j - 1];

                	}

                	pri_que[i] = data;

                	return;

            	}

        }

        pri_que[i] = data;

}  


/* Function to display queue elements */

void display_pqueue() {

        if ((front == -1) && (rear == -1)) {

        	printf("\nLOG: Queue is empty");

            	return;

        }

	printf("LOG: front = %d, rear = %d\n", front, rear);
     
	int i;

        for (i = front; i <= rear; i++) {
			
            	printf("LOG: %u ", pri_que[i]);

        }

     

        //front = 0;

    }


 
