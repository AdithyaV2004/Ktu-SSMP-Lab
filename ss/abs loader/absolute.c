#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = fopen("input.txt", "r");
    unsigned int startaddr, aligned_addr, bytecount, wordcount;
    char line[200];
    int first_line = 1;   
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }  
    aligned_addr = 0;
    bytecount = 0;
    wordcount = 0;   
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] == 'H') {
            continue; // Skip header
        }
        else if (line[0] == 'E') {
            break; // End record
        }
        else if (line[0] == 'T') {
            // Parse T record: T address length data1 data2 ...
            char *token = strtok(line, " \t\n");
            // Skip 'T'          
            // Get address
            token = strtok(NULL, " \t\n");
            if (token == NULL) continue;
            if (sscanf(token, "%X", &startaddr) != 1) {
                printf("Error converting address\n");
                continue;
            }           
            // Skip length
            token = strtok(NULL, " \t\n");         
            // Calculate aligned address and offset
            unsigned int new_aligned = startaddr & ~0Xf;
            int offset = startaddr - new_aligned;           
            // If we're on a new 16-byte boundary, print newline and address
            if (first_line || new_aligned != aligned_addr) {
                // Check if we need to fill gap on previous line before starting new line
                if (!first_line) {
                    // Fill remaining bytes on current line with xx if needed
                    while (bytecount > 0 && bytecount < 8) {
                        printf("xx");
                        bytecount += 2;
                        if (bytecount == 8) {
                            printf(" ");
                            bytecount = 0;
                            wordcount++;
                        }
                    }
                    while (wordcount > 0 && wordcount < 4) {
                        printf("xxxxxxxx ");
                        wordcount++;
                    }
                    printf("\n");
                }                
                aligned_addr = new_aligned;
                bytecount = 0;
                wordcount = 0;
                printf("%04X\t\t", aligned_addr);
                first_line = 0;                
                // Print placeholder bytes for offset
                for (int k = 0; k < offset; k++) {
                    printf("xx");
                    bytecount += 2;
                    
                    if (bytecount == 8) {
                        printf(" ");
                        bytecount = 0;
                        wordcount++;
                    }
                }
            }           
            // Process data tokens
            while ((token = strtok(NULL, " \t\n")) != NULL) {
                // Print each pair of hex digits
                for (size_t idx = 0; idx < strlen(token); idx += 2) {
                    if (token[idx] != '\0' && token[idx + 1] != '\0') {
                        printf("%c%c", token[idx], token[idx + 1]);
                        bytecount += 2;                        
                        if (bytecount == 8) {
                            printf(" ");
                            bytecount = 0;
                            wordcount++;
                        }                        
                        if (wordcount == 4) {
                            aligned_addr += 16;
                            wordcount = 0;
                            bytecount = 0;
                            printf("\n%04X\t\t", aligned_addr);
                        }
                    }
                }
            }
        }
    }    
    // Fill remaining bytes on the last line with xx
    while (bytecount > 0 && bytecount < 8) {
        printf("xx");
        bytecount += 2;
        if (bytecount == 8) {
            printf(" ");
            bytecount = 0;
            wordcount++;
        }
    }
    while (wordcount > 0 && wordcount < 4) {
        printf("xxxxxxxx ");
        wordcount++;
    }    
    printf("\n");
    fclose(fp);
    return 0;
}