

#include "cpuOsPerformance_T.h"
using namespace std;

int main() {

	long result1;
	long result2;
	long result3;
	long result4;

	cpuOsPerformance_T testCpu;

	cout << "Start calculation" << endl;

	// Read time test
	long double result_time;
	for(int i= 0; i <100;i++)
	{
		long double temp = testCpu.readTimeOverhead();	
		cout << "clock_gettime() overhead  " << i+1 << ": " << temp <<endl;
		result_time = result_time + temp;	
	}
	cout << "average clock_gettime call overhead in nano second: " << result_time / 100.0 <<endl;

	// Loop overhead test
	long double result_loop;
	for(int i= 0; i <100;i++)
	{
		long double temp = testCpu.loopOverhead();	
		cout << "loop overhead  " << i+1 << ": " << temp <<endl;
		result_loop = result_loop + temp;	
	}
	cout << "average loop overhead (per iteration) in nano second: " << result1 / 100.0 <<endl;

	// Process creation overhead test
	for(int i= 0; i <100;i++)
	{
		long temp = testCpu.processCreationOverhead();	
		cout << "process creation overhead  " << i+1 << ": " << temp <<endl;
		result1 = result1 + temp;	
	}
	cout << "average process creation overhead in nano second: " << result1 / 100.0 <<endl;

	for(int i= 0; i <100;i++)
	{
		long temp1 = testCpu.threadCreationOverhead() ;	
		cout << "thread creation overhead  " << i+1 << ": " << temp1 <<endl;
		result2 = result2 + temp1;	
	}
	cout << "average thread creation overhead in nano second: " << result2 / 100.0 <<endl;

	for(int i= 0; i <100;i++)
	{
		long temp2 = testCpu.processContextSwitchOverhead() ;	
		cout << "process context switch  " << i+1<< ": " << temp2 <<endl;
		result3 = result3 + temp2;	
	}
	cout << "average process context switch overhead in nano second: " << result3 / 100.0 <<endl;

	for(int i= 0; i <100;i++)
	{
		long temp3 = testCpu.threadContextSwitchOverhead() ;	
		cout << "thread context switch  " << i+1 << ": " << temp3 <<endl;
		result4 = result4 + temp3;	
	}
	cout << "average thread context switch overhead in nano second: " << result4 / 100.0 <<endl;
	
	cout << "Done calculation" << endl;
	return 0;
}

