struct SimpleCommand simpleCommand;
int InsertSimpleCommand(struct SimpleCommand simpleCommand);
        // -> populates empty command
        // -> enlarges the array _simpleCommands if necessary
		// 0 on fail, 1 on success
int InitCommand();
	//-> constructs a simple empty command
	// 0 on fail, 1 on success

void prompt();
void print();
void execute();
void clear();

void quit();
void history();

void DisplayCommand();

char * RecreateCommand(char * command);
struct stack_elem GenerateStackElem();


void cd(struct  SimpleCommand SC);

int splitEnv(char *argVal, char **name, char **value);
void myPrintEnv();

void setOutFile(char * filename,int flag);
void setInFile(char * filename);

extern char **environ;
