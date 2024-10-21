// Only this line of comment is provided 
#include <stdio.h>

int main(void)
{
    double x;
    double total;
    double average;
    int count = 0;

    while (scanf("%lf", &x) == 1){
        total += x;
        count += 1;
        average = total/count;
        printf("Total=%f Average=%f\n", total, average); 

    }
    return 0;
}