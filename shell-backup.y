%{

	#include <stdio.h>
	#include "all_include.h"
	void yyerror(const char *);
	int c = 0;
	int yylex();
	extern char yytext[];
%}

%union {
	char *string_val;
}

%token NEWLINE GREAT LESS GREATGREAT GREATAMP PIPE AMP NOTOKEN
%token <string_val> WORD 
%type <string_val> arg 

%%
P 	:                          

	|	command_line NEWLINE P {
								printf("valid %s\n",yytext);
								}
  	; 

command_line	: 	

				| command_line PIPE arg_list {
											printf("\nAccepted at arg pipe cmLine\n");
											//printf("command_line %s", $3);
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);

											DisplayCommand();
											printf("Executing");
											execute();
											//displayStack();
											

											 }
				| arg_list  				{
											//printf("command_line -> arg_list, Pushing all args\n"); 
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);
											 c++;
											 printf("c incremented in \n%d\n",c);
											DisplayCommand();
											
											//displayStack();
											printf("\nExecuting\n\n");
											execute();
											//prompt();
											//YYACCEPT;
											}
				;


arg_list 		: arg arg_list 				{
												printf("\narg_list->arg arg_list, pushing arg %s\n", $1	); 
												Insert_parsed_arg($1);
												}
		 		| arg 						{
		 									printf("\narg_list gives New command , Pushing arg %s  \n", $1);

		 									InitSimpleCommand();


		 									Init_parsed_args();
		 									Insert_parsed_arg($1);}
		 		;

arg 		 	: WORD 	
				;					


%%
void yyerror(const char * p){
	printf("\nerror : %s\n",p);
}
