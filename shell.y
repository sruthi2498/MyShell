%{

	#include <stdio.h>
	void yyerror(const char *);
	int yylex();
%}

%%
void yyerror(const char * p){
	printf("\nerror : %s\n",p);
}

int main(){
	if(!yyparse()){
			printf("\nParsed Successfully\n");
	}
	else printf("\nParsing Unsuccessful\n");
}