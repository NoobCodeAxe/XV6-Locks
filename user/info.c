#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	pid_t pid;
	pid = fork();
	if(pid<0){return -1;}
	else if(pid>0)
	{
	     
	}
	else
	{
	  settickets(23);
	  
	  wait();
	  exit(); 
	}
	
}
