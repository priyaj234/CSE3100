#include <stdio.h>

int main(void)
{
    printf("Hello, World!\n");

    int n = 0;
    int x = 0;
    while (n < 200){
        if (n % 2 == 0){
            x = x + n;
        }
        n++;
    }
    printf("%d", x);
    return 0;
}