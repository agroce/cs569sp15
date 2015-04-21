#include <stdio.h>
int nondet_int (void);//Adding Range of Non-Deterministic values to variables.
void insert(int);//Insert Operation Definition
void delete(void);//Delete Operation Definition
void display(void);//Display Operation Definition
int queue_array[MAX+1];//Queue Definition
int rear = -1;//Queue Rear Pointer
int front = -1;//Queue Front Pointer
main()
{
    	int choice;
    	int a=nondet_int();//Input Data for Queue Operation

	//Loop for Choosing Queue Operation on the Input Data
	for(int i=0;i<=MAX;i++)
	{
		//choice range assumption
		__CPROVER_assume(choice>=1 && choice<=3);
		choice=nondet_int();
		int input = a+(i*1000);
		//Non Zero Positive Input Assumption
		__CPROVER_assume(input > 0);
		printf("LOG: Choice is %d",choice);

		/*Choosing Operation
		1. Inserting Input value to the Queue.
		2. Deleting First in Queue Value.
		3. Displaying Current Queue.
		*/
        	switch (choice)
        	{
            		case 1:
            		insert(input);
	    		break;
            		case 2:
            		delete();
            		break;
            		case 3:
            		display();
            		break;
            		default:
            		printf("Wrong choice \n");
        	} /*End of switch*/
	}//End of for loop
	display();//Displaying Final Queue Results after all operations.
} /*End of main()*/
insert(int add_item)
{
    	//For First Insertion
	if(front == -1)
	{
		front=0;
		rear=0;

/*Introducing Bug: 
First Queue Index will not be used. Hence would violate the Index Bound */
		rear++;
	}

	int i;
	assert(rear <= MAX);//Queue Overflow Check
	queue_array[rear] = add_item;//Assigning Input to Array
	rear = rear + 1;
    	printf("LOG: Element Inserted in %d is %d", rear,add_item);
} /*End of insert()*/
 
delete()
{
    int temp,i;
    if (front == -1|| front > rear)//Queue Underflow Check
    {
        printf("LOG: Queue Underflow \n");
	return;
    }
    else
    {
        printf("LOG: Element deleted from queue is : %d\n", queue_array[front]);
	front=front+1;//Updating Deletion Operation on Queue
    }
} /*End of delete() */
display()
{
    int i;
    if (front == -1)
        printf("LOG: Queue is empty \n");//Empty Queue Check
    else
    {
	//Displaying Queue Current Status
        printf("LOG: Queue is : \n");
        for (i = front; i < rear; i++)
            printf("LOG: Queue[%d]=%d ", i,queue_array[i]);
        printf("\n");
    }
} /*End of display() */
