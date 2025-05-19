/* main.c for Makefile */
#include <stdio.h>
extern int addnum(int a, int b);

int main(void) {
    int sum;

    sum = addnum(1, 100);
    printf("Sum 1~100 = %d\n", sum);

    return 0;
}
