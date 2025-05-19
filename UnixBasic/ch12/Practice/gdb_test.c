#include <stdio.h>

int main(void)
{
    int i, j=0;

    for (i=1; i<=100; i++)
    {
        j = j+i;
        printf("sub %d\n", j);
    }

    puts(" ");
    printf("sum %d\n", j);

    for (i=1; i<=100; i++)
    {
        if (i == 50)
        {
            puts("arrived a half");
            //i = 60;
        }
        if ( i%2 == 0) continue;
        printf("odd %d\n", i);
    }
    return 0;
}

