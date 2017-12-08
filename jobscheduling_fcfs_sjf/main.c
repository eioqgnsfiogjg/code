#include <stdio.h>
#include <String.h>
#include <malloc.h>
#define OverFlow -1
#define UnderFlow -2
#define OK 1
#define True 1
#define False -1


typedef struct PCB
{
    int ID;                         //标识符
    int ComeTime;                   //到达时间
    int ServerTime;                 //服务时间
    int FinishTime;                 //完成时间
    int TurnOverTime;               //周转时间
    double WeightedTOTime;    //带权周转时间
} PCB;

typedef struct PCBlist{
    struct PCBlist *next;
    PCB data;
} PCBL,*PCBL_pointer;

PCBL_pointer Init_PCBL()
{
    PCBL *p;
    p=(PCBL *)malloc(sizeof(PCBL));     /*分配一个结点*/
    if (p==NULL)
        return NULL;                    /*分配失败*/
    p->next=NULL;
	return p;
}
int Empty_PCBL(PCBL *L_pointer)
{
    if(L_pointer==NULL)
        return True;
    else
        return False;
}
PCBL_pointer Push_PCB(PCBL *L_pointer,PCB x)
{
    PCBL *p;
    p=(PCBL_pointer)malloc(sizeof(PCBL));
    p->data.ID=x.ID;
    p->data.ComeTime=x.ComeTime;
    p->data.ServerTime=x.ServerTime;
    p->next=L_pointer;
    L_pointer=p;
    return L_pointer;
}
/*int Pop_PCBL(PCBL *L_pointer,int x_id)
{
    PCBL *p,*q;
    p=L_pointer;
    q=p;
    while(p->next!=NULL)
    {

        if(p->data.ID==x_id)
        {
          q->next=p->next;
          free(p);
          return OK;
        }
        else
        {
            q=p;
            p=p->next;
        }
    }
    return False;
}*/
/*
int GetTop_PCBL(PCBL *L_pointer,PCB *x_pointer)
{
    if(Empty_LinkStack(*L_pointer)==True)
        return UnderFlow;
    else
    {
        *x_pointer=(*L_pointer)->data;
        return *x_pointer;
    }
}
*/
 
void SetNull_PCBL(PCBL *L_pointer)
{
    PCBL *p,*q;
    p=L_pointer;
    while(p!=NULL)
    {
        q=p;
        p=p->next;
        free(q);
    }
    L_pointer=NULL;
}
int Locate(PCBL *L_pointer,int x_id)
{
    PCBL *p;
    p=L_pointer;
    while(p!=NULL)
    {
        if(p->data.ID==x_id)
        {
            printf("进程id号%d\n到达时间%d\n服务时间%d\n完成时间%d\n周转时间%d\n带权周转时间%f\n",p->data.ID,p->data.ComeTime,p->data.ServerTime,p->data.FinishTime,p->data.TurnOverTime,p->data.WeightedTOTime);
            return OK;
        }
        else
            p=p->next;
    }
    return False;
}
void Show(PCBL *L_pointer)
{
    PCBL *p;
    p=L_pointer;
    printf("进程id\t到达时间\t服务时间\t完成时间\t周转时间\t带权周转时间\n");
    if(p==NULL)
        return;
    while(p->next!=NULL)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%f\n",p->data.ID,p->data.ComeTime,p->data.ServerTime,p->data.FinishTime,p->data.TurnOverTime,p->data.WeightedTOTime);
        p=p->next;
    }
}

void FCFS(PCBL *L_pointer)
{
   int FinishTime=-1;
   PCBL *p,*q,*temp;
   p=L_pointer;
	/*q=p;
   
   while(p->next!=NULL)
   {
   	   
       p=p->next;

       if(q->data.ComeTime>p->data.ComeTime)
        {
            q->next=p->next;
            p->next=q;
            p=q;
        }
        else
        	q=p;
		
   }*/

   while(p!=NULL)
   {

       if(p->data.ComeTime<FinishTime)
       {
           p->data.FinishTime=q->data.FinishTime+p->data.ServerTime;
       }
       else
       {
           p->data.FinishTime=p->data.ComeTime+p->data.ServerTime;
       }

        p->data.TurnOverTime=p->data.FinishTime-p->data.ComeTime;
        p->data.WeightedTOTime=(double)p->data.TurnOverTime/p->data.ServerTime;
        FinishTime=p->data.FinishTime;

       q=p;
       p=p->next;
   }

}
int main()
{
    int i,m,loc_id,del_id;
    PCBL *Head;
    Head=Init_PCBL();
    PCB x;
    printf("请输入进程数\n");
    scanf("%d",&m);
    do
    {
        printf ("1---增加一个进程(Insert)\n");
        printf ("2---查询一个进程(Locate)\n");
        printf ("3---删除一个进程(Delete)\n");
        printf ("4---显示所有进程(Show)\n");
        printf ("5---先来先服务\n");
        printf ("0---退出\n");
        printf("请输入操作号\n");
        scanf ("%d",&i);
        switch(i)
        {
        case 1:
            printf("请输入进程的ID号,到达时间,服务时间\n");
            scanf("%d,%d,%d",&x.ID,&x.ComeTime,&x.ServerTime);
            
            Head=Push_PCB(Head,x);
            break;
        case 2:
            printf("请输入要查找进程的Id号\n");
            scanf("%d",&loc_id);
            if(Locate(Head,loc_id)==OK)
            {
                printf("查找成功\n");
            }
            else
                printf("查找错误\n");
            break;
        /*case 3:
            printf("请输入要删除进程的id\n");
            scanf("%d",&del_id);
            if(Pop_PCBL(Head,del_id)==OK)
                printf("删除成功\n");
            else
                printf("删除失败\n");
            break;*/
        case 4:
            Show(Head);
            break;
        case 5:
            FCFS(Head);
            break;
        case 0:
            break;
        default:
            printf("错误\n");
            break;
        }
    } while(i!=0);
    SetNull_PCBL(Head);

    return 0;
}
