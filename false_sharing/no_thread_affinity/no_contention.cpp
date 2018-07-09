#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

struct culprit_struct {
	volatile int A;
	//volatile int C[20];
	volatile int B;
};

culprit_struct cval; 

#include "iter_count.h"

void thread_working_on_both_A_and_B () {
	volatile int temp1;
	volatile int temp2;
	for(int i=0; i< ITER_COUNT; i++){
		cval.A=10;
		temp1 = cval.A;
		cval.B=20;
		temp2 = cval.B;
	}
}



int main(){

	chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	thread first(thread_working_on_both_A_and_B);
	first.join(); 
	chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	cout << "Time difference(usec) = " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<endl;
	cout << "Time difference(nano sec) = " << chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<endl;
	return 0;
}
