#ifndef _CPUOSPERFORMANCE_T_H
#define _CPUOSPERFORMANCE_T_H


#include<time.h>
#include<math.h>
#include<iostream>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include "helper.h"
using namespace std;

class cpuOsPerformance_T
{
	public:
		cpuOsPerformance_T();
		~cpuOsPerformance_T();
		long double readTimeOverhead();
		long double loopOverhead();
		long double processContextSwitchOverhead();
		long double threadContextSwitchOverhead();
		long double processCreationOverhead();
		long double threadCreationOverhead();
		
	private:
		

};

#endif

