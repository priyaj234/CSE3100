#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//There will be m players in an array
typedef struct Player 
{
	int id;
	int loc;
	long balance;
} TPlayer;

//There will be n properties in an array
typedef struct Property
{
	int id;
	int owner_id;
	int rent;
} TProperty;


int transaction(TPlayer *p1, TPlayer *p2, int amount)
{

	if (p1 ->balance < amount){ //if the balance of the player is less than the rent pay all of player's money and game ends
		p2 ->balance += p1 ->balance;
		p1 ->balance = 0;
		return 0;
	}
	else { //pays rent if there are adequate funds
		p2 ->balance += amount;
		p1 ->balance -= amount;
		return 1;
	}

}

int one_round(int m, int n, TPlayer p[], TProperty prop[])
{
	for(int i = 0; i < m; i++)
	{
		int steps = rand() % 6 + 1 + rand() % 6 + 1;

		TPlayer *player = &p[i]; //creating a player


		if (p[i].loc + steps > n){ //adding n dollars to the player's balance if the go past the nth place
			p[i].balance += n;
		}
		p[i].loc = ((p[i].loc + steps) % n); // finding the spot of the board that the player will be at for the property transactions
		if (prop[p[i].loc].owner_id != -1 && prop[p[i].loc].owner_id != p[i].id){ //if the at a valid property and you're not the owner
			if((transaction(player, &p[prop[p[i].loc].owner_id], prop[p[i].loc].rent)) == 0) { //if the player doesn't have the funds to pay the rent the game ends
				return 0; 
			}
		}
		else{
			prop[p[i].loc].owner_id = p[i].id; //if the property doesn't have an owner the player becomes the owner
		}


	}
	return 1;
}

//used for printing out results
void print_result(int m, TPlayer p[])
{
	printf("      id    balance\n");
	for(int i = 0; i < m; i++)
	{
		printf("%8d %8ld\n", p[i].id, p[i].balance);
	}
	long sum = 0;
	long max = 0;
	for(int i = 0; i < m; i++)
	{
		sum += p[i].balance;
		if(p[i].balance > max) max = p[i].balance;
	}
	printf("average: %f max: %ld, max/average = %lf\n", (double)sum/m, max, (double)max*m/sum); 
}

//max_rounds is needed because the game may never finish
void monopoly(int m, int n, TPlayer p[], TProperty prop[], int max_rounds)
{
	srand(12345);
	int rounds = 1;
	while(one_round(m, n, p, prop) && rounds < max_rounds)
	{
        rounds ++;
	}

	print_result(m, p);
	printf("after %d rounds\n", rounds);
}

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		printf("Usage: %s m n rounds\n", argv[0]);
		return -1;
	}
	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	int rounds = atoi(argv[3]);
	assert(n >= 13);
	assert(m >= 1);
	assert(rounds >= 1);

	
	TPlayer p[m];
	TProperty prop[n];

	for(int i = 0; i < n; i++)
	{
		prop[i].id = i;
		prop[i].owner_id = -1;
		prop[i].rent = i + 1;
	}

	for(int j = 0; j < m; j++)
	{
		p[j].id = j;
		p[j].loc = 0;
		p[j].balance = n;
	}
	monopoly(m, n, p, prop, rounds);
	return 0;	
}
