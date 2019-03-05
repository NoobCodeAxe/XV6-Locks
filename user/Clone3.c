#define PGSIZE (4096)
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "param.h"


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

	int fd = open("tmp",O_WRONLY|O_CREATE);
	assert(fd ==3);
	int clone_pid = clone(worker, 0 ,stack);
	assert(clone_pid >0);
	while(!newfd);
	assert(write(newfd, "goodbye\n", 8)==-1);
	printf(1,"Test Passed\n");
	exit();
}

void 
worker(void *arg_ptr){
	assert(write(3, "hello\n", 6)==6);
	xchg(&newfd,open("tmp2",O_WRONLY|O_CREATE));
	exit();
}
