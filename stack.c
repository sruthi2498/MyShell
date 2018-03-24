#include "all_include.h"

void StackInit(){
	Top=0;
	stack=malloc(sizeof(char *)*STACK_SIZE);
	for(int i=0;i<STACK_SIZE;i++){
		stack[i]=malloc(sizeof(char)*STACK_ELEM_SIZE);
	}
}
int push(char * elem){
	//printf("\npushing %s\n",elem);
	if(Top==STACK_SIZE || Top<0)return 0;
	stack[Top]=elem;
	Top++;
	return 1;
}
int pop(char ** elem){
	if(Top<0 || Top==STACK_SIZE  )return 0;
	*elem=stack[Top-1];
	Top--;
	return 1;
}

void displayStack(){
	printf("\nSTACK from 0 to Top\n");
	for(int i=0;i<Top;i++){
		printf("%d->%s\n",i,stack[i]);
	}
}