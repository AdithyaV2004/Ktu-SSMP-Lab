#include<stdio.h>
struct process{
    int pid, at, bt, ct, tat, wt, rem, c;
}p[20];
int n, q;
float tt=0,w=0;
int arr[100];

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

void robin(){
    printf("Gantt--\n");
    int t=p[0].at, completed=0,top=0;
    while(completed<n){
        int f=0;
        for(int i=0;i<n;i++){
            if(p[i].at<=t){
                if(p[i].rem<=q && p[i].c==0){
                    t+=p[i].rem;
                    p[i].rem=0;
                    p[i].ct=t;
                    p[i].tat=p[i].ct-p[i].at;
                    p[i].wt=p[i].tat-p[i].bt;
                    tt+=p[i].tat;
                    w+=p[i].wt;
                    completed++;
                    printf("|\tp%d",p[i].pid);
                    arr[top++]=t;
                    p[i].c=1;
                    f=1;
                }else if(p[i].c==0){
                    p[i].rem-=q;
                    t+=q;
                    printf("|\tp%d",p[i].pid);
                    arr[top++]=t;
                }
            }
        }
        if(!f){
            for(int i=0;i<n;i++){
                if(p[i].at>t && p[i].c==0){
                    t=p[i].at;
                }
                break;
            }
        }
    }
    printf("\n0\t");
    for(int i=0;i<top;i++){
        printf("\t%d\t",arr[i]);
    }
}

void table(){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    for(int i=0;i<n;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\n\nAvg tat: %f\nAvg wt: %f",(tt/n),(w/n));
}

void main(){    
    printf("Enter no of processes: ");
    scanf("%d",&n);
    printf("\nEnter the at, bt:\n");
    for(int i=0;i<n;i++){
        printf("\nProcess: %d\n",i+1);
            scanf("%d%d",&p[i].at,&p[i].bt)        ;
            p[i].pid=i+1;
            p[i].rem=p[i].bt;
            p[i].c=0;
    }
    printf("Enter the quanta: ");
    scanf("%d",&q);

    sort();
    robin();
    table();
}