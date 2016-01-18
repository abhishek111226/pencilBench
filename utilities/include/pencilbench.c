#include "pencilbench.h"
double start_time=0; 
double stop_time=0; 

double get_time() 
{
	struct timeval Tp;
	int stat;

	stat = gettimeofday (&Tp, NULL);
	if (stat != 0)
		fprintf(stderr, "Error return from gettimeofday: %d", stat);
	return Tp.tv_sec + Tp.tv_usec * 1.0e-6;
}

double pencilbench_timer_start()
{
	start_time=get_time();
	return start_time;
}

double pencilbench_timer_stop()
{
	stop_time=get_time();
	return stop_time;
}

double pencilbench_timer_print()
{
	fprintf(stderr, "%f ",(stop_time-start_time));
	return stop_time-start_time;
}

void* pencilbench_alloc_data(unsigned long long int n, int elt_size)
{
	/// FIXME: detect overflow!
	size_t val = n;
	val *= elt_size;
	void* ret = malloc(val);
	if(ret==NULL) 	
	{
		fprintf (stderr, "[PencilBench] malloc : cannot allocate memory");
		exit (1);
	}
	return ret;
}
