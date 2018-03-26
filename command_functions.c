#include "all_include.h"

int InitCommand(){
	CurrentCommand._numberOfAvailableSimpleCommands=MAX_NUMBER_OF_SIMPLE_COMMANDS;
    CurrentCommand._numberOfSimpleCommands=0;

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
    int ret; 
    struct stack_elem command_to_be_pushed;
    for (int i = 0; i <CurrentCommand._numberOfSimpleCommands; i++ ){
        if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"cd")==0){
                //printf("\ncaling cd");
                cd(CurrentCommand._simpleCommands[i]);
                command_to_be_pushed=GenerateStackElem();
                command_to_be_pushed.pid=getpid();
                if(push(command_to_be_pushed)!=1)printf("could not push\n");
                //printf("\nback from cd");
        }
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"exit")==0){
                    quit();
                }
        else if(strcmp(CurrentCommand._simpleCommands[i]._arguments[0],"history")==0){
                    history();
                    command_to_be_pushed=GenerateStackElem();
                    command_to_be_pushed.pid=getpid();
                    if(push(command_to_be_pushed)!=1)printf("could not push\n");
                }
        else{
            ret = fork();
            if (ret == 0) { 
                execvp(CurrentCommand._simpleCommands[i]._arguments[0],CurrentCommand._simpleCommands[i]._arguments);
                    perror("execvp");
                
                
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
    if (!CurrentCommand._background){
        // wait for last process
        waitpid(ret, NULL);
    } 
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
    
    printf("                            OutFile : %s\n",CurrentCommand._outFile);
    printf("                          inputFile : %s\n",CurrentCommand._inputFile);
    printf("                           errFile  : %s\n",CurrentCommand._errFile);
    printf("                         background : %d\n",CurrentCommand._background); 
}

