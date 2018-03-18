%{

	#include <stdio.h>
	#include "all_include.h"
	void yyerror(const char *);
	int yylex();
%}

%union {
	char *string_val;
}

%token NEWLINE GREAT LESS GREATGREAT GREATAMP PIPE AMP NOTOKEN
%token <string_val> WORD 
%type <string_val> arg


%%
P 	: command_line NEWLINE 
  	|
  	; 

command_line	: arg_list PIPE command_line	
				| arg_list  				{printf("command_line -> arg_list, Pushing all args\n"); 
											 Send_all_args();
											 YYACCEPT;}
				;

arg_list 		: arg arg_list 				{printf("arg_list->arg arg_list, pushing argu %s\n", $1	); Insert_parsed_arg($1);}
		 		| arg 						{printf("arg_list gives New command , Pushing arg %s  \n", $1);
		 									InitSimpleCommand();
		 									printf("between");
		 									Init_parsed_args();
		 									Insert_parsed_arg($1);}
		 		;

arg 		 	: WORD 	
				;					


%%
void yyerror(const char * p){
	printf("\nerror : %s\n",p);
}
