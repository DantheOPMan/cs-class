#include <stdio.h>

int divide_power2(int x, int k);

int main(int argc,char **argv) {
    int x = 24, k = 3;
    printf("%d divided by 2^%d is %d\n", x, k, divide_power2(x, k));
}

int divide_power2(int x, int k) {
    return (x + ((1 << k) - 1 & (x >> (sizeof(int) << 3 - 1)))) >> k;
}