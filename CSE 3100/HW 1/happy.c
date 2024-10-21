#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	int m = n;
	
	while (n != 1 && n != 4){ //will break loop if n is equal to one or four
		int sum = 0; //created the summing variable
		int first; // created the variable to square individual digits
		while (n > 0){ // as long as n is greater than 0 it will run the inner loop
			first = n % 10; //derives the first variable
			sum = sum + (first*first); //adds the square of the first variable to the sum
			n /=10;	//divides the original n to get the next digit in the n
		}
		n = sum; //the new number becomes the sum found
		printf("%d\n", n); //prints every n found before decided if the number was happy or not
	}

	






	if(n==1) printf("%d is a happy number.\n", m);
	else printf("%d is NOT a happy number.\n", m);
	return 0;
}