#include<stdio.h>
struct process
{
    int pid, at, bt, ct, tat, wt, pri, c;
}p[20];
int n;
float t=0,w=0;
int arr[20];

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
    printf("Gantt--\n");
    int completed=0;
    int ct=0, top=0;
    while(completed<n){
        int f=0;
        for(int i=0;i<n;i++){
            if(p[i].at<=ct && p[i].c==0){
                int si=i;
                for(int j=0;j<n;j++){
                    if(p[j].pri<p[si].pri && p[j].at<=ct && p[j].c==0){
                        si=j;
                    }
                }
                p[si].ct=ct+p[si].bt;
                p[si].tat=p[si].ct-p[si].at;
                p[si].wt=p[si].tat-p[si].bt;
                t+=p[si].tat;
                w+=p[si].wt;
                printf("|\tp%d\t",p[si].pid);                
                ct=p[si].ct;
                arr[top++]=ct;
                completed++;
                p[si].c=1;
                f=1;
            }
        }
        if(!f){
            for(int i=0;i<n;i++){
                if(p[i].at>ct && p[i].c==0){
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

void display(){
    printf("\nPID\tAT\tBT\tPRI\tCT\tTAT\tWT");
    for(int i=0;i<n;i++){
        printf("\n%d\t%d\t%d\t%d\t%d\t%d\t%d",p[i].pid,p[i].at,p[i].bt,p[i].pri,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\n\nAvg tat: %f\nAvg wt: %f",(t/n),(w/n));
}

void main(){
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    printf("Enter the at, bt and priority:\n");
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        p[i].c=0;
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pri);
    }
    sort();
    calc();
    display();
}
