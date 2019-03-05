#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat{
  int inuse[NPROC];
  int tickets[NPROC];
  int pid[NPROC];
  int tick[NPROC];
};

#endif // _PSTAT_H
