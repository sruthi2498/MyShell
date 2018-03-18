#include "all_include.h"


int main(){
	InitCommand();
	CurrentSimpleCommand=InitSimpleCommand();

	int ret;

	ret=insertArgument("ls");

	printf("returned %d\n",ret);
	ret=insertSimpleCommand(CurrentSimpleCommand);

	DisplayCommand();

}