#include<stdio.h>
#include<stdlib.h>
#define SIZE 200
int n;

void fcfs(int req[], int h){
    int seek=0;
    printf("\n--FCFS--\nHead movement:\n");
    for(int i=0;i<n;i++){        
        printf("%d->",h);
        seek+=abs(h-req[i]);
        h=req[i];
    }
    printf("%d",h);
    printf("\nTotal head Movement: %d",seek);
}

void scan(int req[], int h){
    int head,dir,seek=0,old;
    printf("\n--SCAN--\nHead movement:\n");
    for (int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    printf("Enter the scan direction(0-left 1-right): ");
    scanf("%d",&dir);
    if (dir){
        printf("%d->",h);
        for(int i=0;i<n;i++){
            if (req[i]>h){
                head=i;
                break;
            }
        }
        for(int i=head;i<n;i++){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        if (h!=SIZE-1){
            old=h;
            h=SIZE-1;
            printf("%d->",h);
            seek+=abs(old-h);
        }
        for(int i=head-1;i>=0;i--){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        printf("0");
        seek+=abs(h);
        printf("\nTotal head movement: %d",seek);
    }else{
        printf("%d->",h);
        for(int i=0;i<n;i++){
            if (req[i]>h){
                head=i-1;
                break;
            }
        }
        for(int i=head;i>=0;i--){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        if (h!=0){
            old=h;
            h=0;
            printf("%d->",h);
            seek+=abs(old);
        }
        for(int i=head+1;i<n;i++){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        if (h!=SIZE-1){
            old=h;
            h=SIZE-1;
            printf("%d",h);
            seek+=abs(old-h);
        }
        printf("\nTotal head movement: %d",seek);
    }
}

void sstf(int req[], int h){
    printf("\n--SSTF--\n");
    for (int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    int c,completed=0,seek=0;
    int t[20]={0};
    int head=h;
    printf("%d->",h);
    while(completed<n){
        int l=199;
        for(int i=0;i<n;i++){
            if(abs(req[i]-head)<l && t[i]==0){
                c=i;
                l=abs(req[i]-head);
            }
        }
        seek+=abs(head-req[c]);
        head=req[c];
        printf("%d->",head);
        t[c]=1;
        completed++;
    }
    printf("\nTotal head movement:%d ",seek);
}

void look(int req[], int h){
    int head,dir,seek=0,old;
    printf("\n--LOOK--\nHead movement:\n");
    for (int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    printf("Enter the look direction(0-left 1-right): ");
    scanf("%d",&dir);
    if (dir){
        printf("%d->",h);
        for(int i=0;i<n;i++){
            if (req[i]>h){
                head=i;
                break;
            }
        }
        for(int i=head;i<n;i++){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        for(int i=head-1;i>=0;i--){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        printf("\nTotal head movement: %d",seek);
    }else{
        printf("%d->",h);
        for(int i=0;i<n;i++){
            if (req[i]>h){
                head=i-1;
                break;
            }
        }
        for(int i=head;i>=0;i--){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        for(int i=head+1;i<n;i++){
            old=h;            
            h=req[i];
            printf("%d->",h);
            seek+=abs(old-h);
        }
        printf("\nTotal head movement: %d",seek);
    }
}

void main(){
    int req[20];
    int h;
    printf("Enter the no of requests: ");
    scanf("%d",&n);
    printf("Enter the requests\n");
    for(int i=0;i<n;i++){
        scanf("%d",&req[i]);        
    }
    printf("Enter the head position: ");
    scanf("%d",&h);
    fcfs(req, h);
    scan(req, h);
    sstf(req, h);
    look(req,h);
}