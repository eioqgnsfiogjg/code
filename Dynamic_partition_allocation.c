#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define Empty 0
#define Full 1
#define OK 0
#define True 0
#define False 1
int minSize=1;
typedef struct{
    int num;
    int size;
    int head;
    int status;
}ElemType;
typedef struct Node{
	ElemType data;
    struct Node* next;
    struct Node* prev;
} PageTable,*PT;
PT np;
int npm;
PT Init_List(){//返回头指针
    PT p;
    p=(PT)malloc(sizeof(PageTable));     /*分配一个结点*/
    if (p==NULL)
        printf("分配失败");                   /*分配失败*/
    p->next=NULL;
    p->prev=NULL;
	return p;
}
int Insert_last(PT Head,ElemType x){
    PT p,q,r;
	/*未初始化时，没有头指针没有数据域
	r=Head->next;
	while(r->next!=NULL)
	{
		r=r->next;
	}
	if(x.head<r->data.head+r->data.size)
	{
		printf("输入的分区头指针处于它的前一个分区，输入错误\n");
		return False;
	}
	*/
    p=(PT)malloc(sizeof(PageTable));               /*分配一个结点*/
    if (p==NULL)
        return False;                             /*分配失败*/
    /*赋值*/
    p->data.num=x.num;
    p->data.size=x.size;
    p->data.head=x.head;
    p->data.status=x.status;
    p->next= NULL;
    q=Head;//把链表头指针地址付给q
    while(q->next!=NULL)
        q=q->next;

    q->next=p;
	p->prev=q;
	p->next=NULL;
    return OK;
}
void SetNull(PT Head)                    /*清空线性表 */
{
    PT p,q;
    q=Head;
    p=q->next;                            /*p取头指针*/
    while(p!=NULL)
    {   q=p;                                       /*q指向p的前驱结点*/
        p=p->next;                                  /*p指向其后继结点*/
        free(q);
    }
    Head->next=NULL;                              /*设置头结点*/
}

int DeleteNode(PT hp,int num){
    PT p=hp->next;
    while(p->data.num!=num&&p->next!=NULL){
        p=p->next;
    }
    if(p->next!=NULL){
        p->prev->next=p->next;
        p->next->prev=p->prev;
        int size0=p->data.size;
        free(p);
        while(p->next!=NULL){
            p=p->next;
            p->data.head-=size0;
        }
        return True;
        }
    else if(p->next==NULL&&p!=NULL){//结尾
        p->prev->next=p->next;
        free(p);
        return True;
    }
    else{
        return False;
    }
}
int SortNum(PT hp)
{
	PT p;
	p=hp->next;
	if(p==NULL)
		return False;
	int count=0;
	while(p!=NULL)
	{
		p->data.num=count;
		count++;
		p=p->next;
	}
	return True;
}
int cycle(int num,PT hp)//回收
{
	PageTable *p=hp->next;
	//子函数在其后定义无法调用
	int min;
	while(p!=NULL)
	{
		//判断头结点和尾部节点的特殊情况
		if(p->data.num==num&&p->data.status==1)
		{
			if(p->data.num==0)
			{
				if(p->next->data.status==0)
				{
					p->data.size+=p->next->data.size;
					p->data.status=0;
					p->data.head=p->data.head>p->next->data.head?p->next->data.head:p->data.head;
					PT r=p->next;//应该保存下一个节点的地址，它在其后会被修改
					p->next=p->next->next;
					p->next->prev=p;
					free(r);
					return True;
				}
				else if(p->next->data.status==1)
				{
					p->data.status=0;
					return True;
				}
			}
			PT q=hp;//这里找到最后一个节点，这里不是双向循环链表
			while(q->next!=NULL)
			{
				q=q->next;
			}
			if(p->data.num==q->data.num)
			{
				if(p->prev->data.status==0)
				{
					p->prev->data.head=p->data.head>p->prev->data.head?p->prev->data.head:p->data.head;
					p->prev->data.size+=p->data.size;
					p->prev->next=NULL;

					free(p);
					return True;

				}
				else if(p->prev->data.status==1)
				{
					p->data.status=0;
					return True;
				}
			}
			//一般情况 Ok
			if(p->prev->data.status==0&&p->next->data.status==0)
			{
				p->prev->data.size=p->prev->data.size+p->next->data.size+p->data.size;
				min=p->data.head>p->next->data.head?p->next->data.head:p->data.head;
				p->prev->data.head=min<p->prev->data.head?min:p->prev->data.head;
				p->prev->next=p->next->next;
				free(p);
				free(p->next);
				return True;
			}
			else if(p->prev->data.status==0)
			{
				p->prev->data.size+=p->data.size;
				p->prev->data.head=p->data.head>p->prev->data.head?p->prev->data.head:p->data.head;
				p->prev->next=p->next;
				p->next->prev=p->prev;
				free(p);
				return True;

			}
			else if(p->next->data.status==0)
			{
				p->data.status=0;
				p->data.size+=p->next->data.size;
				p->data.head=p->data.head>p->next->data.head?p->next->data.head:p->data.head;
				PT n=p->next;
				p->next=p->next->next;
				n->next->prev=p;
				free(n);
				return True;
			}
			else{
				p->data.status=0;
				return True;
			}

		}
		p=p->next;
	}
	return False;
}

int Show(PT Head)        /*遍历线性表*/
    {
        PT p;
        printf("\n");
        p=Head->next;                      /*p指向第一个结点（非头结点）*/
        if (p==NULL)
            return False;
        while(p!= NULL)          /*未结束遍历*/
        {
            printf(" num:%d \t size:%d \t head:%d \tstatus:%d  \n",p->data.num, p->data.size,
            p->data.head,p->data.status);           /*输出数据*/
            p=p->next;                     /*p取后继结点的地址*/
        }
        return True;
    }

PT SortBF(PT L)
{
	/*
	PT j,i;
	for(i=hp->next->next;i->next!=NULL;i=i->next)
	{
		if(i->data.size<(i-1)->data.size)
		{
			hp->data.head=i->data.head;
			hp->data.num=i->data.num;
			hp->data.size=i->data.size;
			hp->data.status=i->data.status;
			j=i->prev;

			do {
				j->next->data.head=j->data.head;
				j->next->data.num=j->data.num;
				j->next->data.size=j->data.size;
				j->next->data.status=j->data.status;
				j=j->prev;
			}while(hp->data.size<j->data.size);
			j->next->data.head=hp->data.head;
			j->next->data.num=hp->data.num;
			j->next->data.size=hp->data.size;
			j->next->data.status=hp->data.status;
		}

	}
	*/


    PT first;     /*排列后有序链的表头指针*/
    PT tail;      /*排列后有序链的表尾指针*/
    PT p_min;     /*保留键值更小的节点的前驱节点的指针*/
    PT min;       /*存储最小节点*/
    PT p;         /*当前比较的节点*/

    first = NULL;
    while (L != NULL) /*在链表中找键值最小的节点。*/
    {
        /*注意：这里for语句就是体现选择排序思想的地方*/
        for (p=L,min=L; p->next!=NULL; p=p->next) /*循环遍历链表中的节点，找出此时最小的节点。*/
        {
            if (p->next->data.size < min->data.size) /*找到一个比当前min小的节点。*/
            {
                p_min = p; /*保存找到节点的前驱节点：显然p->next的前驱节点是p。*/
                min = p->next; /*保存键值更小的节点。*/
            }
        }

        /*上面for语句结束后，就要做两件事；
            一是把它放入有序链表中；
            二是根据相应的条件判断，安排它离开原来的链表。*/

        /*第一件事*/
        if (first == NULL) /*如果有序链表目前还是一个空链表*/
        {
            first = min; /*第一次找到键值最小的节点。*/
            tail = min; /*注意：尾指针让它指向最后的一个节点。*/
        }
        else /*有序链表中已经有节点*/
        {
            tail->next = min; /*把刚找到的最小节点放到最后，即让尾指针的next指向它。*/
            tail = min; /*尾指针也要指向它。*/
        }
        /*第二件事*/
        if (min == L) /*如果找到的最小节点就是第一个节点*/
        {
            //printf("表头%d已经是最小，当前结点后移。\n", min->data);
            L = L->next; /*显然让head指向原head->next,即第二个节点，就OK*/
        }
        else /*如果不是第一个节点*/
        {
            p_min->next = min->next; /*前次最小节点的next指向当前min的next,这样就让min离开了原链表。*/
        }
    }
    if (first != NULL) /*循环结束得到有序链表first*/
    {
        tail->next = NULL; /*单向链表的最后一个节点的next应该指向NULL*/
    }
    L = first;
    return L;
}

PT SortWF(PT L)
{
	/*
	PT j,i;
	for(i=hp->next->next;i->next!=NULL;i=i->next)
	{
		if(i->data.size<(i-1)->data.size)
		{
			hp->data.head=i->data.head;
			hp->data.num=i->data.num;
			hp->data.size=i->data.size;
			hp->data.status=i->data.status;
			j=i->prev;

			do {
				j->next->data.head=j->data.head;
				j->next->data.num=j->data.num;
				j->next->data.size=j->data.size;
				j->next->data.status=j->data.status;
				j=j->prev;
			}while(hp->data.size<j->data.size);
			j->next->data.head=hp->data.head;
			j->next->data.num=hp->data.num;
			j->next->data.size=hp->data.size;
			j->next->data.status=hp->data.status;
		}

	}
	*/


    PT first;     /*排列后有序链的表头指针*/
    PT tail;      /*排列后有序链的表尾指针*/
    PT p_min;     /*保留键值更小的节点的前驱节点的指针*/
    PT min;       /*存储最小节点*/
    PT p;         /*当前比较的节点*/

    first = NULL;
    while (L != NULL) /*在链表中找键值最小的节点。*/
    {
        /*注意：这里for语句就是体现选择排序思想的地方*/
        for (p=L,min=L; p->next!=NULL; p=p->next) /*循环遍历链表中的节点，找出此时最小的节点。*/
        {
            if (p->next->data.size > min->data.size) /*找到一个比当前min小的节点。*/
            {
                p_min = p; /*保存找到节点的前驱节点：显然p->next的前驱节点是p。*/
                min = p->next; /*保存键值更小的节点。*/
            }
        }

        /*上面for语句结束后，就要做两件事；
            一是把它放入有序链表中；
            二是根据相应的条件判断，安排它离开原来的链表。*/

        /*第一件事*/
        if (first == NULL) /*如果有序链表目前还是一个空链表*/
        {
            first = min; /*第一次找到键值最小的节点。*/
            tail = min; /*注意：尾指针让它指向最后的一个节点。*/
        }
        else /*有序链表中已经有节点*/
        {
            tail->next = min; /*把刚找到的最小节点放到最后，即让尾指针的next指向它。*/
            tail = min; /*尾指针也要指向它。*/
        }
        /*第二件事*/
        if (min == L) /*如果找到的最小节点就是第一个节点*/
        {
            //printf("表头%d已经是最小，当前结点后移。\n", min->data);
            L = L->next; /*显然让head指向原head->next,即第二个节点，就OK*/
        }
        else /*如果不是第一个节点*/
        {
            p_min->next = min->next; /*前次最小节点的next指向当前min的next,这样就让min离开了原链表。*/
        }
    }
    if (first != NULL) /*循环结束得到有序链表first*/
    {
        tail->next = NULL; /*单向链表的最后一个节点的next应该指向NULL*/
    }
    L = first;
    return L;
}

int BestFit(int num,PT hp)
{
	PT headp=SortBF(hp);
	if(allocate(num,headp)==True)
		return True;
	else
		return False;

}
int FirstFit(int num,PT hp)
{
	if(allocate(num,hp)==True)
		return True;
	else
		return False;

}
int NextFit(int num,PT hp)
{
	if(allocate(num,hp)==True)
		return True;
	else
		return False;
}
int WorstFit(int num,PT hp)
{

	PT headp=SortWF(hp);
	if(allocate(num,headp)==True)
		return True;
	else
		return False;

}
int allocate(int size,PT hp)
{
	PageTable *p=hp->next;
	while(p!=NULL)
	{
        if(size<=p->data.size)
        {
            if(p->data.size-size>minSize)
            {
                p->data.size-=size;
				/*原意是将p指向的分区后的分区num++,避免num重复，但是由于firstFit的Sort导致出现num不按顺序的情况，故用SortNum代替
                PT r;
                r=p;
                while(r->next!=NULL){
                    r=r->next;
                    r->data.num++;
                }
                */
               //sontnum重新排列num
                PT q=(PT)malloc(sizeof(PageTable));//新建不空闲的分区，放在p指向的空闲区的后面，数据域的填充
                q->data.size=size;
                q->data.status=1;
                q->data.head=p->data.head+p->data.size;
                q->data.num=p->data.num+1;
                PT r;//r保存p的指针，让q在p后，q的指针域指向p的后一个链表节点 ，指针域的填充
                r=p->next;//p没有改变，改变的是p->next，所以应该保留p->next
                p->next=q;
                q->prev=p;//双向链需要补充prev的指针域
                q->next=r;
                npm=q->data.num;
                return True;
            }
            else {
            	p->data.status=1;
            	npm=p->data.num;
            	return True;
			}

        }
        p=p->next;

	}
	return False;
}
int main(){
    PT Head;
    Head=Init_List();
    PT np=Head;
    ElemType x;
    int i;
    do{
    	if(SortNum(Head)==False||Show(Head)==False)
			printf("\n空表！ NULL");

        printf("请输入：数字\n");
        printf("1.初始化分区表\n");
        printf("2.动态分配分区表的存储空间\n");
        printf("3.动态回收分区表的存储空间\n");
        printf("4.删除回收分区表的存储空间\n");
        printf("0.退出\n");
        scanf("%d",&i);
        switch(i)
        {
            case 0:
                break;
            case 1:
            {
                if(Head->next==NULL){
                    SetNull(Head);
                }
                else{
                    break;
                }
                int num0;
                int sizeWithHead;
                printf("请输入分区数\n");
                scanf("%d",&num0);
                int j;
                for(j=0;j<num0;j++){

                	x.num=j;
                	if(j>0){
                        sizeWithHead=x.head+x.size;
                	}
                    printf("请输入分区%d大小\n",j);
                    scanf("%d",&x.size);
                    if(x.size<=0)
					{
						printf("分区大小不能为0或者是负数\n");
						break;
					}
					if(j==0){
                        printf("请输入分区%d起始地址\n",j);
                        scanf("%d",&x.head);
					}
                    else{
                        x.head=sizeWithHead;
                    }

                    x.status=Empty;
                    if(Insert_last(Head,x)!=OK){
                        printf("插入失败\n");
                    }
                }

                break;
            }
            case 2:
            {

                int num1;
                char ch;
                printf("请输入要分配的数据的长度\n");
                scanf("%d",&num1);
                printf("请输入要选用的算法（F，N，B，W)\n");
                getchar();
                scanf("%c",&ch);
                switch(ch)
                {
                	case 'B':
                		if(BestFit(num1,Head)!=True)
                    		printf("分配失败或没有分配空间\n");
                    	break;
                	case 'F':
                		if(FirstFit(num1,Head)!=True)
                    		printf("分配失败或没有分配空间\n");
                    	break;
                    case 'W':
                    	if(WorstFit(num1,Head)!=True)
                    		printf("分配失败或没有分配空间\n");
                    	break;
                    case 'N':
                    	if(NextFit(num1,np)!=True)
                    		printf("分配失败或没有分配空间\n");
                    	break;
                    default:
                    	printf("error!\n");
                    	break;
				}
				int np_m;
				PT r=Head->next;
				for(np_m=0;np_m<npm;np_m++){
                    r=r->next;
				}
				np=r;

                break;
        	}
            case 3:
            {
                int num2;
                printf("请输入要回收的的块号\n");
                scanf("%d",&num2);
                if(cycle(num2,Head)==False)
					printf("没有找到该块，或者它是空闲区,回收失败\n");
				else
					printf("回收成功\n");
                break;
            }
            case 4:{
                int num;
                num=0;
                printf("请输入删除第几个分区");
                scanf("%d",&num);
                if(DeleteNode(Head,num)==True){
                    printf("删除成功");
                }
                else{
                    printf("删除失败");
                }
            }
        }
    }while(i!=0);
	SetNull(Head);
	return 0;
}
