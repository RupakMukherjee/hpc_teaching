/*
pgcc -acc -ta=tesla -Minfo=accel app_loop_test_3.c -o app_loop_test && ./app_loop_test
*/
#include <stdio.h>
#include "openacc.h"

void main() {
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
  return 0;
}
