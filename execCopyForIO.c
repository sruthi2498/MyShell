execute(){
	
	int tmpin = dup(0);
	int tmpout = dup(0);

	//InFile Saved in command structure
	//Set fdin
	int fdin;
	if(infile){
		fdin = open(infile, O_READ);
	}
	else{
		fdin=dup(tmpin);
	}

	int ret;
	int fdout;

	for(i=0; i<CurrentCommand._numberOfSimpleCommands;i++){

		//stdin redirected to fdin
		dup2(fdin,0);
		close(fdin);

		if(i == (CurrentCommand._numberOfSimpleCommands - 1)){
			//Set fdout
			if(outfile){
				fdout = open(outfile, O_RDWR);
			}
			else{
				fdout = dup(tmpout);
			}
		}
		else{

			//Create a pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}

		dup2(fdout,1);
		close(fdout);

		
		//Child Process code




	}

}