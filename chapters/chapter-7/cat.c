#include <stdio.h>

void filecopy(FILE *src, FILE *dest) {
    int c;
    while ((c = getc(src)) != EOF) putc(c, dest);
}

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc == 1) {
        filecopy(stdin, stdout);
    } else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("Error : cant open file %s\n", *argv);
                return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }

    return 0;
} 

