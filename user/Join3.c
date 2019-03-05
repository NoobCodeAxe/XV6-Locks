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
	int fork_pid = fork();
	if (fork_pid ==0){exit();}
	assert(fork_pid>0);

	void *join_stack;
	int join_pid = join(&join_stack);
	assert(join_pid == -1);

	printf(1,"Test Passed\n");
	exit();
}


