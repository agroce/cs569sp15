#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef void * address_t ;

pthread_t addThread;
pthread_t modThread;
pthread_t mulThread;
pthread_t watchThread;

pthread_barrier_t doneComputingBarrier;
pthread_barrier_t doneAssigningBarrier;
pthread_barrier_t donePrintingBarrier;

int a;
int b;
int c;

int counter;

int end;

void * updateA( address_t args ){
	while(end == 0){
		int tempa = b + c;
		
		pthread_barrier_wait( &doneComputingBarrier );
		
		a = tempa;

		pthread_barrier_wait( &doneAssigningBarrier );
		pthread_barrier_wait( &donePrintingBarrier );
		// if(end){
		//     pthread_exit(NULL);
		// }
	}
}

void * updateB( address_t args ){
	while(end == 0){
		int tempb = c % a;
		
		pthread_barrier_wait( &doneComputingBarrier );
		
		b = tempb;

		pthread_barrier_wait( &doneAssigningBarrier );
		pthread_barrier_wait( &donePrintingBarrier );
		// if(end){
		//     pthread_exit(NULL);
		// }
	}
}

void * updateC( address_t args ){
	while(end == 0){
		int tempc = (b+1) * a;
		
		pthread_barrier_wait( &doneComputingBarrier );
		
		c = tempc;

		pthread_barrier_wait( &doneAssigningBarrier );
		pthread_barrier_wait( &donePrintingBarrier );
		// if(end){
		//     pthread_exit(NULL);
		// }
	}
}

void printData(){
	printf("%i a:%i b:%i c:%i\n", counter, a, b, c);
	// std::cout << counter << ", " << NowNumDeer << ", " << (int)(NowNumGrain+.5)<< ", " << (int)(NowNumInvasive+.5)<< ", " << lastTempFactor << ", " << lastPrecipFactor << std::endl ;
}

void * watcher( address_t args ){
 	while(counter < NUM){

		pthread_barrier_wait( &doneAssigningBarrier );

		printData();

		counter++;

		if(counter >= NUM){
			end = 1;
		}

		pthread_barrier_wait( &donePrintingBarrier );
 	}

}

int main( int argc, char *argv[ ] ) {
	a = 1;
	b = 1;
	c = 1;


	counter = 0;

	end = 0;

	pthread_barrier_init( &doneComputingBarrier, NULL, 3 );
	pthread_barrier_init( &doneAssigningBarrier, NULL, 4 );
	pthread_barrier_init( &donePrintingBarrier, NULL, 4 );

	int Arg = 0;
	pthread_create( &addThread, NULL, updateA, (address_t)&Arg );
	pthread_create( &modThread, NULL, updateB, (address_t)&Arg );
	pthread_create( &mulThread, NULL, updateA, (address_t)&Arg );
	pthread_create( &watchThread, NULL, watcher, (address_t)&Arg );

	pthread_join( watchThread, NULL );
	pthread_join( addThread, NULL );
	pthread_join( modThread, NULL );
	pthread_join( mulThread, NULL );

	printData();

	// assert(0);

	return 0;

}