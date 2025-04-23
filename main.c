#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parse.h"

#define MAX_NB_TOKENS 1000
#define MAX_TOKEN_LEN 50
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGUMENTS 50

// Function declaration
void clearT();

int main( int argc,char** argv) {
    //while (1) {
        //clearT();
        // Display prompt
        printf("my_shell> ");
//        fflush(stdout); // Flush stdout to ensure the prompt is displayed

        // Read user input


//    char input[MAX_INPUT_LENGTH];
  //      fgets(input, sizeof(input), stdin);

      //  printf("You entered: %s", input); // Print user input
    //}

char input[1000];
    printf("Enter a command: ");
    gets(input); 

    char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN];
    int token_count = tokenize(input, tokens);
    SimpleCommand command;
    CommandSequence sequence;


    //parse_simple_command(tokens, token_count, &command);
    parse(tokens,token_count,&sequence);


    printf("Tokens:\n");
    for (int i = 0; i < token_count; ++i) {
        printf("%s\n", tokens[i]);


    }
	printf("number of tokens %i\n", token_count);


	//Test of simple command
	//printf("program %s has %i args\n", command.program_name, command.nb_args);

	//Test of sequence of commands
	printf("Sequence of commands has %i commands\n", sequence.nb_cmds);


    return 0;
}


void clearT() {
    pid_t pid = fork();
    if (pid == 0) {
        if (execlp("clear", "clear", NULL) == -1) {
            perror("execlp");
            exit(1);
        }
    } else if (pid < 0) {
        perror("fork");
        exit(1);
    } else {

// Parent process: wait for the child to finish
        wait(NULL);
    }
}
