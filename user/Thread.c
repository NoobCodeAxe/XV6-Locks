
#include "types.h"
#include "stat.h"
#include "user.h"
#define PGSIZE (4096)

void worker(void *arg_ptr);

int ppid;
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}

int global = 1;


int
main(int argc,char *argv[])
{
	
	ppid = getpid();
	int arg =35;
	int thread_pid = thread_create(worker,&arg);
	assert(thread_pid>0);

	int join_pid  = thread_join();
	assert(join_pid == thread_pid);
	assert(global == 2);

	printf(1,"Test Passed\n");
	exit();
}

void 
worker(void *arg_ptr){
	int arg= *(int*)arg_ptr;
	assert(arg == 35)
	assert(global == 1);
	global++;
	exit();
}
