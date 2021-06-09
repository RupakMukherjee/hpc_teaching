/*
pgcc -acc -ta=tesla -Minfo=accel -I/home/rupakm/gkylsoft/gkylzero/include app_loop_test_2.c -o app_loop_test -L/home/rupakm/gkylsoft/gkylzero/lib -lm -lgkylzero; ./app_loop_test
*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "openacc.h"

#include <gkylzero.h>
#include <gkyl_array.h>
#include <gkyl_range.h>

void foo(const struct gkyl_range *);

int main(int argc, char **argv) {
  int shape[] = {100,100};
  struct gkyl_range range;
  gkyl_range_init_from_shape(&range, 2, shape);

  foo(&range);
}

void
foo(const struct gkyl_range *update_range)
{
  int ng = 2;
  int nw = 3;
  int nv = 4;
  int N = ng*nw*nv;
  int x[N];
  int y[ng][nw][nv];
  printf("\n");

  #pragma acc data copyin(N) copyout(y)
  #pragma acc parallel loop gang worker num_gangs(ng) num_workers(nw) vector_length(nv)
  {
     for(int i=0;i<N;i++)
     {
       int gid = __pgi_gangidx();
       int wid = __pgi_workeridx();
       int vid = __pgi_vectoridx();
       x[i] = gid*(ng+1)*(nw+1) + wid*(nw+1) + vid;
       y[gid][wid][vid] = x[i];
       printf("%d %d %d %d %d \n",i,gid,wid,vid,x[i]);
     }
  }
  printf("\n");
  printf("%d %d ",y[ng-1][nw-1][nv-1],x[N-1]);
  printf("\n");
  printf("\n");
}
