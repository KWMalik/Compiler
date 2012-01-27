#include <stdio.h>
#include <debug.h>
#include <string.h>
#include <fsm.h>
#include <regex_to_fsm.h>

/* Arguments :-
 * 	arg1 : <tokens_list_file> 
 *	arg2 : <input_file>
 */

#define MAX_TOKENS 20
#define MAX_TOKEN_LENGTH 50
#define MAX_LINE_LENGTH 100
#define MAX_FILENAME 50

char tokens[MAX_TOKEN_LENGTH][MAX_TOKENS];
int n_tokens = 0;
fsm_t token_NFA[MAX_TOKENS];

void read_tokens (FILE *fp);


int main (int argc, char *argv[])
{	
	char token_filename[MAX_FILENAME];

	strncpy (token_filename, argv[1], MAX_FILENAME);

	FILE * fp ;
	fp = fopen (token_filename, "r");

	if ( !fp )
	{
		perror ("fopen : ");
		exit(3);
	}
	fprintf (stderr, "Going to tokenize and form NFAs\n");

	// Reading tokens
	read_tokens (fp);
}

void read_tokens (FILE *fp)
{
	

	char line[MAX_LINE_LENGTH];
	char *token, *regex;
	while ( 1 )
	{
		fgets (line, MAX_LINE_LENGTH - 1, fp);
		
		if (strlen (line) == 0 && feof(fp))
		{
			break;
		}

		regex = strtok (line, "\t");
	
		fprintf (stderr, "REGEX : %s\n", regex);
		
		// Get the token name 
		token = strtok (NULL, "\t");
		fprintf (stderr, "TOKEN : %s\n", token);
		
		strncpy (tokens[n_tokens], regex, MAX_TOKEN_LENGTH);

		fprintf (stderr, "About to generate NFA\n", token);
		// Generate NFA.
		create_NFA ( token_NFA + n_tokens, regex);
		fprintf (stderr, "Generated NFA\n", token);


	}
}
