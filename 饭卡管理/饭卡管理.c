#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct card
{
	double num;   
	int info;  //��ʾ��ʧ��Ϣ��info=0��ʾû�й�ʧ��info=1��ʾ�Ѿ���ʧ
	char name[20];
	double money;
}student[100];
void creat();  //�����ļ�
void buy();   //��
void con();   //��Ǯ
void add();   //����·���
void mov();   //ע���ɷ���
void set();   //����������ʧ
void bianli();  //����
int i=0,info;
double num;
char name[20];
double money;
FILE *fp;
int main(void)
{	
	int choice;
	do{
    	printf("..................................\n");
       	printf("       ������ѡ���ţ�0--7��     \n");
    	printf("..................................\n");
    	printf("       1�����������ļ�            \n");
    	printf("       2����                    \n");
    	printf("       3����Ǯ                    \n");
    	printf("       4������·���              \n");
    	printf("       5��ע���ɷ���              \n");
    	printf("       6������������ʧ          \n");
      	printf("       7������                    \n");
    	printf("       0���˳�ϵͳ                \n");
    	printf("..................................\n");
    	scanf("%d",&choice);
    	switch(choice)
		{
	        case 0:printf("��лʹ�ñ�������������˳��������������\n");break;
	    	case 1:creat();break;
	    	case 2:buy();break;
	    	case 3:con();break;
	    	case 4:add();break;
	    	case 5:mov();break;
	    	case 6:set();break;
			case 7:bianli();break;
	    	default:exit(0);
		}
	}while(choice!=0);
	return 0;
}

void creat()
{
	int a=0,k;
	i=0;
	if((fp=fopen("card.dat","w+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	printf("������Ŀ���Ϊ0ʱֹͣ���뷹����Ϣ\n");
    printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	scanf("%lf",&num);
	while(num!=0)
	{
		while(num>pow(10,15))
		{
			printf("������Ŀ��ų���15λ��!\n");
		    printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
            scanf("%lf",&num);
		}
		while(num<=0)
		{
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	        scanf("%lf",&num);
		}
        student[i].num=num;
		printf("�������������\n"); 
		scanf("%s",name);
		strcpy(student[i].name,name);
		printf("��������ķ���Ǯ\n");
		scanf("%lf",&money);
		while(money<0)
		{
			printf("����Ľ�����Ϊ����!\n");
		    printf("��������ķ���Ǯ\n");
		    scanf("%lf",&money);
		}
		student[i].money=money;
		printf("��������Ĺ�ʧ��Ϣ(0��ʾû�й�ʧ��1��ʾ�Ѿ���ʧ��:\n");
		scanf("%d",&info);
		student[i].info=info; 
fprintf(fp,"%.0f%s%.0f%d\n",student[i].num,student[i].name,student[i].money,student[i].info);
	    i++;
		do 
		{
		    printf("��������Ŀ���\n");
	        scanf("%lf",&num);
			for(k=0;k<i;k++)
				if(student[k].num==num)
				{
					a=1;
					printf("�˺��Ѿ���ע���ˣ�����������:\n");
					break;
				}
				else
					a=0;
				
		}while(a==1); 	
	}
	if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
	
}

void buy()
{
	int j,flag=-1,k,count=0;
	double num1;
	double mtemp;
    if((fp=fopen("card.dat","w+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	if(i==0)
	{
		printf("���Ƚ��������ļ�!\n");
		return;
	}
	do
	{
		printf("��������Ŀ���,���ҿ��Ų��ó���15λ��:");
	    scanf("%lf",&num1); 
        while(num1>pow(10,15))
		{
			printf("������Ŀ��ų���15λ��!\n");
			printf("��������Ŀ���,���ҿ��Ų��ó���15λ��:");
	        scanf("%lf",&num1);
		}
        while(num1<0)
		{
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������Ŀ���,���ҿ��Ų��ó���15λ��:");
	        scanf("%lf",&num1);
		}
	    for(j=0;j<i;j++)
		   if(student[j].num==num1)
		   {
		       flag=j;
			   break;
		   }
        if(flag==-1)  //�����Ƿ��иÿ�
		{
			count++;
		    printf("�Ҳ����ÿ���������������Ŀ���:\n");
		}
        if(count==5)
		{
			printf("���������Ч�����Ѿ��ﵽ5�Σ�ϵͳ���Զ��������˵�!\n");
			return;
		}
	}while(flag==-1);
	if(student[flag].info==1)
	{
		printf("�����Ѷ��ᡣ\n");
		return;
	}
	else
	{
		if(student[flag].money<5)
		{
			printf("���㣬����Ǯ��\n");
			return;
		}
		else
		{
			printf("��������ķ���:");
			scanf("%lf",&mtemp);
		}
        while(mtemp<0)
		{
			printf("����Ľ�����Ϊ����!\n");
		    printf("��������ķ���:");
			scanf("%lf",&mtemp);
		}
		if(student[flag].money>mtemp)
		{
			printf("֮ǰ:%.2f money.\n",student[flag].money);
			student[flag].money=student[flag].money-mtemp;
			printf("֮��:%.2f money.\n",student[flag].money);
            for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
                
		}
		else
		{
			printf("���㣬����Ǯ��\n");
			return;
		}
	}
	if(fclose(fp))
	{
		 printf("Can not close the file!\n");
		 exit(0);
	} 
}

void con()
{
	int k,conmoney,flag=-1,count=0;
	double num2;
    if((fp=fopen("card.dat","w+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
    if(i==0)
	{
		printf("���Ƚ��������ļ�!\n");
		return;
	}
	do
	{
	    printf("��������ķ�����,���ҿ��Ų��ó���15λ��:");
	    scanf("%lf",&num2);
        while(num2>pow(10,15))
		{
			printf("������Ŀ��ų���15λ��!\n");
			printf("��������ķ�����,���ҿ��Ų��ó���15λ��:");
	        scanf("%lf",&num2);
		}
        while(num2<0)
		{
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������ķ�����,���ҿ��Ų��ó���15λ��:");
	        scanf("%lf",&num2);
		}
	    for(k=0;k<i;k++)
		   if(student[k].num==num2)
		   {
		      flag=k;
			  break;
		   }
        if(flag==-1) //�����Ƿ��иÿ�
		{
		   count++;
		   printf("�Ҳ����ÿ�!������������Ŀ���:\n");
		}
        if(count==5)
		{
			printf("���������Ч�����Ѿ��ﵽ5�Σ�ϵͳ���Զ��������˵�!\n");
			return;
		}
	}while(flag==-1);
    if(student[flag].info==0)
	{
	    printf("�����������Ǯ��:");
	    scanf("%d",&conmoney);
        while(conmoney<0)
		{
			printf("����Ľ�����Ϊ����!\n");
		    printf("�����������Ǯ��:");
	        scanf("%d",&conmoney);
		}
	    printf("֮ǰ:%.2f money.\n",student[flag].money);
	    student[flag].money=student[flag].money+conmoney;
	    printf("֮��:%.2f money.\n",student[flag].money);
        for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
	}
	else
		printf("�˿��Ѿ����ᣡ\n");
    if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	} 
}

void add()
{
	int a=0,k,count=0;
	if(i>=100)
	{
		printf("���ݿ�����!\n");  
		exit(0);	
	}
    if((fp=fopen("card.dat","w+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
    if(i==0)
	{
		printf("���Ƚ��������ļ�!\n");
		return;
	}
    do 
	{
		 printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	     scanf("%lf",&num);
         while(num>pow(10,15))
		 {
			printf("������Ŀ��ų���15λ��!\n");
			printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	        scanf("%lf",&num);
		 }
         while(num<0)
		 {
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	        scanf("%lf",&num);
		 }
	     for(k=0;k<i;k++)
		    if(student[k].num==num)
			{
				a=1;
				count++;
				printf("�˺��Ѿ���ע���ˣ�����������:\n");
				break;
			}
			else
			    a=0; 
            if(count==5)
			{
			   printf("���������Ч�����Ѿ��ﵽ5�Σ�ϵͳ���Զ��������˵�!\n");
			   return;
			}
	}while(a==1);
	student[i].num=num;
	printf("�������������\n");
	scanf("%s",name);
    strcpy(student[i].name,name);
	printf("��������ķ���Ǯ\n");
	scanf("%lf",&money);
    while(money<0)
	{
		printf("����Ľ�����Ϊ����!\n");
		printf("��������ķ���Ǯ\n");
	    scanf("%lf",&money);
	}
	student[i].money=money;
	printf("��������Ĺ�ʧ��Ϣ(0��ʾû�й�ʧ��1��ʾ�Ѿ���ʧ��:\n");
	scanf("%d",&info);
	student[i].info=info;
	for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
	i++;
    if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
}

void mov()
{
	int j,k,flag=-1,count=0;
	double num3;
	if((fp=fopen("card.dat","w"))==NULL)
	{
	 	 printf("File open error!\n");
		 exit(0);
	}
    if(i==0)
    {
		printf("���Ƚ��������ļ�!\n");
		return;
	}
	do
	{ 
		 printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	     scanf("%lf",&num3);
         while(num>pow(10,15))
		 {
			printf("������Ŀ��ų���15λ��!\n");
			printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	        scanf("%lf",&num3);
		 }
        while(num3<0)
		{
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������Ŀ��ţ����ҿ��Ų��ó���15λ��\n");
	        scanf("%lf",&num3);
		}
	    for(j=0;j<i;j++)
		{
		    if(student[j].num==num3)
			{
			   i--;
			   flag=j;
			   break;
			}
		}
	    if(flag==-1) //�����Ƿ��иÿ�
		{
			count++;
		    printf("�˿�������!����������:\n");
		}
		if(count==5)
		{
			printf("������Ŀ����Ѿ����볬��5�Σ�ϵͳ���Զ��������˵�!\n");
			return;
		}
	}while(flag==-1);
	for(k=flag;k<i;k++)
		student[k]=student[k+1];
	for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
    if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}
}

void set()
{
	int info1,m,k,flag=-1,count=0;
	double num4;
    if((fp=fopen("card.dat","w+"))==NULL)
	{
	 	 printf("File open error!\n");
		 exit(0);
	}
    if(i==0)
	{
		printf("���Ƚ��������ļ�!\n");
		return;
	}
	do
	{
	    printf("��������ķ����ţ����ҿ��Ų��ó���15λ��:\n");
	    scanf("%lf",&num4); 
        while(num4>pow(10,15))
		{
			printf("������Ŀ��ų���15λ��!\n");
			printf("��������ķ����ţ����ҿ��Ų��ó���15λ��:\n");
	        scanf("%lf",&num4);
		}
        while(num4<0)
		{
			printf("����ķ����Ų���Ϊ����!\n");
		    printf("��������ķ����ţ����ҿ��Ų��ó���15λ��:\n");
	        scanf("%lf",&num4);
		}
        for(m=0;m<i;m++)
           if(student[m].num==num4)
		   {
		 	  flag=m;
			  break;
		   }
        if(flag==-1)	//�����Ƿ��иÿ�
		{
			count++;
		    printf("�Ҳ����ÿ�!����������:\n");
		}
        if(count==5)
		{
			printf("������Ŀ����Ѿ����볬��5�Σ�ϵͳ���Զ��������˵�!\n");
			return;
		} 
	}while(flag==-1);
	printf("��������Ҫ�޸ĵĹ�ʧ��Ϣ(info=0��ʾû�й�ʧ��info=1��ʾ�Ѿ���ʧ):\n");
	scanf("%d",&info1);
    student[flag].info=info1;
    for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
    if(fclose(fp))
	{
		printf("Can not close the file!\n");
		exit(0);
	}	
} 

void bianli()
{
	int l=0;
    if((fp=fopen("card.dat","r"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
     if(i==0)
	{
		printf("���Ƚ��������ļ�!\n");
		return;
	}
	for(l=0;l<i;l++)
	{
fscanf(fp,"%lf%s%lf%d",&student[l].num,student[l].name,&student[l].money,&student[l].info);
		if(student[l].num==0)
			continue;
		printf("%.0f %s %.0f %d\n",student[l].num,student[l].name,student[l].money,student[l].info);
	}
}

