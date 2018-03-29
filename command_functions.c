#include "all_include.h"

int InitCommand(){
    sc = 0;
	CurrentCommand._numberOfAvailableSimpleCommands=MAX_NUMBER_OF_SIMPLE_COMMANDS;
    CurrentCommand._numberOfSimpleCommands=0;

    CurrentCommand._outFile=NULL; 
    CurrentCommand._inputFile=NULL; 
    CurrentCommand._errFile=NULL; 
    CurrentCommand.flag_for_outfile=0;
    CurrentCommand._background=0; 

   // printf("Init commanding %d\n", ++comm);
    return 1;
}



int InsertSimpleCommand(struct SimpleCommand simpleCommand){

	//CurrentCommand._simpleCommands is the array of simpleCommands
	//CurrentCommand._numberOfSimpleCommands will give the index in that array
    //printf("\ninserting...\n");
	if(CurrentCommand._numberOfSimpleCommands >= CurrentCommand._numberOfAvailableSimpleCommands ){
		printf("Max number of commands reached, insertSimpleCommand FAILED\n");
		return 0;
	}

	CurrentCommand._simpleCommands[CurrentCommand._numberOfSimpleCommands]=simpleCommand;

 	CurrentCommand._numberOfSimpleCommands++;
   
 	return 1;
}


void execute(){

    //save in/out
    int tmpin = dup(0);
    int tmpout = dup(1);
   // printf("tmpin %d tmpout %d\n",tmpin,tmpout);

    //InFile Saved in command structure
    //Set fdin
    int fdin;
    if(CurrentCommand._inputFile){
        if((fdin = open(CurrentCommand._inputFile, O_RDONLY))<0)
                    perror("open");
        else 
            printf("opened infile %s\n",CurrentCommand._inputFile);
    }
    else{
        //use default input
        fdin=dup(tmpin);
    }
   // printf("fdin %d\n",fdin);
    int ret;
    int fdout;

    struct stack_elem command_to_be_pushed;
   // printf("\n in execute - number of simpleCommands : %d \n",CurrentCommand._numberOfSimpleCommands);
    for (int i = 0; i <CurrentCommand._numberOfSimpleCommands; i++ ){
        
        //stdin redirected to fdin
        dup2(fdin,0);
        close(fdin);

        if(i == (CurrentCommand._numberOfSimpleCommands - 1)){
            //Last simple CurrentCommand
            if(CurrentCommand._outFile){
                if((fdout = open(CurrentCommand._outFile, O_RDWR | O_CREAT, S_IRWXU|S_IRWXG |S_IRWXO ))<0)
                    perror("open");
                else 
                  printf("opened outfile %s\n",CurrentCommand._outFile);
            }
            else{
                fdout = dup(tmpout);
            }
            //printf("fdout %d\n",fdout);
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

        //ALIAS
        char * current_command=malloc(sizeof(char) * (20) );
        strcpy(current_command,CurrentCommand._simpleCommands[i]._arguments[0]);
        //printf("current command %s\n",current_command);
        struct Aliastruct AS = getAlias(current_command);
        printf("command returned %s\n",AS.command);
        if(strcmp(AS.command," ")!=0)
        {
            //char * command_arg, *command_arg1;
            CurrentCommand._simpleCommands[i]._arguments[0] = strtok(AS.command," ");
            CurrentCommand._simpleCommands[i]._arguments[1] = strtok(NULL," ");

        }



        if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"alias")==0){
            char *alias,*command;
            DisplayCommand();
            int number_of_args=CurrentCommand._simpleCommands[i]._numberOfArguments;

            if(number_of_args<5){
                printf("Invalid alias, Expected more number of arguments\n");
                return;
            }
            // strcpy(current_command,CurrentCommand._simpleCommands[i]._arguments[1]);
            
            // alias = strtok(current_command, "=");
            // printf("alias %s\n",alias);
            // command = strtok(NULL, "=");
            
            //second last argument : aliasname
            //strcpy(alias,"");
            alias=CurrentCommand._simpleCommands[i]._arguments[number_of_args-2];
            command=malloc(sizeof(char)*20);
            strcpy(command,"");
            //third last argument : "="
            //fourth last argument : actual command starts
            int command_start_arg=number_of_args-4;
            //second argument : last arg in actual command
            int command_end_arg=1;

            int j=command_start_arg;
            while(j>=command_end_arg){
               // printf("j %d\n",j);
                //printf("arg : %s\n",CurrentCommand._simpleCommands[i]._arguments[j]);
                strcat(command,CurrentCommand._simpleCommands[i]._arguments[j]);
                strcat(command," ");
                j--;

            }
            //printf("alias %s command %s\n",alias,command);
            //alias[strlen(alias)]='\0';
            //command[strlen(command)]='\0';
            printf("alias %s command %s\n",alias,command);
            setAlias(alias,command);
        }
        //CD
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"cd")==0){
                //printf("\ncaling cd");
                cd(CurrentCommand._simpleCommands[i]); 
                command_to_be_pushed=GenerateStackElem();
                command_to_be_pushed.pid=getpid();
                if(push(command_to_be_pushed)!=1)printf("could not push\n");
                //printf("\nback from cd");
        }
        //HISTORY
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"history")==0){
              history();
              command_to_be_pushed=GenerateStackElem();
              command_to_be_pushed.pid=getpid();
              if(push(command_to_be_pushed)!=1)printf("could not push\n");
          }
        //EDITOR
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"editor")==0){
                    if(CurrentCommand._simpleCommands[i]._numberOfArguments <3){
                        printf("Expected file name not found\n");
                        return;
                    }
                    char * filename=CurrentCommand._simpleCommands[i]._arguments[1];
                    //printf("file : %s\n",filename);
                    int return_val=editor(filename);
                    command_to_be_pushed=GenerateStackElem();
                    command_to_be_pushed.pid=getpid();
                    if(push(command_to_be_pushed)!=1)printf("could not push\n");
                }
        //QUIT
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"exit")==0){
                    quit();
                }
        //SET ENV VAR
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"export")==0){   
            if(CurrentCommand._simpleCommands[i]._numberOfArguments == 3){
                char *name = malloc(sizeof(char)*50);
                char *value = malloc(sizeof(char)*75);
                if(splitEnv(CurrentCommand._simpleCommands[i]._arguments[1], &name, &value)){
                    setenv(name, value, 1);
                }
            }
            else{
                printf("Wrong number of arguments to set environment variable. Expects input to be in the form - export newvar='path/to/file'  ");
            }
        }
        //PRINT ENV VAR
        else if( (strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"printenv")==0) ||
                    (strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"env")==0)){
                myPrintEnv();
        }
       //UNSET ENV VAR
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"unset")==0){
            if(CurrentCommand._simpleCommands[i]._arguments[1] != NULL)
                    unsetenv(CurrentCommand._simpleCommands[i]._arguments[1]);
        }        
        else{
            ret = fork();
            if (ret == 0) { 
                execvp(CurrentCommand._simpleCommands[i]._arguments[0],CurrentCommand._simpleCommands[i]._arguments);
                    perror("execvp");
                
                //sprompt();              
                _exit(1);
            }
            else if(ret < 0){
                perror("fork");
                return;
            }
            if(i==0){
                //printf("first simple command (take pid)\n");
                command_to_be_pushed=GenerateStackElem();
                command_to_be_pushed.pid=ret;
                if(push(command_to_be_pushed)!=1)printf("could not push\n");
            }
            //ret value in parent is pid of child
        }
        
        // Parent shell continue
    
        
    }// for

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


void setOutFile(char * filename,int flag){
    CurrentCommand._outFile=filename;
    CurrentCommand.flag_for_outfile=flag;
}
void setInFile(char * filename){
    //printf("setting input file to %s",filename);
    CurrentCommand._inputFile=filename;
}


void cd(struct  SimpleCommand SC){


    // if(strcmp(SC._arguments[1],"..")!=0 && strcmp(SC._arguments[1],".")!=0 ){
    //     strcat(Prompt,"/");
    //     strcat(Prompt,SC._arguments[1]);
    // }               
    if(chdir(SC._arguments[1])==-1)printf("Could not cd\n");  
}
void prompt(){
    printf("\n%s",Prompt);
    printf("$");
}

void quit(){
    printf("\nExit...\n");
    //fflush( stdout );
    exit(0);

}

void history(){
    displayStack();
}

char * RecreateCommand(char * command){
    //char * command=malloc(sizeof(char)*MAX_CHAR_SIZE_OF_COMMAND);
    //char command[MAX_CHAR_SIZE_OF_COMMAND];
    strcpy(command,"");
    for(int i=0;i<CurrentCommand._numberOfSimpleCommands;i++){
        if(i>0 && i<CurrentCommand._numberOfSimpleCommands-1){
             strcat(command," | ");
        }
       // char * simpleCommand=malloc(sizeof(char)*MAX_CHAR_SIZE_OF_SIMPLECOMMAND);
        struct SimpleCommand SC=CurrentCommand._simpleCommands[i];
        for(int j=0;j<SC._numberOfArguments-1;j++){
            //printf("\targ %d %s\n",j,SC._arguments[j]);
            strcat(command,SC._arguments[j]);
            strcat(command," ");
          //  printf("\tcommand at %d %s\n",j,command);
        }
        //printf("simpleCommand %s\n",simpleCommand);       
    }
    command[strlen(command)]='\0';
   // printf("Command in recreate %s\n",command);
    return command;
}

struct stack_elem GenerateStackElem(){
    struct stack_elem SE;
    //get command
    SE.command=malloc(sizeof(char)*MAX_CHAR_SIZE_OF_COMMAND);
    SE.command=strdup(RecreateCommand(SE.command));
    //printf("command %s\n",SE.command);
    time_t mytime;  

    mytime = time(NULL);
    SE.time_str=malloc(sizeof(char)*50);
    SE.time_str = strdup(ctime(&mytime));
    SE.time_str[strlen(SE.time_str)-1] = '\0';
    //printf("Current Time : %s\n", SE.time_str);
    //printf ( "Current local time and date: %s", asctime (timeinfo) );
    return SE;
}

void DisplayCommand(){

	printf("\nCOMMAND STRUCTURE\n");
	printf("    numberOfAvailableSimpleCommands : %d\n",CurrentCommand._numberOfAvailableSimpleCommands);
    printf("             numberOfSimpleCommands : %d\n",CurrentCommand._numberOfSimpleCommands);

    printf("                            \nSIMPLE COMMANDS\n");
    for(int i=0;i<CurrentCommand._numberOfSimpleCommands;i++){
    	printf("                     Simple command : %d\n",i);
    	struct SimpleCommand SC=CurrentCommand._simpleCommands[i];
    	printf("         numberOfAvailableArguments : %d\n",SC._numberOfAvailableArguments); 
        printf("                  numberOfArguments : %d\n",SC._numberOfArguments); 
        
        for(int j=0;j<SC._numberOfArguments;j++){
    	 	printf("                             Arg %d : %s\n",j,SC._arguments[j]);
    	}
        printf("                          ---------------\n");
    }
    
    printf("                            OutFile : %s (Flag : %d)\n",CurrentCommand._outFile,CurrentCommand.flag_for_outfile);
    printf("                          inputFile : %s\n",CurrentCommand._inputFile);
    printf("                           errFile  : %s\n",CurrentCommand._errFile);
    printf("                         background : %d\n",CurrentCommand._background); 
}

//Call setenv function in c with no arguments to print all environment variables
void myPrintEnv(){
    char **var = environ;
    while(*var != NULL){
        printf("%s\n", *var);
        *var++;
    }
}

int splitEnv(char *argVal, char **name, char **value){

    char *token;
    char *str;
    int i;
    str = strdup(argVal);

    /* get the first token */
    *name = strtok(str, "=");
    *value = strtok(NULL, "=");
   // printf("Name : %s Value : %s \n", *name, *value);
    return 1;

}