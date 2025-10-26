#include<stdio.h>

struct process{
    int pid, at, bt, tat, ct, wt, c;
}p[20];
int n;
int arr[20];
float t=0,w=0;

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

void display(){
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\t");
    for(int i=0;i<n;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\n\nAvg tat: %f\nAvg wt: %f",(t/n),(w/n));
}

void calc(){
    printf("Gantt---\n");
    int ct=p[0].at, top=0;
    int completed=0;    
    while(completed<n){
        int f=0;
        for(int i=0;i<n;i++){
            if(p[i].at<=ct && p[i].c==0){
                int si=i;
                for(int j=i;j<n;j++){
                    if(p[j].bt<p[si].bt && p[j].c==0 && p[j].at<=ct){
                        si=j;
                    }
                }
                p[si].ct=ct+p[si].bt;
                p[si].tat=p[si].ct-p[si].at;
                p[si].wt=p[si].tat-p[si].bt;
                ct+=p[si].bt;
                completed++;
                f=1;
                p[si].c=1;
                t+=p[si].tat;
                w+=p[si].wt;
                printf("|\tp%d\t",p[si].pid);
                arr[top++]=p[si].ct;
            }
        }
        if(!f){
            for (int i=0;i<n;i++){
                if(p[i].c==0&&p[i].at>ct){
                    ct=p[i].at;
                    break;
                }
            }
        }
    }
    printf("\n0\t");
    for(int i=0;i<n;i++){
        printf("\t%d\t",arr[i]);
    }
}

void main(){
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("\nEnter process at and bt: ");
    for (int i=0;i<n;i++){
        p[i].pid=i+1;
        p[i].c=0;
        scanf("%d%d",&p[i].at,&p[i].bt);
    }
    sort();
    calc();
    display();
}