#include <stdio.h>
#include <stdlib.h>

#define true 0
#define false 1


#define N 100
#define M 100

int compare(int* need,int* work,int b){
    int flag = true;
    int t;
    for(t = 0; t < b;t++){
        if(*(need+t) > *(work+t)){
            flag = false;
        }
    }
    if(flag==true){
        return true;
    }
    else{
        return false;
    }
}
int safe(int *max,int *allocation,int *need,int *available,int m,int n){//m��Դ��������n������

    int *work;
    int b;
    work = (int*)malloc(m*sizeof(int));
    for(b = 0;b < m; b++){
        *(work+b) = *(available+b);
    }

    int i;
    int *safelist;
    safelist = (int*)malloc(n*sizeof(int));
    int *finish;
    finish = (int*)malloc(n*sizeof(int));
    int a;
    for(a = 0;a < n;a++){
        *(finish + a ) = false;
    }//finish��ʼ��


	int j=0;
	for( i=0 ;i < n ;i++){//n������ ѭ��
		if( *( finish + i ) == false){
			if(compare(need+i*M,work,m) == true){

                for(b = 0;b < m;b++){
                    *( work + b ) += *(allocation+i*M+b);
                }
				// work->A += allocation[i].A;
				// work->B += allocation[i].B;
				// work->C += allocation[i].C;
				*( finish + i ) = true;
				*( safelist + ( j++ ) )=i;
				i = -1;
			}

		}
    }

	int flag = true;
	for(i = 0;i < n;i++){
		if(*( finish + i )==false){
			flag=false;
		}
	}
	if(flag == false){
		printf("����ȫ\n");
		free(safelist);
		free(work);
		free(finish);
		return false;
	}
	else{
		printf("��ȫ����Ϊ\n" );
		for(i=0;i<n;i++){
			printf("%d\n", *( safelist+i ) );
        }
        free(safelist);
		free(work);
		free(finish);
        return true;
	}

}

int main()
{
    int i,j,n,m,menu,proc;
    printf("�����������n\n");
    scanf("%d",&n);
    printf("��������Դ������\n");
    scanf("%d",&m);


    //�����ĸ����ݽṹ�����г�ʼ��
    int Available[M];
    int Max[N][M];
    int Allocation[N][M];
    int Need[N][M];
    int Request[M];


    do {
        printf("������ȫ����������ԴAvailable\n");
        for(i = 0;i < m;i++)
        {
            scanf("%d",&Available[i]);
        }
        printf("�����������Ҫ��Դ�������ĿMax(%d*%d)\n",n,m);
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
            {
                scanf("%d",&Max[i][j]);
            }
        }
        printf("����������Ѿ�������Դ����ĿAllocation(%d*%d)\n",n,m);
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
            {
                scanf("%d",&Allocation[i][j]);

            }
        }
        for(i = 0;i < n;i++)
        {
            for(j = 0;j < m;j++)
            {

                Need[i][j] = Max[i][j] - Allocation[i][j];
            }
        }

    } while(safe((int *)Max,(int *)Allocation,(int *)Need,(int *)Available,m,n) == false);



    do {
             //��ʾ�������Դ����
        A:
        printf("******��Դ�����*******************\n");
        printf("������\tMax\t\tAllocation\tNeed\t\tAvailable\n");
		printf("\t");
		for(i = 0;i < 4;i++)
		{

			for(j = 0;j < m;j++)
			{
				printf("%d ",j);
				if(j == m-1)
				printf("\t\t");
			}

		 }
		 printf("\n");
		 for(i = 0;i < n;i++)
		 {
            printf("%d\t",i);
		 	for(j = 0;j < m;j++)
		 	{
		 		printf("%d ",Max[i][j]);
		 		if(j == m-1)
		 			printf("\t\t");
            }
            	for(j = 0;j < m;j++)
		 	{
		 		printf("%d ",Allocation[i][j]);
		 		if(j == m-1)
		 			printf("\t\t");
            }
            	for(j = 0;j < m;j++)
		 	{
		 		printf("%d ",Need[i][j]);
		 		if(j == m-1)
		 			printf("\t\t");
            }
            if(i == 0)
            {

                for(j = 0;j < m;j++)
                {
                    printf("%d ",Available[j]);
                    if(j == m-1)
                        printf("\t");
                }
            }

            printf("\n");
		 }
        printf("***************************************\n");
        /*A:*/
        printf("***************************************\n");
        printf("1.һ�������������·�����Դ\n");
        printf("0.�˳�\n");
        printf("***************************************\n");
        printf("�����������\n");
        scanf("%d",&menu);
        switch(menu)
        {
        case 1:


            printf("������ڼ����������������Դ\n");
            scanf("%d",&proc);
            printf("������������������Դ����Ŀ\n");
           for(i = 0;i < m;i++)
            {
                scanf("%d",&Request[i]);
            }

            for(i = 0;i < m;i++)
            {

                    if(Request[i] > Need[proc][i])
                    {
                        printf("��Ҫ����Դ���������Ƶ����ֵ\n");
                        goto A;
                    }

            }

            for(i = 0;i < m;i++)
            {

                if(Request[i] > Available[i])
                {
                    printf("�����㹻��Դ\n");
                    goto A;
                }

            }
                //������Դ
                i = proc;
                for(j = 0;j < m;j++)
                {
                    Available[j] -= Request[j];
                    Allocation[i][j] += Request[j];
                    Need[i][j] -= Request[j];
                }
        //����ع�
	    if(safe((int *)Max,(int *)Allocation,(int *)Need,(int *)Available,m,n) == false)
        {
                i = proc;
                for(j = 0;j < m;j++)
                {
                    Available[j] += Request[j];
                    Allocation[i][j] -= Request[j];
                    Need[i][j] += Request[j];
                }
        }
        /*
            for(i = 0;i < n;i++)
            {
                for(j = 0;j < m;j++)
                {
                    if(Need[i][j] != 0)
                    {
                        break;
                    }

                }
                Available[j] += Allocation[i][j];
                Max[i][j] = 0;
                printf("��%d�����̵ĵ������Ѿ�����\n",i);
            }
            */

        int *flag1;
        int b;
        flag1 =  (int*)malloc(n*sizeof(int));
        for(b = 0;b < n; b++){
            *(flag1+b) = true;
        }

        for(i = 0;i < n;i++)
        {
           for(j = 0;j < m;j++)
            {
            	if(Need[i][j] != 0)
                {
                    *(flag1+i) = false;
                    break;
                }

            }

        }
        for(i = 0;i < n;i++){
            if(*(flag1 + i) == true)
            {
                for(j = 0;j < m;j++)
                {
                    Available[j] += Allocation[i][j];

                }
                 printf("��%d�����̵ĵ������Ѿ�����\n",i);
            }
        }
        free(flag1);//???
	break;
        case 2:
            break;
        }
    } while(menu!=0);

    return 0;
}

