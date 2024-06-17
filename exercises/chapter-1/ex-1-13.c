/*
Exercise 1-13. Write a program to print a histogram of the lengths of words in its input. It is
easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.
*/

#include <stdio.h>
#include <stdbool.h>

#define OUT 0
#define IN  1

#define MAX_WORD_LEN 10

int main() {
    int state = OUT;

    int lengths[MAX_WORD_LEN+1]; // frequency of word lengths
    for (int i = 0; i <= MAX_WORD_LEN; i++) lengths[i] = 0; // init array

    int len = 0; // word length

    int c;
    while ((c = getchar()) != EOF) {
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
            state = IN;
            len++;
        } else if (state == IN) {
            state = OUT;
            lengths[len]++;
            len = 0;
        }
    }

    printf("Lengths :\n");
    for (int k = 1; k <= MAX_WORD_LEN; k++) {
        printf("%2d (%2d) : ", k, lengths[k]);
        for (int j = 0; j < lengths[k]; j++) printf("#");
        printf("\n", lengths[k]);
    }
}
