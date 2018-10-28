

#include "cpuOsPerformance_T.h"
using namespace std;

int main() {

	long result1;
	long result2;
	long result3;
	long result4;

	cpuOsPerformance_T testCpu;

	cout << "Start calculation" << endl;

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

