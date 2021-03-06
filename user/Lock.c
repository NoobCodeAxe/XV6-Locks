#define PGSIZE (4096)
#include "types.h"
#include "stat.h"
#include "user.h"


void worker(void *arg_ptr);
volatile int global =0;
lock_t lock;
int num_threads =10;
int loops =1000;
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
	lock_init(&lock);
	int i;
	for (i =0; i<num_threads;i++)
	{
		int thread_pid = thread_create(worker,0);
		assert(thread_pid>0);
	}
	
	for(i=0;i<num_threads;i++)
	{
		int join_pid = thread_join();
		assert(join_pid >0);
	}
	
	assert(global == num_threads * loops);
	printf(1,"Test Passed\n");
	exit();
}

void
worker(void *arg_ptr){

int i,j,tmp;
for(i=0;i<loops;i++)
{
	lock_get(&lock);
	tmp = global;
	for(j=0;j<50;j++);
	global = tmp+1;
	lock_release(&lock);




}

exit();

}
