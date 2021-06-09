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
#include <gkyl_range.h>


void foo_1(const struct gkyl_range *);
void foo_2(const struct gkyl_range *);
void foo_3(const struct gkyl_range *);
void foo_4(const struct gkyl_range *);
void foo_5(const struct gkyl_range *);
void foo_6(const struct gkyl_range *);
void foo_7(const struct gkyl_range *);
void foo_8(const struct gkyl_range *);

int main(int argc, char **argv) {
  int shape[] = {100,100};
  struct gkyl_range range;
  gkyl_range_init_from_shape(&range, 2, shape); 

  // foo_1(&range);
  // foo_2(&range);
  // foo_3(&range);
  // foo_4(&range);
  // foo_5(&range);
  // foo_6(&range);
  // foo_7(&range);
  foo_8(&range);
}

void
foo_1(const struct gkyl_range *update_range)
{
  
  struct gkyl_range_iter iter;
  gkyl_range_iter_init(&iter, update_range);
  
  while (gkyl_range_iter_next(&iter)) {
    
    long lidx = gkyl_range_idx(update_range, iter.idx);
    // printf("%d,%d: %ld\n", iter.idx[0], iter.idx[1], lidx); 
  }
}
// ******************************************** //
void
foo_2(const struct gkyl_range *update_range)
{
  long num = update_range->volume;
  
#ifdef _OPENACC
  int num_threads = 1;
  int thread_id = 0;
#else
  int num_threads = 1;
  int thread_id = 0;
#endif

  struct gkyl_range local_range = *update_range;
  gkyl_range_set_split(&local_range, num_threads, thread_id);
  
  struct gkyl_range_iter iter;
  gkyl_range_iter_init(&iter, &local_range);

  for (long i=0; i<num; ++i) {

   gkyl_range_iter_next(&iter);
    // printf("%d: %d %d\n", thread_id, iter.idx[0], iter.idx[1]);
    
  }

}
// ******************************************* //
void
foo_3(const struct gkyl_range *update_range)
{   
  int gangs  = 5;
  int gwidth = 1;
  int size   = gangs*gwidth;
  int *ids = malloc(sizeof(1*size));

  int i, N = 10;
  int x[N];

  for(int i=0;i<size;i++)
    ids[i] = 0;

#pragma acc data copyin(N) copyout(x)
#pragma acc parallel num_gangs(gangs) copyout(ids[0:size])
{
  ids[__pgi_gangidx()] = __pgi_gangidx();
#pragma acc loop  
  for(i=0; i<N; i++)
  {
    x[i] = i;
    printf("%d %d \n", x[i], ids[i]);
  }
   printf("\n");
}

}
// ******************************************* //
void
foo_4(const struct gkyl_range *update_range)
{
  int gangs  = 10;
  int gwidth = 10;
  int size   = gangs*gwidth;
  int *ids = malloc(sizeof(50*size));

  for(int i=0;i<size;i++)
    ids[i] = 0;

#pragma acc parallel num_gangs(gangs) copy(ids[0:size])
  {
    int place = __pgi_gangidx();
#pragma acc loop seq
    for (int i=0;i<10;i++ )
      ids[place*gwidth+i] = 14;
  }
  for (int i=0;i<size;i++)
    printf("%d ", ids[i]);
  printf("\n"); 
  printf("\n"); 
}
// ***************************************** //
void
foo_5(const struct gkyl_range *update_range)
{
  int gangs  = 10;
  int gwidth = 10;
  int size   = gangs*gwidth;
  int *ids   = malloc(sizeof(50*size));

  for(int i=0;i<size;i++)
    ids[i] = 0;

#pragma acc parallel num_gangs(gangs) copy(ids[0:size])
  {
    int place = __pgi_gangidx()*gwidth;
    #pragma acc loop
    for(int i=0;i<10;i++)
      ids[place+i] = 14;
  }  
  for (int i=0;i<size;i++)
    printf("%d ", ids[i]);
  printf("\n"); 
  printf("\n");  
}
// ***************************************** //
void
foo_6(const struct gkyl_range *update_range)
{
  int gangs  = 10;
  int gwidth = 10;
  int size   = gangs*gwidth;
  int *ids   = malloc(sizeof(50*size));

  for(int i=0;i<size;i++)
    ids[i] = 0;

#pragma acc parallel num_gangs(gangs) copy(ids[0:size])
  {
    int place = __pgi_gangidx();
    #pragma acc loop
    for(int i=0;i<10;i++)
      ids[place*gwidth+i] = 14;
  }  
  for (int i=0;i<size;i++)
    printf("%d ", ids[i]);
  printf("\n");
  printf("\n");
}
// ***************************************** //
void
foo_7(const struct gkyl_range *update_range)
{
  int gangs  = 10;
  int gwidth = 10;
  int size   = gangs*gwidth;
  int *ids   = malloc(sizeof(50*size));

  for(int i=0;i<size;i++)
    ids[i] = 0;

#pragma acc parallel num_gangs(gangs) copy(ids[0:size])
  {
    int place = __pgi_gangidx();
    #pragma acc loop worker
    for(int i=0;i<10;i++)
      ids[place*gwidth+i] = 14;
  }  
  for (int i=0;i<size;i++)
    printf("%d ", ids[i]);
  printf("\n");
  printf("\n");  
}
// ***************************************** //
void
foo_8(const struct gkyl_range *update_range)
{
  int gangs  = 5;
  int gwidth = 10;
  int gsize  = gangs*gwidth;

  #pragma acc parallel gang vector_length(10) copy(gsize)
  {
    int gid = __pgi_gangidx();
    int vid = __pgi_vectoridx();

    #pragma acc loop vector   
     for(int i=0;i<10;i++)
       printf("%d %d %d \n",i,gid, gsize);
       printf("%d %d \n", gid, gsize);
  }
  printf("\n");
}
