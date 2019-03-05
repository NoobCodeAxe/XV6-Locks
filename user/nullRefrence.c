#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(void)
{
  int* p;
  p=0;
  printf(1,"%p\n",p);
  *p = 100;
  printf(1,"%p\n", *p);
  exit();

}
