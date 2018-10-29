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

long double cpuOsPerformance_T::readTimeOverhead()
{
  	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;
	
	// Get initial time
	clock_gettime(clk_id, &tp1);

	// Call clock_gettime() 20x
	int num_calls = 21;
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	clock_gettime(clk_id, &tp2);
	
	// Average time to read time is tp2-tp2/num_calls
	// Note: num_calls is # of times tp2 is set, +1 for tp1
	long double time_diff =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );
	long double result = time_diff/((double) num_calls);
	return result;
	
}

long double cpuOsPerformance_T::loopOverhead()
{
  	struct timespec tp1 = {0, 0};
	struct timespec tp2 = {0, 0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;

	// Set up short loop variables
	int a, b, c, d, e, f;
	a = 0;
	b = 1;
	c = 2;
	d = 3;
	e = 4;

	// Get initial time
	clock_gettime(clk_id, &tp1);

	// Run loop
	// Each loop has simple instructions in a dependent loop
	for (int i=0; i<100; i++) {
		a = e + 2;
		b = a + 2;
		c = b + 2;
		d = c + 2;
		e = e + 2;
	}

	// Get ending time
	clock_gettime(clk_id, &tp2);
	long double short_loop_runtime =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );

	// Now set up long loop variables (20 total)
	int g,h,i,j,k,l,m,n,o,p,q,r,s,t;
	a = 0;
	b = 1;
	c = 2;
	d = 3;
	e = 4;
	f = 5;
	g = 6;
	h = 7;
	i = 8;
	j = 9;
	k = 10;
	l = 11;
	m = 12;
	n = 13;
	o = 14;
	p = 15;
	q = 16;
	r = 17;
	s = 18;
	t = 19;
	
	// Get initial time before long loop
	clock_gettime(clk_id, &tp1);

	// Short loop was 500 instructions.  Match long loop
	for (int i=0; i<25; i++) {
	a = t + 2;
	b = a + 2;
	c = b + 2;
	d = c + 2;
	e = d + 2;
	f = e + 2;
	g = f + 2;
	h = g + 2;
	i = h + 2;
	j = i + 2;
	k = j + 2;
	l = k + 2;
	m = l + 2;
	n = m + 2;
	o = n + 2;
	p = o + 2;
	q = p + 2;
	r = q + 2;
	s = r + 2;
	t = s + 2;
	}

	// Get end time after long loop
	clock_gettime(clk_id, &tp2);
	long double long_loop_runtime =  (((tp2.tv_sec - tp1.tv_sec)*1000.0 * 1000.0 * 1000.0) + (tp2.tv_nsec - tp1.tv_nsec) );

	// Result is [(long loop time) - (short loop time)] / [(long loop interations) - (short loop iterations)]
	long double result = (long_loop_runtime - short_loop_runtime) / ((double) (100 - 25));

	return result;
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


