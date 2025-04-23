#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

int tokenize(char* input, char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN]) {
    int token_count = 0;
    int token_length = 0;

    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] == ' ' || input[i] == '\t') {
            tokens[token_count][token_length] = '\0';
            token_count++;
            token_length = 0;
        } else {
            tokens[token_count][token_length] = input[i];
	token_length = token_length + 1;
        }
    }


    if (token_length > 0) {
        tokens[token_count++][token_length] = '\0';
    }

    return token_count;
}

 int parse_simple_command(char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN],int nb_tokens,SimpleCommand* command)
{
	if(nb_tokens<=0) {
	return -1;
	}

	command->nb_args=nb_tokens - 1; //store number of arguments 
	strcpy(command->program_name, tokens[0]); //store command name in prog


	if(nb_tokens > 1)
	{
		for(int i=0;i<command->nb_args;i++) {
			strcpy(command->args[i],tokens[i+1]);
		}
	}

	return nb_tokens;

}

int parse_compound_command(char tokens[MAX_NB_TOKENS][MAX_TOKEN_LEN],int nb_tokens,CompoundCommand* command)
{
	char str_or[]="||";
	char str_and[]="&&";
	bool isCompound = false;

	for(int i=0;i<nb_tokens;i++){
		if((strcmp(tokens[i],str_or)==0) || strcmp(tokens[i],str_and)==0){
		parse_simple_command(tokens,i,&command->cmd1);
		parse_simple_command(tokens+i+1,nb_tokens-i-1,&command->cmd2);
		if(strcmp(tokens[i],str_or) == 0)
			command->op = OPERATOR_OR;
		else
			command->op = OPERATOR_AND;
		isCompound = true;
		break;
		}
	}

	if(!isCompound){
		parse_simple_command(tokens, nb_tokens, &command->cmd1);
		command->op = -1;
	}

	return 0;



	}

int parse(char tokens[MAX_NB_ARGS][MAX_TOKEN_LEN], int nb_tokens, CommandSequence* command){
	int commandIndex = 0; //start
	command->nb_cmds = 0;
	command->in_parallel= false;

	for (int i = 0; i < nb_tokens; i++) {
        	if (strcmp(tokens[i], "&") == 0) {
            	command->in_parallel = true;
            	continue;
        }

        int j = i;
        while (j < nb_tokens && strcmp(tokens[j], ";") != 0) {
            j=j+1;
        }

        int numTokens = j - i;
        if (numTokens > 0) {
            if (parse_compound_command(tokens + i, numTokens, &command->cmds[commandIndex]) == -1) {
                return -1;
            }
            commandIndex++;
            command->nb_cmds++;
        }

        i = j; // Skip the separator token.
    }

    return 0;
}






