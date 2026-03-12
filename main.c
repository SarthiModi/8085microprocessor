#include "simulator.h"

Label labelDirectory[MAX_LABELS];
int totalLabels = 0;

char programBuffer[MAX_PROGRAM_LINES][100];
int totalLines = 0;

void loadAssemblyProgram(){
    FILE *fp = fopen("program.asm","r");
    if(!fp){ printf("program.asm not found\n"); exit(1); }

    totalLines = 0;
    totalLabels = 0;

    while(fgets(programBuffer[totalLines],100,fp)){
        char temp[100];
        strcpy(temp, programBuffer[totalLines]);

        char *colon = strchr(temp, ':');
        if(colon){
            *colon = '\0';
            strcpy(labelDirectory[totalLabels].name, temp);
            labelDirectory[totalLabels].address = totalLines;
            totalLabels++;
        }
        totalLines++;
    }
    fclose(fp);
}

void executeProgram(){
    while(cpu.PC < totalLines){
        printf("\nExecuting Line %d: %s\n", cpu.PC+1, programBuffer[cpu.PC]);
        decodeInstruction(programBuffer[cpu.PC]);
        displayCPUState();

        executedInstructionCount++;
        cpu.PC++;

        if(isDebugMode){
            printf("\nPress ENTER to execute next instruction...");
            getchar();
        }
    }
}

int main(){
    initCPU();
    setupInitialEnvironment();
    loadAssemblyProgram();
    executeProgram();

    printFlags();
    printf("\nTotal Instructions Executed: %d\n", executedInstructionCount);

    char choice;
    unsigned int start, end;

    printf("\nDo you want to see memory output? (y/n): ");
    scanf(" %c", &choice);

    while(choice=='y' || choice=='Y'){
        printf("Enter start address (in HEX): ");
        scanf("%x", &start);
        printf("Enter end address (in HEX): ");
        scanf("%x", &end);
        displayMemory(start,end);

        printf("\nDo you want to see other output? (y/n): ");
        scanf(" %c", &choice);
    }

    printf("\nProgram Finished.\n");
    return 0;
}
