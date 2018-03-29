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

command_list : 
			  | command_list command_line
			 ;					

command_line: pipe_list io_modifier_list NEWLINE 		{
											/* Entire command read, Execute and Wait for next Command */
											printf("\nExecuting\n\n");
											//DisplayCommand();
											execute();
											InitCommand();
											prompt();
										}
			| NEWLINE  					{
											prompt();
										}	
			;
 
io_modifier_list: io_modifier_list io_modifier 
				| 
				; 

io_modifier : GREATGREAT WORD  {
		 						setOutFile($2,2);
		 						}
		 	| GREAT WORD     {
		 						setOutFile($2,1);
		 						}
		 	| GREATGREAT AMP WORD {
		 						setOutFile($3,2);
		 						}
		 	| GREATAMP WORD {
		 						setOutFile($2,1);
		 						}
		 	| LESS WORD 	{	//set input file
		 						setInFile($2);}
		 	;

pipe_list: pipe_list PIPE cmd_and_args  {
											/* Send simple command to Cmd Table and wait for more commands */
											 //printf("pipe_list -> PIPE ,  Pushing all args\n"); 
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);
											 c++;
											 //printf("c incremented in yacc \n%d\n",c);
											 //DisplayCommand();
		
											
											}
		 | cmd_and_args 				{
											 //printf("the first cmd, Pushing all args\n"); 
											 Send_all_args();
											 InsertSimpleCommand(CurrentSimpleCommand);
											 //c++;
											 //printf("c incremented in yacc \n%d\n",c);
											 //DisplayCommand();
										}
		 ;

cmd_and_args: WORD arg_list 			{
												//printf("\n arg_list gives New command , Pushing arg WORD %s  \n", $1);

			 									InitSimpleCommand();

												
												Insert_parsed_arg($1);
										}
			;

arg_list: arg_list WORD 				{
		 									printf("\n arg_list encounters argument, push arg WORD %s", $2);
		 									Insert_parsed_arg($2);
		 								}
		|								{
											Init_parsed_args();
										}
		;
 

%%
void yyerror(const char * p){
	printf("\nerror : %s\n",p);
}