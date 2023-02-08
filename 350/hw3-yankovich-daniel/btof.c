#include <math.h>
#include <stdio.h>
#include <string.h>

float binary_to_float(const char *input) {
    int sign = (input[0] == '0') ? 1 : -1;
    int exponent = 0;
    for (int i = 2; i <= 9; i++) {
        exponent += pow(2, 9 - i) * (input[i] - '0');
    }
    exponent -= 127;
    float mantissa = 1.0;
    for (int i = 11; i < 34; i++) {
        mantissa += pow(2, -(i - 10)) * (input[i] - '0');
    }
    return sign * pow(2, exponent) * mantissa;
}

int main(int argc, char *argv[]) {
    printf("%f\n", binary_to_float(argv[1]));
    return 0;
}
