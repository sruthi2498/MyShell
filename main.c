#include "all_include.h"


int main(){
	InitCommand();
	InitSimpleCommand();

	int ret;

	ret=insertArgument("ls");
	ret=insertArgument("-l");
	ret=insertArgument(NULL);

	ret=InsertSimpleCommand(CurrentSimpleCommand);

	InitSimpleCommand();
	ret=insertArgument("mkdir");
	ret=insertArgument("test");
	ret=insertArgument(NULL);

	ret=InsertSimpleCommand(CurrentSimpleCommand);

	DisplayCommand();

	execute();

}