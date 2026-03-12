#include "simulator.h"

CPU cpuState;
int isDebugMode = 1;
int executedInstructionCount = 0;

void initCPU() {
    cpuState.A = cpuState.B = cpuState.C = cpuState.D = cpuState.E = cpuState.H = cpuState.L = 0;
    cpuState.PC = 0;
    cpuState.SP = 0xFFFF;
    cpuState.Z = cpuState.S = cpuState.P = cpuState.CY = cpuState.AC = 0;
}

void updateFlags(unsigned char result) {
    cpuState.Z = (result == 0);
    cpuState.S = (result & 0x80) != 0;

    int count = 0;
    for(int i = 0; i < 8; i++)
        if(result & (1 << i)) count++;
    cpuState.P = (count % 2 == 0);
}

void displayCPUState() {
    printf("\n================ CPU STATE ================\n");
    printf("A:%02X  B:%02X  C:%02X  D:%02X  E:%02X  H:%02X  L:%02X\n",
           cpuState.A,cpuState.B,cpuState.C,cpuState.D,cpuState.E,cpuState.H,cpuState.L);
    printf("PC:%04X  SP:%04X\n", cpuState.PC, cpuState.SP);
    printf("FLAGS -> Z:%d S:%d P:%d CY:%d AC:%d\n",
           cpuState.Z,cpuState.S,cpuState.P,cpuState.CY,cpuState.AC);
    printf("===========================================\n");
}

void printFlags() {
    printf("\nFinal Flags: Z=%d S=%d P=%d CY=%d AC=%d\n",
           cpuState.Z,cpuState.S,cpuState.P,cpuState.CY,cpuState.AC);
}

void displayMemory(int start, int end) {
    printf("\n--- MEMORY OUTPUT ---\n");
    for(int i = start; i <= end; i++)
        printf("Addr %04X : %02X\n", i, ramMemory[i]);
}

void setupInitialEnvironment() {
    char choice;
    unsigned int val, addr;

    printf("Do you want to initialize registers? (y/n): ");
    scanf(" %c", &choice);

    if(choice == 'y' || choice == 'Y') {
        printf("Enter A register (hex): "); scanf("%x", &val); cpuState.A = val;
        printf("Enter B register (hex): "); scanf("%x", &val); cpuState.B = val;
        printf("Enter C register (hex): "); scanf("%x", &val); cpuState.C = val;
        printf("Enter D register (hex): "); scanf("%x", &val); cpuState.D = val;
        printf("Enter E register (hex): "); scanf("%x", &val); cpuState.E = val;
        printf("Enter H register (hex): "); scanf("%x", &val); cpuState.H = val;
        printf("Enter L register (hex): "); scanf("%x", &val); cpuState.L = val;
    }

    printf("Do you want to initialize memory? (y/n): ");
    scanf(" %c", &choice);

    while(choice == 'y' || choice == 'Y') {
        printf("Enter memory address (hex): ");
        scanf("%x", &addr);
        printf("Enter value (hex): ");
        scanf("%x", &val);
        ramMemory[addr] = val;

        printf("Add another memory value? (y/n): ");
        scanf(" %c", &choice);
    }
}
