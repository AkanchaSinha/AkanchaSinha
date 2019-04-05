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
    printf("Welcome to Ratnabh's Program for Banker's Algorithm\n");
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

