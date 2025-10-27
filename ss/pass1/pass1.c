#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
 
 
 
void main(){ 
    char label[10],opcode[10],operand[10]; 
    char code[10],value[3]; 
    int startaddr=0,LOCCTR,length; 
    FILE *fp1,*fp2,*fp3,*fp4; 
    fp1=fopen("input.txt","r"); 
    fp2=fopen("optab.txt","r"); 
     
    fp3=fopen("symtab.txt","w"); 
    fp4=fopen("intermediate.txt","w"); 
     
    if(!fp1||!fp2||!fp3||!fp4){ 
        printf("Error opening file"); 
        exit(1); 
    } 
    fscanf(fp1,"%s%s%s",label,opcode,operand); 
    if(strcmp(opcode,"START")==0){ 
        startaddr=atoi(operand); 
        LOCCTR=startaddr; 
        fprintf(fp4,"%d\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand); 
        fscanf(fp1,"%s\t%s\t%s",label,opcode,operand); 
    } 
    else LOCCTR=0; 
    while(strcmp(opcode,"END")!=0){ 
        fprintf(fp4,"%d\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand); 
        if(strcmp(label,"**")!=0) 
            fprintf(fp3,"%s\t%d\n",label,LOCCTR); 
        rewind(fp2); 
        fscanf(fp2,"%s\t%s",code,value); 
        while(strcmp(code,"END")!=0){ 
            if(strcmp(code,opcode)==0){ 
                LOCCTR+=3; 
                break; 
            } 
            fscanf(fp2,"%s\t%s",code,value); 
        } 
        if(strcmp(opcode,"WORD")==0)     LOCCTR+=3; 
        else if(strcmp(opcode,"RESW")==0)    LOCCTR+=(3*atoi(operand)); 
        else if(strcmp(opcode,"RESB")==0)    LOCCTR+=(atoi(operand)); 
        else if(strcmp(opcode,"BYTE")==0)    LOCCTR += (strlen(operand) - 3); 
        fscanf(fp1, "%s%s%s", label, opcode, operand); 
    } 
fprintf(fp4,"%d\t%s\t%s\t%s\n",LOCCTR,label,opcode,operand); 
fclose(fp1); 
fclose(fp2); 
fclose(fp3); 
fclose(fp4); 
length=LOCCTR - startaddr; 
printf("length of the file:%d",length); 
}