#include<stdio.h>
int n=3,m=3,i=0,j;

int AvailableResources[3]={3,2,2};
int AllocatedResources[][3]={{0,0,1},{3,2,0},{2,1,1}};
int MaxNeed[][3]={{8,4,3},{6,2,0},{3,3,3}};
int CurrentNeed[3][3];
int SafetySeq[3];
_Bool End[3]={0,0,0};
