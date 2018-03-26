#include "all_include.h"
int editor(char * filename){
	FILE *f = fopen(filename, "a+");
	if(!f){
		printf("File could not be created/opened\n");
		return 0;
	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *string = malloc(fsize + 1);
	int read_ret=fread(string, fsize, 1, f);
	if(read_ret<0){
		printf("File Empty or could not read\n");
		return 0;
	}

	string[fsize] = 0;
	printf("\n--------------------------\n\tFILE : %s\t\n--------------------------\n",filename);
	printf("%s",string);


	char * new_string=malloc(sizeof(char)*WRITE_SIZE);
	int write_ret;
	for ( ;; ) {
	   // printf( "enter input: " );
	    fflush( NULL );   // make sure prompt is actually displayed, credit Basile Starynkevitch
	    if ( fgets( new_string,WRITE_SIZE,stdin) == NULL ) break;
	    write_ret=fwrite(new_string, strlen(new_string), 1, f);
		if(write_ret<0){
			printf("Could not edit file\n");
			return 0;
	}
	    
	}
	

	fclose(f);
	return 1;
}