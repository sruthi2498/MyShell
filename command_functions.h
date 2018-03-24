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

void DisplayCommand();

char * RecreateCommand();

void cd(struct  SimpleCommand SC);