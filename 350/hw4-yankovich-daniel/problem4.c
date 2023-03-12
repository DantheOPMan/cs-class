#include <stdio.h>

long decode2(long x, long y, long z);
long decode3(long x, long y, long z);

int main() {
    long x = 1, y = 1, z = 12;
    printf("%ld\n", decode2(x,y,z));
    printf("%ld\n", decode3(x,y,z));
    return 0;
}

long decode2(long x, long y, long z) {
    y = y - z;
    x*=y;
    return ((y << 63) >> 63) ^ (x);
}
long decode3(long x, long y, long z) {
    y = y - z;
    x*=y;
    return (y)^(x);
}