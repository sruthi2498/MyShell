#include "all_include.h"


int main(){
	InitCommand();
	InitSimpleCommand();

	int ret;

	ret=insertArgument("ls");
	ret=insertArgument("-v");

	printf("returned %d\n",ret);
	ret=InsertSimpleCommand(CurrentSimpleCommand);

	DisplayCommand();

}