#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
void letter_counts(char a[], int n, int counts[26])
{
    //counts[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}
    for(int i = 0; i < n; i++){
        for (int j=0; j < 26; j++){
           if (a[i] == j) {
            counts[j]++;
           }
        }

    }

}

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s n\n", argv[0]);
        return -1;
    }
    int n = atoi(argv[1]);
    printf("n=%d\n", n);
    assert(n >= 1 && n <= 10000);

    char a[n];
    int sum = 0;
    for(int i=0; i<n; i++)
    {
        sum += 2*i +1;
        a[i] = sum % 26 + 97;
    }

    int counts[26];
    letter_counts(a, n, counts);
    for (int p=0; p < 26; p++){
        printf("%d\n", counts[p]);
    }


    return 0;
}