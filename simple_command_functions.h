void InitSimpleCommand();
	//-> construct simple empty command

int insertArgument( char * argument ); 
        // ->  2inserts a new argument  into the SimpleCommand 
        // -> enlarges the _arguments array if necessary
        // -> It also makes sure  that the last element is NULL since that is required for the exec() system call. 

		// 0 if it fails, 1 if its a success 