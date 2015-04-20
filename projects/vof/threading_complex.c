#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <iostream>


typedef void * address_t ;

int counter;

pthread_t deerThread;
pthread_t grainThread;
pthread_t invasiveThread;
pthread_t watchThread;

pthread_barrier_t doneComputingBarrier;
pthread_barrier_t doneAssigningBarrier;
pthread_barrier_t donePrintingBarrier;

int	NowYear;		// 2014 - 2019
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;
float NowNumGrain;
float NowNumInvasive;
float lastPrecipFactor;
float lastTempFactor;
float precipFactor;
float tempFactor;



const float GRAIN_GROWS_PER_MONTH =		8.0;
const float ONE_DEER_EATS_PER_MONTH =		0.5;

const float ONE_DEER_PRODUCE_PER_MONTH = 0.12;
const float RANDOM_DEER = 0.15;


const float ONE_GRAIN_PRODUCE_PER_MONTH = 1.02;
const float RANDOM_GRAIN = 0.15;

const float AVG_PRECIP_PER_MONTH =		6.0;
const float AMP_PRECIP_PER_MONTH =		6.0;
const float RANDOM_PRECIP =			2.0;

const float AVG_TEMP =				50.0;
const float AMP_TEMP =				20.0;
const float RANDOM_TEMP =			10.0;

const float MIDTEMP =					40.0;
const float MIDPRECIP =				10.0;

float randRange(float low , float high){
	return low + (float) (rand()) /( (float)(RAND_MAX/(high-low)));
}

void updateTemperaturePrecipitation(){
	float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	NowTemp = temp + randRange( -RANDOM_TEMP, RANDOM_TEMP );

	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
	NowPrecip = precip + randRange( -RANDOM_PRECIP, RANDOM_PRECIP );
	if( NowPrecip < 0. )
		NowPrecip = 0.;
	lastTempFactor = tempFactor;
	lastPrecipFactor = precipFactor;
	precipFactor = exp(-pow((NowPrecip- MIDPRECIP )/10,2.0));
	tempFactor = exp(-pow((NowTemp- MIDTEMP )/10,2.0));

}

void * updateGrain( address_t args ){
	while(1){


		float tempFactor = exp(-pow((NowTemp- MIDTEMP )/10,2.0));
		float precipFactor = exp(-pow((NowPrecip- MIDPRECIP )/10,2.0));

		precipFactor = precipFactor * (NowNumGrain/(NowNumGrain+NowNumInvasive)+0.2);

		float tempNumGrain = NowNumGrain + GRAIN_GROWS_PER_MONTH * tempFactor * precipFactor - NowNumDeer * ONE_DEER_EATS_PER_MONTH* (NowNumGrain/(NowNumGrain+NowNumInvasive)) ;

		if (tempNumGrain <= 0.5){
			tempNumGrain = 1;
		}


		pthread_barrier_wait( &doneComputingBarrier );
		
		NowNumGrain = tempNumGrain;

		pthread_barrier_wait( &doneAssigningBarrier );
		pthread_barrier_wait( &donePrintingBarrier );

	}

}

void * updateInvasive( address_t args ) {
	while(1){

		float precipFactor = exp(-pow((NowPrecip- MIDPRECIP )/10,2.0));

		precipFactor = precipFactor * (NowNumInvasive/(NowNumGrain+NowNumInvasive)+0.5);

		int tempNumInvasive = NowNumInvasive + GRAIN_GROWS_PER_MONTH * 1.2 * precipFactor - NowNumDeer * ONE_DEER_EATS_PER_MONTH * (NowNumInvasive/(NowNumGrain+NowNumInvasive)) * 2 ;

		if (tempNumInvasive <= 0.5){
			tempNumInvasive = 1;
		}

		pthread_barrier_wait( &doneComputingBarrier );
		
		NowNumInvasive = tempNumInvasive;

		pthread_barrier_wait( &doneAssigningBarrier );
		pthread_barrier_wait( &donePrintingBarrier );
	}
}

void * updateDeer( address_t args ){
	while(1){

		float foodSupply = NowNumGrain+(NowNumInvasive/3) - NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		float tempNumDeer = NowNumDeer;

		if (foodSupply <= 0) {
			tempNumDeer += foodSupply/3-1;
		} else {
			tempNumDeer += foodSupply/9+1;
		}

		if (tempNumDeer <= 0) {
			tempNumDeer = 1.0;
		}

		pthread_barrier_wait( &doneComputingBarrier );
		
		NowNumDeer = (int)tempNumDeer;
		
		pthread_barrier_wait( &doneAssigningBarrier );

		pthread_barrier_wait( &donePrintingBarrier );

	}

}

void printData(){
	// std::cout << counter << ", " << NowNumDeer << ", " << (int)(NowNumGrain+.5)<< ", " << (int)(NowNumInvasive+.5)<< ", " << lastTempFactor << ", " << lastPrecipFactor << std::endl ;
	counter++;
}

void * watcher( address_t args ){
 	while(NowYear < 2015){

		pthread_barrier_wait( &doneAssigningBarrier );

		updateTemperaturePrecipitation();

		printData();

		NowMonth++;
		if (NowMonth >= 12) {
			NowMonth = 0;
			NowYear++;
		}

		pthread_barrier_wait( &donePrintingBarrier );
 	}	
}

int main( int argc, char *argv[ ] ) {
	NowNumDeer = 1;
	NowNumGrain = 1;
	NowNumInvasive = 1;


	counter = 0;

	NowMonth =    11;
	NowYear  = 2014;

	// srand (time(NULL));
	srand (1337);

	pthread_barrier_init( &doneComputingBarrier, NULL, 3 );
	pthread_barrier_init( &doneAssigningBarrier, NULL, 4 );
	pthread_barrier_init( &donePrintingBarrier, NULL, 4 );

	int Arg = 0;
	pthread_create( &deerThread, NULL, updateDeer, (address_t)&Arg );
	pthread_create( &grainThread, NULL, updateGrain, (address_t)&Arg );
	pthread_create( &invasiveThread, NULL, updateInvasive, (address_t)&Arg );
	pthread_create( &watchThread, NULL, watcher, (address_t)&Arg );

	pthread_join( watchThread, NULL );

	pthread_cancel( deerThread );
	pthread_cancel( grainThread );
	pthread_cancel( invasiveThread );

	printf("%i\n", NowNumDeer);
	assert(NowNumDeer == 3);

	return 0;

}