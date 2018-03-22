
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard Spaces and Tabs */
     	}	

">" 	{
		return GREAT;
	}

[^ \t\n][^ \t\n]*  {
		/* Assume that file names only have alpha chars */
		yylval.string_val=strdup(yytext);
		return WORD;
	}

.	{
		/* Invalid character in input */
		return NOTOKEN;
	}

%%
	
