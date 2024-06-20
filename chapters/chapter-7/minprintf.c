#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...) {
    va_list ap; // arg pointer
    char *p; // pointer to fmt
    char *sval; // string value
    int ival; // integer value
    double dval; // double value

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
            case 's':
                for (sval = va_arg(ap, char*); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }
}