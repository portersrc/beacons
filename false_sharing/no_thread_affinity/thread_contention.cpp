#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

struct culprit_struct {
	volatile int A;
//	volatile int C[20];
	volatile int B;
};

culprit_struct cval; 

#include "iter_count.h"

void thread_working_on_A () {
	volatile int *temp = new int;
	for(int i=0; i< ITER_COUNT; i++){
		cval.A=10;
		*temp = cval.A;
	}
}

void thread_working_on_B () {
	volatile int *temp = new int;
	for(int i=0; i< ITER_COUNT; i++){
		cval.B=20;
		*temp = cval.B;
	}
}


int main(){

	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	thread first(thread_working_on_A);
	thread second(thread_working_on_B);

	first.join(); //thread_working_on_A
	second.join(); //thread_working_on_B
	chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	cout << "Time difference(usec) = " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<endl;
	cout << "Time difference(nano sec) = " << chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<endl;
	return 0;
}
