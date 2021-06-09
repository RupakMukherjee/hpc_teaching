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

#include <gkylzero.h>
#include <gkyl_array.h>

int main(int argc, char **argv) {
//  int N = 200;
  int i, N = 200;
  float sum = 0;
  float a = 3.5f;
  struct gkyl_array *arrA = gkyl_array_new(GKYL_DOUBLE, 1, N);
  struct gkyl_array *arrB = gkyl_array_new(GKYL_DOUBLE, 1, N);  
  struct gkyl_array *arrC = gkyl_array_new(GKYL_DOUBLE, 1, N);

  double *arrAData = arrA->data;
  double *arrBData = arrB->data;
  double *arrCData = arrC->data;
  
  for (int i=0; i<N; ++i){
     arrAData[i] = 2.0f;
     arrBData[i] = 1.0f;
  }

#pragma acc data copyin(sum,arrAData[N],arrBData[N],arrCData[N]) copyout(sum,arrCData[N])
  {  
  #pragma acc parallel loop private(i)
//  #pragma acc parallel loop gang vector_length(128) 
//  #pragma acc loop vector	  
  #pragma acc loop reduction(+:sum)	  
    for (int i= 0; i<N; ++i) {
       arrCData[i] = a * arrAData[i] + arrBData[i];
       sum += (float)i; 
    }
  }

  printf("%f",arrCData[153]);
  printf("\n");
  printf("%f",sum);

  gkyl_array_release(arrA);
  gkyl_array_release(arrB);
  gkyl_array_release(arrC);
}
