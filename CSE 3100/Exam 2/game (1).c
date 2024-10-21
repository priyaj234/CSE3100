#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
 
#define MAX 60

//read a character from a pipe
//the function returns the number of bytes read
int read_char(int pd, char *c)
{
	return read(pd, c , sizeof(char));
}

//write a character to a pipe
void write_char(int pd, char c)
{
        write(pd, &c, sizeof(char));
}

//read a string from a pipe
int read_string(int pd, char *buf, int max)
{
        return read(pd, buf , max);
}

//write a string to a pipe
void write_string(int pd, char *buf)
{
	write(pd, buf, strlen(buf) + 1);
}

//check whether all the letters are found in a word
int all_letters_found(char *word)
{
	for (int i = 0; i <= MAX; i++){
                if (word[i] != '-'){
                        return 1;
                }
        }
        return 0;
}

void run_game(char *word)
{
        int pd1[2];
        //pipe creation
        if(pipe(pd1) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd2[2];
        //pipe creation
        if(pipe(pd2) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid = fork();
        if(pid == 0)
        {
                close(pd1[0]);
                close(pd2[1]);
                
		char buf[MAX];
		strcpy(buf, word);
		for(int i = 0; i < strlen(buf); i++)
			buf[i] = '-';
 
                write_string(pd1[1], buf);

                char guess;

                close(pd2[1]);
                while(read_char(pd2[0], &guess)!=0)
                {
                        printf("%c\n", guess);
			for(int i = 0; i <= strlen(word); i++){
                                if (word[i] == guess){
                                        buf[i] = guess;
                                }
                        }

                }
		close(pd1[1]);
                close(pd2[0]);


        }

        close(pd1[1]);
        close(pd2[0]);

        char buf[MAX];
        read_string(pd1[0], buf, MAX);
	char guess = 'a';
        while(!all_letters_found(buf))
        {
                printf("%s\n", buf);
		write_char(pd2[1], guess);
                read_string(pd1[0], buf, MAX);
		

        }
        printf("%s\n", buf);
	close(pd1[0]);
        close(pd2[1]);

	
	
	
}

int main(int argc, char *argv[])
{
        if(argc != 2)
        {
                printf("Usage: %s word\n", argv[0]);
                return 0;
        }
	char word[MAX];
	strcpy(word, argv[1]);
	assert(strlen(word) < MAX);
	for(int i = 0; i< strlen(word); i++)
		word[i] = tolower(word[i]);
        run_game(word);
        return 0;
}
