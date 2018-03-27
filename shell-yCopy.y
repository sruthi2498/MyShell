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

%%

command_list :  command_list command_line 
			 ;					{
								printf("valid %s\n",yytext);
								}

command_line: pipe_list NEWLINE 		{
											printf("\nExecuting\n\n");
											execute();
										}
			| NEWLINE  
 

pipe_list: pipe_list PIPE cmd_and_args  {
											 printf("command_line -> arg_list, Pushing all args\n"); 
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);
											 c++;
											 printf("c incremented in yacc \n%d\n",c);
											 DisplayCommand();
											
											//displayStack();
											//printf("\nExecuting\n\n");
											//execute();
											//prompt();
											//YYACCEPT;
											}
		 | cmd_and_args 				{
											 printf("command_line -> arg_list, Pushing all args\n"); 
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);
											 c++;
											 printf("c incremented in yacc \n%d\n",c);
											 DisplayCommand();
										}
		 ;

cmd_and_args: WORD arg_list 			{
												printf("\narg_list->arg arg_list, pushing cmd WORD %s\n", $1); 
												Insert_parsed_arg($1);
										}
			;

arg_list: arg_list WORD 				{
		 									printf("\na rg_list gives New command , Pushing arg WORD %s  \n", $2);

		 									InitSimpleCommand();


		 									Init_parsed_args();
		 									Insert_parsed_arg($2);
		 								}
		|
		;
 

%%
void yyerror(const char * p){
	printf("\nerror : %s\n",p);
}
