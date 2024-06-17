#include <stdio.h>
#include <stdlib.h>

int bitcount(unsigned int num) {
    int count = 0;
    while (num) {
        num &= num - 1; // removes the rightmost bit. Example: 0b00111010 -> 0b00111000
        count++;
    }
    return count;
}

int main(int argc, char *argv[]) {
    if (argc >= 1) {
        printf("%d has bitcount %d\n", atoi(argv[1]), bitcount(atoi(argv[1])));
    }
    return 0;
}