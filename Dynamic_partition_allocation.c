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
PT Init_List(){//����ͷָ��
    PT p;
    p=(PT)malloc(sizeof(PageTable));     /*����һ�����*/
    if (p==NULL)
        printf("����ʧ��");                   /*����ʧ��*/
    p->next=NULL;
    p->prev=NULL;
	return p;
}
int Insert_last(PT Head,ElemType x){
    PT p,q,r;
	/*δ��ʼ��ʱ��û��ͷָ��û��������
	r=Head->next;
	while(r->next!=NULL)
	{
		r=r->next;
	}
	if(x.head<r->data.head+r->data.size)
	{
		printf("����ķ���ͷָ�봦������ǰһ���������������\n");
		return False;
	}
	*/
    p=(PT)malloc(sizeof(PageTable));               /*����һ�����*/
    if (p==NULL)
        return False;                             /*����ʧ��*/
    /*��ֵ*/
    p->data.num=x.num;
    p->data.size=x.size;
    p->data.head=x.head;
    p->data.status=x.status;
    p->next= NULL;
    q=Head;//������ͷָ���ַ����q
    while(q->next!=NULL)
        q=q->next;

    q->next=p;
	p->prev=q;
	p->next=NULL;
    return OK;
}
void SetNull(PT Head)                    /*������Ա� */
{
    PT p,q;
    q=Head;
    p=q->next;                            /*pȡͷָ��*/
    while(p!=NULL)
    {   q=p;                                       /*qָ��p��ǰ�����*/
        p=p->next;                                  /*pָ�����̽��*/
        free(q);
    }
    Head->next=NULL;                              /*����ͷ���*/
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
    else if(p->next==NULL&&p!=NULL){//��β
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
int cycle(int num,PT hp)//����
{
	PageTable *p=hp->next;
	//�Ӻ�����������޷�����
	int min;
	while(p!=NULL)
	{
		//�ж�ͷ����β���ڵ���������
		if(p->data.num==num&&p->data.status==1)
		{
			if(p->data.num==0)
			{
				if(p->next->data.status==0)
				{
					p->data.size+=p->next->data.size;
					p->data.status=0;
					p->data.head=p->data.head>p->next->data.head?p->next->data.head:p->data.head;
					PT r=p->next;//Ӧ�ñ�����һ���ڵ�ĵ�ַ���������ᱻ�޸�
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
			PT q=hp;//�����ҵ����һ���ڵ㣬���ﲻ��˫��ѭ������
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
			//һ����� Ok
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

int Show(PT Head)        /*�������Ա�*/
    {
        PT p;
        printf("\n");
        p=Head->next;                      /*pָ���һ����㣨��ͷ��㣩*/
        if (p==NULL)
            return False;
        while(p!= NULL)          /*δ��������*/
        {
            printf(" num:%d \t size:%d \t head:%d \tstatus:%d  \n",p->data.num, p->data.size,
            p->data.head,p->data.status);           /*�������*/
            p=p->next;                     /*pȡ��̽��ĵ�ַ*/
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


    PT first;     /*���к��������ı�ͷָ��*/
    PT tail;      /*���к��������ı�βָ��*/
    PT p_min;     /*������ֵ��С�Ľڵ��ǰ���ڵ��ָ��*/
    PT min;       /*�洢��С�ڵ�*/
    PT p;         /*��ǰ�ȽϵĽڵ�*/

    first = NULL;
    while (L != NULL) /*���������Ҽ�ֵ��С�Ľڵ㡣*/
    {
        /*ע�⣺����for����������ѡ������˼��ĵط�*/
        for (p=L,min=L; p->next!=NULL; p=p->next) /*ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ㡣*/
        {
            if (p->next->data.size < min->data.size) /*�ҵ�һ���ȵ�ǰminС�Ľڵ㡣*/
            {
                p_min = p; /*�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p��*/
                min = p->next; /*�����ֵ��С�Ľڵ㡣*/
            }
        }

        /*����for�������󣬾�Ҫ�������£�
            һ�ǰ����������������У�
            ���Ǹ�����Ӧ�������жϣ��������뿪ԭ��������*/

        /*��һ����*/
        if (first == NULL) /*�����������Ŀǰ����һ��������*/
        {
            first = min; /*��һ���ҵ���ֵ��С�Ľڵ㡣*/
            tail = min; /*ע�⣺βָ������ָ������һ���ڵ㡣*/
        }
        else /*�����������Ѿ��нڵ�*/
        {
            tail->next = min; /*�Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ������*/
            tail = min; /*βָ��ҲҪָ������*/
        }
        /*�ڶ�����*/
        if (min == L) /*����ҵ�����С�ڵ���ǵ�һ���ڵ�*/
        {
            //printf("��ͷ%d�Ѿ�����С����ǰ�����ơ�\n", min->data);
            L = L->next; /*��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK*/
        }
        else /*������ǵ�һ���ڵ�*/
        {
            p_min->next = min->next; /*ǰ����С�ڵ��nextָ��ǰmin��next,��������min�뿪��ԭ����*/
        }
    }
    if (first != NULL) /*ѭ�������õ���������first*/
    {
        tail->next = NULL; /*������������һ���ڵ��nextӦ��ָ��NULL*/
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


    PT first;     /*���к��������ı�ͷָ��*/
    PT tail;      /*���к��������ı�βָ��*/
    PT p_min;     /*������ֵ��С�Ľڵ��ǰ���ڵ��ָ��*/
    PT min;       /*�洢��С�ڵ�*/
    PT p;         /*��ǰ�ȽϵĽڵ�*/

    first = NULL;
    while (L != NULL) /*���������Ҽ�ֵ��С�Ľڵ㡣*/
    {
        /*ע�⣺����for����������ѡ������˼��ĵط�*/
        for (p=L,min=L; p->next!=NULL; p=p->next) /*ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ㡣*/
        {
            if (p->next->data.size > min->data.size) /*�ҵ�һ���ȵ�ǰminС�Ľڵ㡣*/
            {
                p_min = p; /*�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p��*/
                min = p->next; /*�����ֵ��С�Ľڵ㡣*/
            }
        }

        /*����for�������󣬾�Ҫ�������£�
            һ�ǰ����������������У�
            ���Ǹ�����Ӧ�������жϣ��������뿪ԭ��������*/

        /*��һ����*/
        if (first == NULL) /*�����������Ŀǰ����һ��������*/
        {
            first = min; /*��һ���ҵ���ֵ��С�Ľڵ㡣*/
            tail = min; /*ע�⣺βָ������ָ������һ���ڵ㡣*/
        }
        else /*�����������Ѿ��нڵ�*/
        {
            tail->next = min; /*�Ѹ��ҵ�����С�ڵ�ŵ���󣬼���βָ���nextָ������*/
            tail = min; /*βָ��ҲҪָ������*/
        }
        /*�ڶ�����*/
        if (min == L) /*����ҵ�����С�ڵ���ǵ�һ���ڵ�*/
        {
            //printf("��ͷ%d�Ѿ�����С����ǰ�����ơ�\n", min->data);
            L = L->next; /*��Ȼ��headָ��ԭhead->next,���ڶ����ڵ㣬��OK*/
        }
        else /*������ǵ�һ���ڵ�*/
        {
            p_min->next = min->next; /*ǰ����С�ڵ��nextָ��ǰmin��next,��������min�뿪��ԭ����*/
        }
    }
    if (first != NULL) /*ѭ�������õ���������first*/
    {
        tail->next = NULL; /*������������һ���ڵ��nextӦ��ָ��NULL*/
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
				/*ԭ���ǽ�pָ��ķ�����ķ���num++,����num�ظ�����������firstFit��Sort���³���num����˳������������SortNum����
                PT r;
                r=p;
                while(r->next!=NULL){
                    r=r->next;
                    r->data.num++;
                }
                */
               //sontnum��������num
                PT q=(PT)malloc(sizeof(PageTable));//�½������еķ���������pָ��Ŀ������ĺ��棬����������
                q->data.size=size;
                q->data.status=1;
                q->data.head=p->data.head+p->data.size;
                q->data.num=p->data.num+1;
                PT r;//r����p��ָ�룬��q��p��q��ָ����ָ��p�ĺ�һ������ڵ� ��ָ��������
                r=p->next;//pû�иı䣬�ı����p->next������Ӧ�ñ���p->next
                p->next=q;
                q->prev=p;//˫������Ҫ����prev��ָ����
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
			printf("\n�ձ� NULL");

        printf("�����룺����\n");
        printf("1.��ʼ��������\n");
        printf("2.��̬���������Ĵ洢�ռ�\n");
        printf("3.��̬���շ�����Ĵ洢�ռ�\n");
        printf("4.ɾ�����շ�����Ĵ洢�ռ�\n");
        printf("0.�˳�\n");
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
                printf("�����������\n");
                scanf("%d",&num0);
                int j;
                for(j=0;j<num0;j++){

                	x.num=j;
                	if(j>0){
                        sizeWithHead=x.head+x.size;
                	}
                    printf("���������%d��С\n",j);
                    scanf("%d",&x.size);
                    if(x.size<=0)
					{
						printf("������С����Ϊ0�����Ǹ���\n");
						break;
					}
					if(j==0){
                        printf("���������%d��ʼ��ַ\n",j);
                        scanf("%d",&x.head);
					}
                    else{
                        x.head=sizeWithHead;
                    }

                    x.status=Empty;
                    if(Insert_last(Head,x)!=OK){
                        printf("����ʧ��\n");
                    }
                }

                break;
            }
            case 2:
            {

                int num1;
                char ch;
                printf("������Ҫ��������ݵĳ���\n");
                scanf("%d",&num1);
                printf("������Ҫѡ�õ��㷨��F��N��B��W)\n");
                getchar();
                scanf("%c",&ch);
                switch(ch)
                {
                	case 'B':
                		if(BestFit(num1,Head)!=True)
                    		printf("����ʧ�ܻ�û�з���ռ�\n");
                    	break;
                	case 'F':
                		if(FirstFit(num1,Head)!=True)
                    		printf("����ʧ�ܻ�û�з���ռ�\n");
                    	break;
                    case 'W':
                    	if(WorstFit(num1,Head)!=True)
                    		printf("����ʧ�ܻ�û�з���ռ�\n");
                    	break;
                    case 'N':
                    	if(NextFit(num1,np)!=True)
                    		printf("����ʧ�ܻ�û�з���ռ�\n");
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
                printf("������Ҫ���յĵĿ��\n");
                scanf("%d",&num2);
                if(cycle(num2,Head)==False)
					printf("û���ҵ��ÿ飬�������ǿ�����,����ʧ��\n");
				else
					printf("���ճɹ�\n");
                break;
            }
            case 4:{
                int num;
                num=0;
                printf("������ɾ���ڼ�������");
                scanf("%d",&num);
                if(DeleteNode(Head,num)==True){
                    printf("ɾ���ɹ�");
                }
                else{
                    printf("ɾ��ʧ��");
                }
            }
        }
    }while(i!=0);
	SetNull(Head);
	return 0;
}
