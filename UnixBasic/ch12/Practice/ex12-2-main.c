/* ex12-2-main.c for makefile */

#include <stdio.h>

extern int add(int a, int b);
extern int sub(int a, int b);

int main(void) {
    int num1, num2, res;

    num1 = 10;
    num2 = 20;

    res = add(num1, num2);
    printf("%d + %d = %d\n", num1, num2, res);
    res = sub(num1, num2);
    printf("%d - %d =%d\n", num1, num2, res);

	return 0;
}
