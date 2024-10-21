#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void one_particle(int *grid, int n)
{
	int x = 0; //initializing all of the coordinates to origin and creating an empty index value
	int y = 0;
	int z = 0;
	int index;


	for (int i = 0; i < n; i++){ //making n moves
		int r = rand() % 6;

		if (r == 0) {x = x - 1;} //determining what direction each move is
		if (r == 1) {x = x + 1;}
		if (r == 2) {y = y + 1;}
		if (r == 3) {y = y - 1;}
		if (r == 4) {z = z - 1;}
		if (r == 5) {z = z + 1;}

		

	}
	index = ((x+n) + ((y+n)*(2*n+1)) + ((z+n)*(2*n+1)*(2*n+1))); //creating the index for the number of moves

	grid[index] += 1; //adds one to that index if thats the final point


}


double density(int *grid, int n, double r)
{
	double total = 0.0; //creating variable for all of the possible points
	double sum = 0.0; //creating variable for the sum of the points visited
	for (int x = -n; x <= n; x++){ //next three lines iterate through each coordinate
		for (int y = -n; y <= n; y++){
			for (int z = -n; z <= n; z++){
				total = total + grid[((x+n) + ((y+n)*(2*n+1)) + ((z+n)*(2*n+1)*(2*n+1)))]; ///creates all of the total points
				if (((x*x)+(y*y)+(z*z)) <= ((r*r) * (n*n))) {
					sum = sum + grid[((x+n) + ((y+n)*(2*n+1)) + ((z+n)*(2*n+1)*(2*n+1)))]; ///if within possible distance visted point gets added
				}
			}
		}
	}
	return (double) (sum/total); //returns fraction of visited points and total possible points


    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}


void diffusion(int n, int m)
{
	//fill in a few line of code below
	int* grid = calloc((((2*n) + 1)*((2*n) + 1)*((2*n)+1)), sizeof(int)); //allocate memory

	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	free(grid); //free the memory


}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
