#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;
	//TODO
	for (int i = 0; i <= n; i++) { //initializes loop at i = 0 and will run loop while it is lesser than or equal to n, i increments by 1 every loop
		int pow = 1; //intializes power variable
		for (int x = 1; x <= i; x++){ //for as many times as i loops this loop will also loop and multiple the power by 16
			pow *= 16;}
			
		pi = pi + (((4.0/((8.0*i)+1.0))-(2.0/((8.0*i)+4.0))-(1.0/((8.0*i)+5.0))-(1.0/((8.0*i)+6.0))) * (1.0/pow)); //math for summation
			
		}
	
	







	printf("PI = %.10f\n", pi);
	return 0;
}