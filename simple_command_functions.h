struct SimpleCommand InitSimpleCommand();
	//-> construct simple empty command

void insertArgument( char * argument ); 
        // ->  inserts a new argument  into the SimpleCommand 
        // -> enlarges the _arguments array if necessary
        // -> It also makes sure  that the last element is NULL since that is required for the exec() system call. 