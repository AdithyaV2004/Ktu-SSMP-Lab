 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex_to_dec(char hex[]) {
    int val;
    sscanf(hex, "%x", &val);
    return val;
}
int main() {
    {
    char line[200], recordType, progaddr_str[10];
    char opcode[10], operand[10], relocated[10];
    int maskBits[12];
    int progaddr, start, length_dec, maskVal, loadaddr;
    printf("Enter program load address (PROGADDR): ");
    scanf("%s", progaddr_str);
    sscanf(progaddr_str, "%x", &progaddr);
    printf("\nADDRESS\t\tCONTENT\n----------------------------\n");
    FILE *fp = fopen("input.txt", "r");
    if (!fp) {
        printf("Error: Cannot open input file.\n");
        return 0;
    }
    while (fscanf(fp, " %c", &recordType) != EOF) {
        if (recordType == 'H' || recordType == 'E') {
            fgets(line, sizeof(line), fp); 
        } else if (recordType == 'T') {            
            if (fscanf(fp, "%x %x %x", &start, &length_dec, &maskVal) != 3) {
                break; 
            }
            loadaddr = progaddr + start; 
            for (int i = 11; i >= 0; i--) {
                maskBits[i] = maskVal % 2;
                maskVal /= 2;
            }
            for (int i = 0; i < 10; i++) {
                if (fscanf(fp, "%s %s", opcode, operand) != 2)
                    break;
                int memaddr = loadaddr + (i * 3);
                int operand_dec;
                sscanf(operand, "%x", &operand_dec);
                if (maskBits[i] == 1)
                    operand_dec += progaddr;
                sprintf(relocated, "%04X", operand_dec);
                printf("%04X\t\t%s%s\n", memaddr, opcode, relocated);
            }
        }
    }
    printf("----------------------------\n");
    fclose(fp);
    return 0;
}
}            