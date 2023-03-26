#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int len(char *s) {
  return strlen(s);
}

void lptoa(char *s, long *p) {
  long val = *p;
  sprintf(s,"%ld",val);
}

long longlen(long x) {
  long v;
  char buf[8];
  v = x;
  lptoa(buf,&v);
  return len(buf);
}

int main() {
  longlen(INT_MAX-1);
}