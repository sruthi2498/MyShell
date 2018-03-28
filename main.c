#include "all_include.h"


int main(){
	StackInit();
	InitCommand();

	
	Prompt=malloc(sizeof(char)*PROMPT_SIZE);
	strcpy(Prompt,"hash:~");
	prompt();
	// int a=0;
	// while(a!=-1){
	// 	a=pressed_arrow();
	// 	if(HistoryPointer==0){
	// 		printf("no command");
	// 	}
	// 	else{
	// 		if(a==1){
	// 			//up
	// 			HistoryPointer--;

	// 			//printf("HistoryPointer %d stackelem %s",HistoryPointer,stack[HistoryPointer].command);
	// 		}
	// 		else if(a==2){
	// 			//down
	// 			HistoryPointer++;

	// 			//printf("HistoryPointer %d stackelem %s",HistoryPointer,stack[HistoryPointer].command);
	// 		}
	// 	}
	// 	yyparse();
	// }
	if(!yyparse()){
			//printf("\nParsed Successfully\n");

	} 
	

}