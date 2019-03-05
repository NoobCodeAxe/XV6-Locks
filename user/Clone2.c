#define PGSIZE (4096)
#include "types.h"
#include "stat.h"
#include "user.h"


void worker(void *arg_ptr);
volatile int global =1;
volatile int arg = 55;
int ppid;
#define assert(x) if (x) {} else { \
   printf(1, "%s: %d ", __FILE__, __LINE__); \
   printf(1, "assert failed (%s)\n", # x); \
   printf(1, "TEST FAILED\n"); \
   kill(ppid); \
   exit(); \
}



int
main(int argc,char *argv[])
{
	 ppid = getpid();
	void *stack = malloc(PGSIZE*2);
	assert(stack != NULL);
	if((uint)stack % PGSIZE)
		stack = stack +(4096 - (uint)stack%PGSIZE);
	int clone_pid = clone(worker, (void*)&arg ,stack);
	assert(clone_pid >0);
	while(global !=55);
	assert(arg ==1);
	printf(1,"Test Passed\n");
	exit();
}

void 
worker(void *arg_ptr){
	int tmp = *(int*)arg_ptr;
	*(int*)arg_ptr =1;
	assert(global == 1);
	global = tmp;
	exit();
}
