#include <stdio.h>
#include <stdlib.h>


double two_d_random(int n)
{	
	int steps[(2*n) + 1][(2*n) + 1];

	for (int a = 0; a < ((2*n) + 1); a++){
		for (int b = 0; b < ((2*n)+1); b++){
			steps[a][b] = 0;
		}
	}

	int x = 0;
	int y = 0;

	while ((x != n) && (x != -n) && (y != n) && (y != -n )){

		if (steps[x + n][y + n] == 0) {
			steps[x + n][y + n] = 1;
		}

		int r = rand () % 4;
	
		if (r == 0) {y = y + 1;}
		if (r == 1) {x = x + 1;}
		if (r == 2) {y = y - 1;}
		if (r == 3) {x = x - 1;}

	}


	int counter = 0;

	for (int a = 0; a <= ((2*n)); a++){
			for (int b = 0; b <= ((2*n)); b++){
				if (steps[a][b] == 1) {
					counter = counter + 1;
				}
		}
	}

	return (double) counter/(((2*n)-1)*((2*n)-1));
}

//Do not change the code below
int main(int argc, char* argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}