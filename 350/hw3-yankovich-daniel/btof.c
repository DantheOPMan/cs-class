#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define LEN 32
#define EXP_32 8
#define MAN_32 9		


float string_to_float(const char *s) {
  unsigned int u_int = 0;
  int i;
  int sign = (s[0] == '1') ? -1 : 1;
  int exponent = 0;
  float significand = 0;
  int base = 1;

  /* extract exponent */
  for (i=EXP_32; i>0; i--) {
    if (s[i] == '1') {
      exponent += base;
    }
    base *= 2;
  }

  /* extract significand */
  base = 0.5;
  for (i=MAN_32; i<LEN; i++) {
    if (s[i] == '1') {
      significand += base;
    }
    base /= 2;
  }

  /* calculate float */
  float f = sign * pow(2, exponent-127) * (1 + significand);

  return f;
}

int main(int argc, char **argv) {
  float f = string_to_float(argv[1]);
  printf("%.15f\n", f);
  return 0;
}
