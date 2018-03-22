/*
* shell.l: simple lexical analyzer for the shell.
*/
%{
	#include <string.h>
	#include "all_include.h"
	#include "y.tab.h"
	void yyerror(const char *);
%}
%%
\n 		{	InitCommand();
			prompt();
			return NEWLINE; }
[ \t] 	{ /* Discard spaces and tabs */}
">" 	{return GREAT;}
"<" 	{return LESS;}
">>" 	{return GREATGREAT;}
">&" 	{return GREATAMP;}
“|” 	{return PIPE;}
“&” 	{return AMP;}
[^ \t\n][^ \t\n]* {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;}
. 		{ 
		return NOTOKEN;
		}
%%