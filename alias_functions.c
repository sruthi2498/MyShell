#include "all_include.h"

counter=0;

struct  Aliastruct getAlias(char * cur_command){
	//DisplayAlias();
	//printf("in get alias command : %s\n",cur_command);
	int i;
	struct Aliastruct NoAlias;
	NoAlias.aliasname=malloc(sizeof(char) * (20) );
	NoAlias.command=malloc(sizeof(char) * (20) );

	for(i=0;i<counter;i++)
	{
		//printf("i=%d\n",i);
		if(strcmp(AliasTable[i].aliasname,cur_command)==0)
			return AliasTable[i];
	}

	strcpy(NoAlias.aliasname,"Nonexistent");
	strcpy(NoAlias.command," ");
	//printf("returning from getlias\n");
	return NoAlias;

}

void setAlias(char * alias, char * command)
{	
	//printf("IN set alias : alias %s command %s\n",alias,command);

	struct Aliastruct temp;
	temp=AliasInit();
	temp.aliasname=alias;
	temp.command=command;
	//printf("Alias name : %s\tCommand : %s\n",temp.aliasname,temp.command);
	AliasTable[counter]=temp;
	counter++;
	DisplayAlias();
	return;	
}

void DisplayAlias(){
	struct Aliastruct t;
	for(int i=0;i<counter;i++){
		t=AliasTable[i];
		printf("Alias name : %s\tCommand : %s\n",t.aliasname,t.command);
	}
}

struct  Aliastruct AliasInit()
{
	AliasTable[counter].aliasname=malloc(sizeof(char) * (20) );
	AliasTable[counter].command=malloc(sizeof(char) * (20) );
	
	return AliasTable[counter];


}