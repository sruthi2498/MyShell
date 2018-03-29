execute(){
	
	//save in/out
	int tmpin = dup(0);
	int tmpout = dup(1);

	//InFile Saved in CurrentCommand structure
	//Set fdin
	int fdin;
	if(CurrentCommand._inputFile){
		fdin = open(CurrentCommand._inputFile, O_READ);
	}
	else{
		//use default input
		fdin=dup(tmpin);
	}

	int ret;
	int fdout;

	for(i=0; i<CurrentCommand._numberOfSimpleCurrentCommands;i++){

		//stdin redirected to fdin
		dup2(fdin,0);
		close(fdin);

		if(i == (CurrentCommand._numberOfSimpleCommands - 1)){
			//Last simple CurrentCommand
			if(outfile){
				fdout = open(CurrentCommand._outFile, O_RDWR);
			}
			else{
				fdout = dup(tmpout);
			}
		}
		else{
			//not last simple CurrentCommand
			//Create a pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}
		//redirect output
		dup2(fdout,1);
		close(fdout);

		
		//Create Child Process code
		ret=fork()
		.
		.
		.



	}//end for

	//restore in/out details

	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);

	if(!CurrentCommand._background){
		//wait for last CurrentCommand
		waitpid(ret,NULL);
	}
}


