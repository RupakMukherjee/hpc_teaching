/*

pgcc -acc -ta=tesla -Minfo=accel -I/home/rupakm/gkylsoft/gkylzero/include app_loop_test.c -o app_loop_test -L/home/rupakm/gkylsoft/gkylzero/lib -lm -lgkylzero

time ./app_loop_test

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

int main(int argc, char **argv) {
  const int ng    = 2;
  const int nw    = 3;
  const int nv    = 4;
  int N     = ng*nw*nv;

  float sum = 0;
  float a   = 0.5f;

  struct gkyl_array *arrA = gkyl_array_new(GKYL_DOUBLE, 1, N);
  struct gkyl_array *arrB = gkyl_array_new(GKYL_DOUBLE, 1, N);  
  struct gkyl_array *arrC = gkyl_array_new(GKYL_DOUBLE, 1, N);

  double *arrAData = arrA->data;
  double *arrBData = arrB->data;
  double *arrCData = arrC->data;
  
  for (int i=0; i<N; ++i){
     arrAData[i] = (float)i;
  }

#pragma acc data copyin(arrAData[N],arrBData[N],arrCData[N]) copyout(arrBData[N],arrCData[N])
  {  
  #pragma acc parallel loop gang worker num_gangs(ng) num_workers(nw) vector_length(nv) reduction(+:sum)	  
    for (int i= 0; i<N; ++i) 
    {
      if (i==0){
        arrBData[i] = arrAData[i+1];
      }
      else if (i == N-1){
        arrBData[i] = arrAData[i-1];
      }
      else{
        arrBData[i] = arrAData[i-1] + arrAData[i+1];
      }
      int gid     = __pgi_gangidx();
      int wid     = __pgi_workeridx();
      int vid     = __pgi_vectoridx();
      arrCData[i] = a * (gid*(ng+1)*(nw+1) + wid*(nw+1) + vid);
      sum         += arrCData[i];
      printf("%d %d %d %d \n",i,gid,wid,vid);
    }
  }

  printf("\n");
  for (int i= 0; i<N; ++i)
    printf("%d %f %f %f \n", i, arrAData[i], arrBData[i], arrCData[i]);
  
  printf("\n \n");
  printf("%f",sum);
  printf("\n \n");

  gkyl_array_release(arrA);
  gkyl_array_release(arrB);
  gkyl_array_release(arrC);
}
