#include <time.h>

inline double dclock(void)
{
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	return tp.tv_sec+1.0e-9*tp.tv_nsec;
}
