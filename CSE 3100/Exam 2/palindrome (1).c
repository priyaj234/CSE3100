#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h> 
#include <fcntl.h>
#include <string.h> 
#include <sys/stat.h>

#define MAX 60                //each word is less than 60 letters

//test whether a word is a palindrome
int palindrome(const char *word)
{
	//TODO
	//fill in the code below
    char temp[MAX];
    strcpy(temp, word);

    char check[MAX];
	strcpy(check, temp);
	strtok(check," ");
	strtok(temp, " ");

	//was not able to finish actual reversal process


	for(int i = 0; i <= MAX; i++){
		if (temp[i] != check[i]){
			return 0;
		}
		return 1;
	}

}

int main()
{
	int fd_dict = open("dict.txt", O_RDONLY);
	if(fd_dict < 0)
	{
		printf("Error opening the file\n");
		return -1;
	}

	dup2(fd_dict, 0);
	scanf(0);




	
	//Make sure when the file is created, the user has the read and write access 
	int fd = open("palindrome.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); 
	if(fd < 0)
	{ 
		printf("Error opening the file\n");
		return -1;
	} 

	
	dup2(fd, 1);
	


	//Do not change the code below
        char word[MAX];
        while(scanf("%s\n", word)!=EOF)
		if(palindrome(word)) printf("%s\n", word);

	return 0;
}
