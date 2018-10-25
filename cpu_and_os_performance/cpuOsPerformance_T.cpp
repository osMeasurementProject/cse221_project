/*
Functions to measure CPU and OS performance
*/

#include "cpuOsPerformance_T.h"
#include "helper.h"

cpuOsPerformance_T::cpuOsPerformance_T()
{
	cout<<"cpuOsPerformance_T object created" <<endl;
}

cpuOsPerformance_T::~cpuOsPerformance_T()
{
	cout<<"cpuOsPerformance_T object destroyed" <<endl;
}

long double cpuOsPerformance_T::processContextSwitchOverhead()
{
	pid_t pid;
  	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;
	long double result;
	int fdPipe[2];

	//create unix pipe
	pipe(fdPipe);

	//fork child process
	pid = fork();

	if (pid == 0) 
	{	
		//child process
    	clock_gettime(clk_id, &tp2); //end time
    	write(fdPipe[1], (void*)&tp2, sizeof(timespec));
		close(fdPipe[1]);
    	exit(1);
  	}
  	else if (pid > 0)
	{
		//parent process
    	clock_gettime(clk_id, &tp1); //start time
    	wait(NULL);
    	read(fdPipe[0], (void*)&tp2, sizeof(timespec));
		close(fdPipe[0]);
  	}
	else
	{
		cout << " ERROR: fork() failed " <<endl;
	}
	//cout << "process contex switch  start second : " << tp1.tv_sec << " nano second : " <<tp1.tv_nsec <<endl;
	//cout << "process contex switch end  second : " << tp2.tv_sec << " nano second : " <<tp2.tv_nsec <<endl;
	result =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );
	return result;
}


long double cpuOsPerformance_T::threadContextSwitchOverhead()
{

	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;	
	long double result;
	pthread_t thread;

	pipe(fd); // create pipe
	pthread_create(&thread, NULL, threadProg, NULL); // create pthread

	clock_gettime(clk_id, &tp1);
	pthread_join(thread, NULL);
	read(fd[0], (void*)&tp2, sizeof(timespec));
	close(fd[0]);

	//cout << "thread contex switch  start second : " << tp1.tv_sec << " nano second : " <<tp1.tv_nsec <<endl;
	//cout << "thread contex switch end  second : " << tp2.tv_sec << " nano second : " <<tp2.tv_nsec <<endl;
	result =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );
	return result;
}


long double cpuOsPerformance_T::processCreationOverhead()
{
	pid_t pid;
  	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;
	long double result;

	// start time and fork child process
	clock_gettime(clk_id, &tp1);
	pid = fork();

	if (pid == 0) 
	{
		//child process
		exit(1);
  	}
  	else if (pid > 0)
	{
		//parent process
    	clock_gettime(clk_id, &tp2); //end time
		wait(NULL);
  	}
	else
	{
		cout << " ERROR: fork() failed " <<endl;
	}
	//cout << "process creation start second : " << tp1.tv_sec << " nano second : " <<tp1.tv_nsec <<endl;
	//cout << "process creation end  second : " << tp2.tv_sec << " nano second : " <<tp2.tv_nsec <<endl;
	result =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );
	return result;
}

long double cpuOsPerformance_T::threadCreationOverhead()
{
	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;	
	pthread_t thread;
	long double result;

	clock_gettime(clk_id, &tp1); // start time
	pthread_create(&thread, NULL, emptyThread, NULL); // create pthread
	clock_gettime(clk_id, &tp2); //end time
	pthread_join(thread, NULL);

	//cout << "thread creation  start second : " << tp1.tv_sec << " nano second : " <<tp1.tv_nsec <<endl;
	//cout << "thread creation end  second : " << tp2.tv_sec << " nano second : " <<tp2.tv_nsec <<endl;
	result =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );
	return result;
}


