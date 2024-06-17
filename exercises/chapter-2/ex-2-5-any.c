#include <stdio.h>

int any(char s1[], char s2[]) {
    int i, j;
    int match = 0;

    for (i = 0; s1[i] != '\0' && !match; i++)
        for (j = 0; s2[j] != '\0' && !(match = (s1[i] == s2[j])); j++);;
    return (match) ? i-1 : -1;
}

int main(int argc, char *argv[]) {
    if (argc >= 2)
        printf("%s %s matched at %d\n", argv[1], argv[2], any(argv[1], argv[2]));
    return 0;
}
