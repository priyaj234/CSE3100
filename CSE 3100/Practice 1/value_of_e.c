#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

//This is the function to generate a random number uniformly between 0 and 1.
double uniform_random()
{
  return drand48();
}

//In the following function, repeatadly call the function uniform_random(), keeping track of the 
//sum of random numbers generated, and stop when the sum exceeds 1. 
//Return the count of random numbers generated.

int count_n(){
  int count = 0;
  double sum = 0.000;
  while (sum < 1.000) {
    count += 1;
    sum = sum + uniform_random();
  }
  return count;
}



int main(int argc, char** argv){
  srand48(1551142124);
  int n = 2000000;
  unsigned int total = 0;
  for(int i = 0; i < n; i++){
    total += count_n();
  }
  double e = 1.0*total/n;

  printf("e: %.3f\n", e);
}
