#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void reality_1_example_1();
void reality_1_example_2();
void reality_3();
double fun();

typedef struct {
  float a[8];
  int d;
} struct_t;

int main(int argc,char **argv) {
  int n;			/* used to loop for reality_3() */

  reality_1_example_1();
  reality_1_example_2();

  if (argc==1) n = 20;		/* default 5 iter */
  else n = atoi(argv[1]);
  reality_3(n);

  return 0;
}

void reality_1_example_1(){
  float f=50000;
  int i=40000;

  /* fill here */
  printf("reality_1_example_1_float: f=%f\n", f);
  printf("f*f=%f",(f * f));
  if(f*f>=0){
    printf(">= 0\n\n");
  }else{
     printf("< 0\n\n");
  }
  
  printf("reality_1_example_1_int: i=%i\n",i);
  printf("i*i=%i",(i * i));
  if(i*i>=0){
    printf(">= 0\n\n");
  }else{
    printf("< 0\n\n");
  }

  i=50000;

  /* fill here */
  printf("reality_1_example_1_int: i=%i\n",i);
  printf("i*i=%i",(i * i));
  if(i*i>=0){
    printf(" >= 0\n\n");
  }else{
    printf(" < 0\n\n");
  }

}

void reality_1_example_2(){
  double fx=1e20,fy=-1e20,fz=3.14;
  unsigned int uix=12,uiy=34,uiz=56;
  int six=12,siy=34,siz=56;

  /* fill here */
  printf("reality_1_example_2_unsigned: uix=%u uiy=%u uiz=%u\n",uix,uiy,uiz);
  printf("((uix+uiy)+uiz)=%u",((uix+uiy)+uiz));
  if(((uix+uiy)+uiz) == (uix+(uiy+uiz))){
    printf(" == ");
  }else{
    printf(" != ");
  }
  printf("(uix+(uiy+uiz))=%u\n\n",(uix+(uiy+uiz)));


  printf("reality_1_example_2_signed: six=%d siy=%d siz=%d\n",six,siy,siz);
  printf("((six+siy)+siz)=%d",((six+siy)+siz));
  if(((six+siy)+siz) == (six+(siy+siz))){
    printf(" == ");
  }else{
    printf(" != ");
  }
  printf("(six+(siy+siz))=%d\n\n",(six+(siy+siz)));


  printf("reality_1_example_2_float: fx=%e fy=%e fz=%e\n\n",fx,fy,fz);
  printf("((fx + fy) + fz)=%e",(fx * fy * fz));
  if((fx * fy * fz) == (fz * fy * fx)){
    printf(" == ");
  }else{
    printf(" != ");
  }
  printf("(fx + (fy + fz))=%e\n\n",(fz * fy * fx));

}

void reality_3(int n) {
  double d;
  int i;

  /* fill here */
  printf("reality_3: n=%d iterations\n",n);
  for(i=0; i<=n; i++){
    d = fun(i);
  }
}

double fun(int i){
  volatile struct_t s;

  s.d = 3.14;
  s.a[i] = 1073741824;
  printf("fun(%d) -> %d\n",i,s.d);  

  return s.d;
}

/* End of file */