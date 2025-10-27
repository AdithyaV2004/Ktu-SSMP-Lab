#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
 
void main(){ 
    FILE *fp=fopen("input.txt","r"); 
    unsigned int i,j,startaddr,aligned_addr,bytecount,wordcount; 
    char line[100],start_addr1[10]; 
     
    if(fp==NULL){ 
        printf("Error opening file"); 
        exit(1); 
    } 
    if(fscanf(fp,"%s",line)==EOF){ 
        printf("Empty file"); 
        exit(1); 
    } 
    while(fscanf(fp,"%s",line)!=EOF){ 
        if(line[0]=='T'){ 
            for(i=2,j=0;i<8 && j<6;i++,j++) 
                start_addr1[j]=line[i]; 
            start_addr1[j]='\0'; 
            if(sscanf(start_addr1,"%X",&startaddr)!=1){ 
                printf("Error converting hex:%s\n",start_addr1); 
                break; 
            } 
             
            aligned_addr= startaddr & ~0Xf; 
            int offset= startaddr - aligned_addr; 
            i=12; 
            bytecount=0; 
            wordcount=0; 
            printf("%04X\t\t",aligned_addr); 
             
            for(int k=0;k<offset;k++){ 
                printf("xx"); 
                bytecount+=2; 
                 
                if(bytecount==8){ 
                    printf(" "); 
                    bytecount=0; 
                    wordcount++; 
                     
                } 
            } 
             
            while(line[i]!='\0'){ 
                 
                if(line[i]!='^'){ 
                    printf("%c%c",line[i],line[i+1]); 
                    bytecount+=2; 
                    startaddr++; 
                     
                    if(bytecount==8){ 
                        printf(" "); 
                        bytecount=0; 
                        wordcount++; 
                    } 
                     
                    if(wordcount==4){ 
                        aligned_addr+=16; 
                        wordcount=0; 
                        printf("\n%04X\t\t",aligned_addr); 
                    } 
                    i+=2; 
                } 
                else 
                    i++; 
            } 
            printf("\n"); 
        } 
        else if(line[0]=='E') 
            break; 
    } 
    fclose(fp); 
}