#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>

#define NNN 2048

void copyij();
void copyji();
void init_mat();
int64_t time_diff();

int src[NNN][NNN], dst[NNN][NNN];

int main(int argc,char **argv) {

  int i,j,n;
  
  long int del_sec,del_msec;
  struct timeval tv_s,tv_e;

  init_mat();
  gettimeofday(&tv_s, NULL); 
  copyij();
  gettimeofday(&tv_e, NULL); 

  /* fill here to compute elapsed time */
  del_sec = tv_e - tv_s;
  printf("copyij(): dim=%d: elapsed=%ld.%03ld secs\n",NNN,del_sec,del_msec/1000);


  init_mat();
  gettimeofday(&tv_s, NULL); 
  copyji();
  gettimeofday(&tv_e, NULL); 

  /* fill here to compute elapsed time */

  printf("copyji(): dim=%d: elapsed=%ld.%03ld secs\n",NNN,del_sec,del_msec/1000);

  return 0;
}

void copyij(){
  int i,j;

  /* fill here */

}

void copyji(){
  int i,j;

  /* fill here */

}

void init_mat(){
  int i,j;

  for (i=0;i<NNN;i++)
    for (j=0;j<NNN;j++) src[i][j] = dst[i][j] = 1;

}