
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int rand_r ( unsigned int *seed)
{
  unsigned int next = *seed;
  int result;
  next *= 1103515245;
  next += 12345;
  result = (unsigned int) (next/65536)% 2048;

  next *= 1103515245;
  next += 12345;
  result <<=10;
  result ^= (unsigned int) (next/65536) % 1024;

  next *= 1103515245;
  next += 12345;
  result <<=10;
  result ^=(unsigned int) (next/65536) % 1024;

  *seed = next;
  return result;
}  

unsigned int seed;
// Call rand_r to get min/max version
int rand(int min, int max) {return min + (rand_r(&seed) % (max-min));}


//running system call
int
main(void)
{
    //printf(1, "There are %d system calls. \n", howmanysys());
    struct pstat a;
   settickets(30);
    getpinfo(&a);
    int i;
    for(i = 0; i < 12; i++) {
      printf(1,"Process %d ticks is %d\n", i, a.tick[i]);
    }

   // settickets(30);
    int  pid, pid2;
    pid = fork();
    if(pid ==0)
    {
      settickets(20);
      //settickets(20);
	int stuff = 100;
         int j;
         for (j=0;j<stuff*10000;j++)
	{
	  stuff = stuff + rand(0,10000);  //keepin busy
	}

	getpinfo(&a);
for(i = 0; i < 12; i++) {
      printf(1,"Process %d ticks is %d\n", i, a.tick[i]);
    }
	   //printf(1,"\n\n\n Process 2, with PID: %d, ran for %d ticks. \n",a.pid[4],a.tick[4]);	


      pid2 = fork();
      if(pid2==0)
       {
        settickets(10);
	//settickets(10);
        int stuff = 100;
         
          
          int j;
         for (j=0;j<stuff*10000;j++)
        {
          stuff = stuff + rand(0,10000);  //keepin busy
        }

      
	getpinfo(&a);
	   for(i = 0; i < 12; i++) {
      printf(1,"Process %d ticks is %d\n", i, a.tick[i]);
    }
	  //printf(1,"\n\n\n Process 3, with PID: %d, ran for %d ticks. \n",a.pid[5],a.tick[5]);
      }
      else
	{
           int stuff = 100;
         int l;
         for (j=0;j<stuff*10000;j++)
        {
          stuff = stuff + rand(0,10000);  //keepin busy
        } 

	   getpinfo(&a);
for(i = 0; i < 12; i++) {
      printf(1,"Process %d ticks is %d\n", i, a.tick[i]);
    }
           //printf(1,"\n\n\n Process 1, with PID: %d, ran for %d ticks. \n",a.pid[3],a.tick[3]);  
           

getpinfo(&a);

         int i;
    for(i = 0; i < 12; i++) {

      printf(1,"Process %d ticks is %d\n", i, a.tick[i]);
	//exit();
    }
	}

    }
wait();
    exit();
}
