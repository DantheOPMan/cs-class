#include <stdio.h>

long unknown(unsigned long x) {
    if (x == 0)
	    return 0;

    unsigned long nx = x >> 1;
    long rv = unknown(nx);
    return rv + ((1^x)& 1);
}

int main() {
    printf("%ld\n", unknown(31));
    printf("%ld\n", unknown(-31));
    return 0;
}