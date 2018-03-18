int InitCommand();
	//-> constructs a simple empty command

void insertSimpleCommand(struct SimpleCommand * simpleCommand);
        // -> populates empty command
        // -> enlarges the array _simpleCommands if necessary

void prompt();
void print();
void execute();
void clear();