#define PGSIZE (4096)
#include "types.h"
#include "stat.h"
#include "user.h"


void worker(void *arg_ptr);
volatile int global =1;
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

	int arg = 42;
	int clone_pid = clone(worker,&arg,stack);
	assert(clone_pid>0);

	sbrk(PGSIZE);
	void **join_stack = (void**) ((uint)sbrk(0)-4);
	assert(join((void**)((uint)join_stack+2))==-1);
	assert(join(join_stack) == clone_pid)
	assert(stack == *join_stack)
	assert(global == 2);
	printf(1,"Test Passed\n");
	exit();
}

void 
worker(void *arg_ptr){
	int arg = *(int*)arg_ptr;
	assert(arg==42);
	assert(global ==1);
	global++;
	exit();
}
