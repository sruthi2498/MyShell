#include "all_include.h"

void StackInit(){
	Top=0;
	HistoryPointer=0;
	for(int i=0;i<STACK_SIZE;i++){
		stack[i].command=malloc(sizeof(char)*STACK_ELEM_SIZE);
	}
}
int push(struct stack_elem elem){
	//printf("\npushing %s\n",elem);
	if(Top==STACK_SIZE || Top<0)return 0;
	stack[Top]=elem;
	HistoryPointer=Top;
	Top++;
	return 1;
}
int pop(struct stack_elem * elem){
	if(Top<0 || Top==STACK_SIZE )return 0;
	*elem=stack[Top-1];
	HistoryPointer=Top;
	Top--;
	return 1;
}

void displayStack(){
	int space=10;
	printf("\nCommand Time PID\n");
	for(int i=Top-1;i>=0;i--){
		printf("%d : %s",i,stack[i].command);
		printf("%*s",space,stack[i].time_str);
		printf("%*d\n",space,stack[i].pid);
		//printf("%d : %s%10s%s%10s%d\n",i,stack[i].command,stack[i].time_str,stack[i].pid);
	}
}