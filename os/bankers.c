#include<stdio.h>
int alloc[20][20], max[20][20], need[20][20], avail[20];
int m, n, seq[10];

void nmatrix(){
    for(int i=0; i<m;i++){
        for(int j=0;j<n;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("Process\tAllocation\tMax\tNeed\n");
    for(int i=0;i<m;i++){
        printf("p%d\t",i);
        for(int j=0;j<n;j++){
            printf("%d ",alloc[i][j]);
        }
        printf("\t\t");
        for(int j=0;j<n;j++){
            printf("%d ",max[i][j]);
        }
        printf("\t");
        for(int j=0;j<n;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
}

int issafe() {
    int c = 0, completed[20] = {0}, top = 0;
    while (c < m) {
        int f = 0;
        for (int i = 0; i < m; i++) {
            if (completed[i] == 0) {
                int s = 1;
                for (int j = 0; j < n; j++) {
                    if (need[i][j] > avail[j]) {
                        s = 0;
                        break;
                    }
                }
                if (s) {
                    f = 1;
                    for (int j = 0; j < n; j++) {
                        avail[j] += alloc[i][j];
                    }
                    completed[i] = 1;
                    seq[top++] = i;
                    c++;
                }
            }
        }
        if (!f) {
            return 0;  // unsafe state
        }
    }
    return 1;  // safe sequence exists
}



void main(){
    printf("Enter the number of processes: ");
    scanf("%d",&m);
    printf("Enter the number of Resources: ");
    scanf("%d",&n);
    
    printf("\nEnter the allocation matrix:\n");
    for(int i=0; i<m;i++){
        printf("Process p%d\n",i);
        for(int j=0;j<n;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("\nEnter the max matrix:\n");
    for(int i=0; i<m;i++){
        printf("Process p%d\n",i);
        for(int j=0;j<n;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter the Available resources:\n");
    for(int j=0;j<n;j++){
        scanf("%d",&avail[j]);
    }
    nmatrix();
    if(issafe()){
        printf("\nSafe sequence: ");
        for(int i=0;i<m-1;i++){
            printf("p%d->",seq[i]);        
        }
        printf("p%d",seq[m-1]);
    }else{
        printf("\nNo safe sequence");
    }
}
