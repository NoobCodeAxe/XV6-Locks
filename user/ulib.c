#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "param.h"
#include "syscall.h"
#include "traps.h"
#include "fs.h"
#define PGSIZE 4096

char*
strcpy(char *s, char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, void *vsrc, int n)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}
//lock
int
lock_init(lock_t *lck)
{
	lck->flag = 0;
	return 0;
}
//get lock
void 
lock_get(lock_t *lck){
	while(xchg(&lck->flag, 1) != 0)
	    ;
}
//release lock
void 
lock_release(lock_t *lck){
	xchg(&lck->flag, 0);
}

int
thread_create(void (*start_routine)(void*), void *arg)
{
	//declare lock
	lock_t lck;
	lock_init(&lck);
	


	//get the lock

	lock_get(&lck);
	void *stack= malloc(PGSIZE*2);	
	

	//release
	lock_release(&lck);
	if((uint)stack % PGSIZE)
		stack = stack + (PGSIZE - (uint)stack % PGSIZE);

	int creatingReturn = clone(start_routine,arg,stack);
	return creatingReturn;

}
int
thread_join()
{
	void *stack = malloc(sizeof(void*));
	int creationReturn= join(&stack);

	//declare lock
	lock_t lck;
	lock_init(&lck);
	


	//get the lock

	lock_get(&lck);
	free(stack);	
	

	//release
	lock_release(&lck);
	
//free(stack); //we malloc we free

	return creationReturn;

}

