#include "all_include.h"
int editor(char * filename){
	FILE *f = fopen(filename, "a+");
	if(!f){
		printf("File could not be created/opened\n");
		return 0;
	}
	//FIND SIZE OF FILE
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	//READ ENTIRE FILE
	char *string = malloc(fsize + 1);
	int read_ret=fread(string, fsize, 1, f);
	if(read_ret<0){
		printf("File Empty or could not read\n");
		return 0;
	}

	string[fsize] = 0;
	//PRINT FILENAME
	printf("\n--------------------------\n\tFILE : %s\t\n--------------------------\n",filename);

	//SPLIT STRING INTO LINES
	 int i=1;
	 if(strlen(string)!=0){
		char* pch = NULL;

	    pch = strtok(string, "\n");
	   
	    while (pch != NULL)
	    {
	    	//PRINT EACH LINE WITH LINE NUMBER
	        printf("%d. %s\n", i,pch);
	        i++;
	        pch = strtok(NULL, "\n");
	    }
	}
	else{
		printf("%d. ",i );
		i++;
		
	}

	//ALLOW USER TO WRITE UNTIL CtrlD IS PRESSED
	char * new_string=malloc(sizeof(char)*WRITE_SIZE);
	int write_ret;
	for ( ;; ) {

	    fflush( NULL );   
	    //GET NEW STRING
	    if ( fgets( new_string,WRITE_SIZE,stdin) == NULL ) break;
	    if(new_string[0]=='\n' || new_string[strlen(new_string)-1]=='\n' ){
	    	 printf( "%d. " ,i);
	    	 i++;
	    }
	    //WRITE NEW STRING
	    write_ret=fwrite(new_string, strlen(new_string), 1, f);
		if(write_ret<0){
			printf("Could not edit file\n");
			return 0;
		}
	    
	}
	

	fclose(f);
	return 1;
}