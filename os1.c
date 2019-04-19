#include<stdio.h>
int n=3,m=3,i=0,j;

int AvailableResources[3]={3,2,2};
int AllocatedResources[][3]={{0,0,1},{3,2,0},{2,1,1}};
int MaxNeed[][3]={{8,4,3},{6,2,0},{3,3,3}};
int CurrentNeed[3][3];
int SafetySeq[3];
_Bool End[3]={0,0,0};

int *AllocatedResv,*ResAllocl,*ProcessMx,*ProcessNd;

void TableDisplay();
int CheckingAlgorithm(int,int *);
int RequestingAlgorithm(int,int *);
_Bool SafeAlgorithm(int pid);
void NeedCalculator();
int SafeSeqCreate();
void SafetySequenceDisplay();

int main(){
    printf("Welcome\n");
    NeedCalculator();
    TableDisplay();
    int *REQ,Arr[3],prc;
    printf("Enter Processes: 0, 1 & 2\n");scanf("%d",&prc);
    printf("Enter Resource Request: ");
    scanf("%d",&Arr[0]);scanf("%d",&Arr[1]);scanf("%d",&Arr[2]);
    REQ=Arr;
    printf("For Process P%d checking Request\n",prc);
    CheckingAlgorithm(prc,REQ);
    TableDisplay();
}
int CheckingAlgorithm(int processID,int *REQ){
    if(RequestingAlgorithm(processID,REQ)==1)TableDisplay();
    else{
        printf("Request was not satisfied\n");
        return 0;
    }
    printf("Now checking safety\n");
    if(SafeSeqCreate()!=0)SafetySequenceDisplay();
    else printf(" A safe sequence is not possible.\n");
}
int RequestingAlgorithm(int processID,int *REQ){
    AllocatedResv=AvailableResources;
    ResAllocl=AllocatedResources[processID];
    ProcessNd=CurrentNeed[processID];
    for(i=0;i<m;i++){
        if(*(REQ+i)>*(ProcessNd+i))return 0;
        if(*(REQ+i)>*(AllocatedResv+i))return 0;
    }
    printf("Request is possible!\n");
    for(i=0;i<m;i++){
        *(ResAllocl+i)+=*(REQ+i);
        *(AllocatedResv+i)-=*(REQ+i);
        *(ProcessNd+i)-=*(REQ+i);
    }
    return 1;
}
_Bool SafeAlgorithm(int processID){
    printf("Possible Process to Run: P%d\n",processID);
    AllocatedResv=AvailableResources;
    ResAllocl=AllocatedResources[processID];
    for(i=0;i<3;i++){
        *(AllocatedResv+i)+=*(ResAllocl+i);
        *(ResAllocl+i)=0;
        *(ProcessNd+i)=0;
    }
    return 1;
}
int SafeSeqCreate(){
    int *W=AvailableResources,flag;
    int *Sequence=SafetySeq,k=0,g=0;
    _Bool *F=End;
    for(i=0;i<10;i++){
        k=i%3;
        if(*(F+k)==1)

continue;
        ProcessNd=CurrentNeed[k];
        flag=1;
        printf("Need:");
        for(j=0;j<3;j++){
            printf(" %d",*(ProcessNd+j));
            if(*(ProcessNd+j)>*(W+j))flag=0;
        }
        printf("\n");
        if(flag==1){
            *(F+k)=SafeAlgorithm(k);
            *(Sequence+(g++))=k;
            TableDisplay();        
        }
        else *(F+k)=0;
        if(*(F)&*(F+1)&*(F+2)==1)return 1;
    }
    return 0;
}
void SafetySequenceDisplay(){
    int *Sequence=SafetySeq,i;
    printf("Safety Sequence:");
    printf("<");for(i=0;i<3;i++)printf("%d,",*(Sequence+i));printf(">\n");
}
void NeedCalculator(){
    int processID,i,j;
    for(processID=0;processID<n;processID++){
        ProcessNd=CurrentNeed[processID];
        ResAllocl=AllocatedResources[processID];
        ProcessMx=MaxNeed[processID];
        for(i=0;i<m;i++){
            *(ProcessNd+i)=*(ProcessMx+i)-*(ResAllocl+i);
        }
    }
}
void TableDisplay(){
    int i,j;
    printf("\nProcess\tMaximum\t\tAllocated\tNeed\t\tAvailable\n");
      for(j=0;j<n;j++){
        ResAllocl=AllocatedResources[j];
        AllocatedResv=AvailableResources;
        ProcessMx=MaxNeed[j];
        ProcessNd=CurrentNeed[j];
        printf("P%d\t",j);
        for(i=0;i<m;i++){
            printf("%d ",*(ProcessMx+i));
        }
        printf("\t\t");
        for(i=0;i<m;i++){
            printf("%d ",*(ResAllocl+i));
        }
        printf("\t\t");
        for(i=0;i<m;i++){
            printf("%d ",*(ProcessNd+i));
        }
        printf("\t\t");
        printf("R%d: %d ",j,*(AllocatedResv+j));
        printf("\n");
    }
    printf("\n");
}
