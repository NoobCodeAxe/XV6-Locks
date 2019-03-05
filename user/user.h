#ifndef _USER_H_
#define _USER_H_

struct pstat;
struct stat;
typedef struct __lock_t{
	uint flag;
}lock_t;
// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int howmanysys(void);
int uptime(void);
int settickets(int);
int getpinfo(struct pstat *);
int clone(void(*fcn)(void*),void *arg, void*stack);
int join(void **stack);

// user library functions (ulib.c)
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int thread_create(void (*start_routine)(void*), void *arg);
int thread_join();
int lock_init(lock_t *lck);
void lock_acquire(lock_t *lck);
void lock_release(lock_t *lck);
#endif // _USER_H_

