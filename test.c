#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    int max = 5;
    for (int c = 0; c < max; c++)
    {
        num = rand();
        printf("%d\n", num);
    }
    return 0;
}