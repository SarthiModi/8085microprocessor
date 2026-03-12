extern unsigned char ramMemory[MEM_SIZE];
extern CPU cpuState;
extern int isDebugMode;
extern int executedInstructionCount;
extern char programBuffer[500][100];
extern int totalLines;

extern Label labelDirectory[MAX_LABELS];
extern int totalLabels;

void displayCPUState();
void decodeInstruction(char *line);
void loadAssemblyProgram();
void executeProgram();
void displayMemory(int start, int end);
void setupInitialEnvironment();
