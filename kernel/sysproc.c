#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "syscall.h"
#include "pstat.h"
#include "proc.h"

extern int numOfCalls;

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
//return the number of system calls 
int
sys_howmanysys(void)
{
  return numOfCalls;
}

//set tickets
int
sys_settickets(void)
{
	int number;
	if(argint(0, &number) < 0)
	  return -1;
	if(number <=0){return -1;}
	else
	{
	proc->tickets=number;
	return 1;
	}
}

//extern ptable ptable;

int 
sys_getpinfo(void)
{
  struct pstat* a;
  if(argptr(0, (char**)&a, sizeof(struct pstat*)) < 0)
    return -1;
  /*struct pstat{
  int inuse[NPROC];
  int tickets[NPROC];
  int pid[NPROC];
  int tick[NPROC];
};*/
  struct proc *proca = getProcs();
  struct proc *p;
  int i;
  for(p = proca,i = 0; p < (proca+NPROC); p++,i++){
    a->inuse[i] = p->state==RUNNING;
    a->tickets[i] = p->tickets;
    a->pid[i]=p->pid;
    a->tick[i]=p->ticks;
  }
  
  return 1; //impement later
}

//extern int clone(void(*fcn)(void*), void *arg, void *stack);

int sys_clone(void) {
  void *fcn, *arg, *stack;

  if(argptr(0, (void *)&fcn, sizeof(void *)) < 0)
    return -1;

  if(argptr(1, (void *)&arg, sizeof(void *)) < 0)
    return -1;

  if(argptr(2, (void *)&stack, sizeof(void *)) < 0)
    return -1;

  if ((uint)stack % PGSIZE != 0)
    return -1;

  if ((uint)proc->sz - (uint)stack == PGSIZE/2)
    return -1;

  return clone(fcn, arg, stack);
}

int sys_join(void) {
  void **stack;

  if(argptr(0, (void *)&stack, sizeof(void *)) < 0)
    return -1;

  int rt = join(stack);
  return rt;
}
