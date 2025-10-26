#include<stdio.h>

struct process{
    int pid, at, bt, ct, tat, wt;
}p[20];
int n;
int t=0;

void sort(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(p[j].at>p[j+1].at){
                struct process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void calc(){
    for (int i=0;i<n;i++){
        if(p[i].at>t){
            t=p[i].at;
        }
        p[i].ct=t+p[i].bt;
        p[i].wt=p[i].ct-t;
        p[i].tat=p[i].ct-p[i].at;
        t=p[i].ct;
    }
}

void gantt(){
    printf("\nGantt---\n");
    for(int i=0;i<n;i++){
        printf("|\tp%d\t",p[i].pid);
    }
    printf("\n0\t");
    for(int i=0;i<n;i++){
        printf("\t%d\t",p[i].ct);
    }
    printf("\n");
}

void display(){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }    
}

void main(){
    printf("Enter no of processes:");
    scanf("%d",&n);
    printf("\nEnter at and bt of processes:\n");
    for (int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Process %d:\n",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);
    }
    sort();
    calc();
    gantt();
    display();
}





