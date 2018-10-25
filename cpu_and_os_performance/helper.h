#ifndef _HELPER_H
#define _HELPER_H

static int fd[2];

static inline void* threadProg(void* p)
{
	struct timespec tp2 = {0,0};
	clockid_t clk_id = CLOCK_MONOTONIC_RAW;
	clock_gettime(clk_id, &tp2);
	write(fd[1], (void*)&tp2, sizeof(long double));
	close(fd[1]);
	pthread_exit(NULL);
};

static inline void* emptyThread(void *) {
  pthread_exit(NULL);
}
#endif
