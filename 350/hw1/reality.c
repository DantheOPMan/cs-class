#include <stdio.h>
#include <stdlib.h>

void reality_1_example_1();
void reality_1_example_2();
void reality_3();
double fun();

typedef struct {
  int a[2];
  double d;
} struct_t;

int main(int argc,char **argv) {
  int n;			/* used to loop for reality_3() */

  reality_1_example_1();
  reality_1_example_2();

  if (argc==1) n = 5;		/* default 5 iter */
  else n = atoi(argv[1]);
  reality_3(n);

  return 0;
}

void reality_1_example_1(){
  float f=50000;
  int i=40000;

  /* fill here */
  printf((i * i), "\n");

  i=50000;

  /* fill here */
  printf((i * i), "\n");

}

void reality_1_example_2(){
  float fx=1e20,fy=-1e20,fz=3.14;
  unsigned int uix=12,uiy=34,uiz=56;
  int six=12,siy=34,siz=56;

  /* fill here */
  printf(((fx + fy) + fz), "\n");
  printf((fx + (fy + fz)), "\n");
}

void reality_3(int n) {
  double d;
  int i;

  /* fill here */

}

double fun(int i){
  volatile struct_t s;

  s.d = 3.14;
  s.a[i] = 1073741824;
  printf("fun(%d) -> %f\n",i,s.d);  

  return s.d;
}

/* End of file */