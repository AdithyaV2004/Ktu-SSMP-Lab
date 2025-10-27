#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    FILE *fp1, *fp2, *fp3, *fp4;
    int len,nol=0;
    char label[10], opcode[10], operand[10], locctr[10];
    char symbol[10], symbol_value[10], code[10], value[10], start[10];
    fp1 = fopen("intermediate.txt", "r");
    fp2 = fopen("length.txt", "r");
    fp3 = fopen("optab.txt", "r");
    fp4 = fopen("symtab.txt", "r");
    if (!fp1 || !fp2 || !fp3 || !fp4) {
        printf("Error opening file.\n");
        exit(1);
    }
    fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        strcpy(start, operand);
        fscanf(fp2, "%d", &len);
    }
    printf("H^%s^%06s^%06X\n", label, start, len);
    printf("T^00%s^", start);
    fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);
    while (strcmp(opcode, "END") != 0) {
        if(nol>=8){
            printf("\nT^00%s^",locctr);
            nol=0;
        }        
        int found = 0;
        rewind(fp3);
        while (fscanf(fp3, "%s%s", code, value) != EOF) {
            if (strcmp(opcode, code) == 0) {
                rewind(fp4);
                while (fscanf(fp4, "%s%s", symbol, symbol_value) != EOF) {
                    if (strcmp(symbol, operand) == 0) {
                        printf("%s%s^", value, symbol_value);
                        nol+=3;
                        found = 1;
                        break;
                    }
                }
                break;
            }
        }
        if (!found) {
            if (strcmp(opcode, "WORD") == 0){
                printf("%06d^", atoi(operand));
                nol+=3;
            }
            else if (strcmp(opcode, "BYTE") == 0) {
                int byte_len = strlen(operand);
                for (int i = 2; i < byte_len - 1; i++){
                    printf("%X", operand[i]);                    
                    nol+=1;
                }
                printf("^");
            }
        }
        fscanf(fp1, "%s%s%s%s", locctr, label, opcode, operand);
    }
    // --- END RECORD ---
    printf("\nE^00%s\n", start);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}