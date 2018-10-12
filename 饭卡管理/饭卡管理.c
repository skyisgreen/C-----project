#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
struct card
{
	double num;   
	int info;  //表示挂失信息，info=0表示没有挂失，info=1表示已经挂失
	char name[20];
	double money;
}student[100];
void creat();  //创建文件
void buy();   //买饭
void con();   //续钱
void add();   //添加新饭卡
void mov();   //注销旧饭卡
void set();   //设置与解除挂失
void bianli();  //遍历
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
       	printf("       请输入选择编号（0--7）     \n");
    	printf("..................................\n");
    	printf("       1、建立饭卡文件            \n");
    	printf("       2、买饭                    \n");
    	printf("       3、续钱                    \n");
    	printf("       4、添加新饭卡              \n");
    	printf("       5、注销旧饭卡              \n");
    	printf("       6、设置与解除挂失          \n");
      	printf("       7、遍历                    \n");
    	printf("       0、退出系统                \n");
    	printf("..................................\n");
    	scanf("%d",&choice);
    	switch(choice)
		{
	        case 0:printf("感谢使用本软件！已正常退出，按任意键结束\n");break;
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
	printf("当输入的卡号为0时停止输入饭卡信息\n");
    printf("请输入你的卡号，而且卡号不得超过15位数\n");
	scanf("%lf",&num);
	while(num!=0)
	{
		while(num>pow(10,15))
		{
			printf("你输入的卡号超过15位数!\n");
		    printf("请输入你的卡号，而且卡号不得超过15位数\n");
            scanf("%lf",&num);
		}
		while(num<=0)
		{
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的卡号，而且卡号不得超过15位数\n");
	        scanf("%lf",&num);
		}
        student[i].num=num;
		printf("请输入你的姓名\n"); 
		scanf("%s",name);
		strcpy(student[i].name,name);
		printf("请输入你的饭卡钱\n");
		scanf("%lf",&money);
		while(money<0)
		{
			printf("输入的金额必须为正数!\n");
		    printf("请输入你的饭卡钱\n");
		    scanf("%lf",&money);
		}
		student[i].money=money;
		printf("请输入你的挂失信息(0表示没有挂失，1表示已经挂失）:\n");
		scanf("%d",&info);
		student[i].info=info; 
fprintf(fp,"%.0f%s%.0f%d\n",student[i].num,student[i].name,student[i].money,student[i].info);
	    i++;
		do 
		{
		    printf("请输入你的卡号\n");
	        scanf("%lf",&num);
			for(k=0;k<i;k++)
				if(student[k].num==num)
				{
					a=1;
					printf("此号已经被注册了！请重新输入:\n");
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
		printf("请先建立饭卡文件!\n");
		return;
	}
	do
	{
		printf("请输入你的卡号,而且卡号不得超过15位数:");
	    scanf("%lf",&num1); 
        while(num1>pow(10,15))
		{
			printf("你输入的卡号超过15位数!\n");
			printf("请输入你的卡号,而且卡号不得超过15位数:");
	        scanf("%lf",&num1);
		}
        while(num1<0)
		{
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的卡号,而且卡号不得超过15位数:");
	        scanf("%lf",&num1);
		}
	    for(j=0;j<i;j++)
		   if(student[j].num==num1)
		   {
		       flag=j;
			   break;
		   }
        if(flag==-1)  //查明是否有该卡
		{
			count++;
		    printf("找不到该卡！请重新输入你的卡号:\n");
		}
        if(count==5)
		{
			printf("你输入的无效卡号已经达到5次，系统将自动返回主菜单!\n");
			return;
		}
	}while(flag==-1);
	if(student[flag].info==1)
	{
		printf("本卡已冻结。\n");
		return;
	}
	else
	{
		if(student[flag].money<5)
		{
			printf("余额不足，请续钱。\n");
			return;
		}
		else
		{
			printf("请输入你的饭费:");
			scanf("%lf",&mtemp);
		}
        while(mtemp<0)
		{
			printf("输入的金额必须为正数!\n");
		    printf("请输入你的饭费:");
			scanf("%lf",&mtemp);
		}
		if(student[flag].money>mtemp)
		{
			printf("之前:%.2f money.\n",student[flag].money);
			student[flag].money=student[flag].money-mtemp;
			printf("之后:%.2f money.\n",student[flag].money);
            for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
                
		}
		else
		{
			printf("余额不足，请续钱。\n");
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
		printf("请先建立饭卡文件!\n");
		return;
	}
	do
	{
	    printf("请输入你的饭卡号,而且卡号不得超过15位数:");
	    scanf("%lf",&num2);
        while(num2>pow(10,15))
		{
			printf("你输入的卡号超过15位数!\n");
			printf("请输入你的饭卡号,而且卡号不得超过15位数:");
	        scanf("%lf",&num2);
		}
        while(num2<0)
		{
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的饭卡号,而且卡号不得超过15位数:");
	        scanf("%lf",&num2);
		}
	    for(k=0;k<i;k++)
		   if(student[k].num==num2)
		   {
		      flag=k;
			  break;
		   }
        if(flag==-1) //查明是否有该卡
		{
		   count++;
		   printf("找不到该卡!请重新输入你的卡号:\n");
		}
        if(count==5)
		{
			printf("你输入的无效卡号已经达到5次，系统将自动返回主菜单!\n");
			return;
		}
	}while(flag==-1);
    if(student[flag].info==0)
	{
	    printf("请输入你的续钱额:");
	    scanf("%d",&conmoney);
        while(conmoney<0)
		{
			printf("输入的金额必须为正数!\n");
		    printf("请输入你的续钱额:");
	        scanf("%d",&conmoney);
		}
	    printf("之前:%.2f money.\n",student[flag].money);
	    student[flag].money=student[flag].money+conmoney;
	    printf("之后:%.2f money.\n",student[flag].money);
        for(k=0;k<i;k++)
fprintf(fp,"%.0f%s%.0f%d\n",student[k].num,student[k].name,student[k].money,student[k].info);
	}
	else
		printf("此卡已经冻结！\n");
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
		printf("数据库已满!\n");  
		exit(0);	
	}
    if((fp=fopen("card.dat","w+"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
    if(i==0)
	{
		printf("请先建立饭卡文件!\n");
		return;
	}
    do 
	{
		 printf("请输入你的卡号，而且卡号不得超过15位数\n");
	     scanf("%lf",&num);
         while(num>pow(10,15))
		 {
			printf("你输入的卡号超过15位数!\n");
			printf("请输入你的卡号，而且卡号不得超过15位数\n");
	        scanf("%lf",&num);
		 }
         while(num<0)
		 {
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的卡号，而且卡号不得超过15位数\n");
	        scanf("%lf",&num);
		 }
	     for(k=0;k<i;k++)
		    if(student[k].num==num)
			{
				a=1;
				count++;
				printf("此号已经被注册了！请重新输入:\n");
				break;
			}
			else
			    a=0; 
            if(count==5)
			{
			   printf("你输入的无效卡号已经达到5次，系统将自动返回主菜单!\n");
			   return;
			}
	}while(a==1);
	student[i].num=num;
	printf("请输入你的姓名\n");
	scanf("%s",name);
    strcpy(student[i].name,name);
	printf("请输入你的饭卡钱\n");
	scanf("%lf",&money);
    while(money<0)
	{
		printf("输入的金额必须为正数!\n");
		printf("请输入你的饭卡钱\n");
	    scanf("%lf",&money);
	}
	student[i].money=money;
	printf("请输入你的挂失信息(0表示没有挂失，1表示已经挂失）:\n");
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
		printf("请先建立饭卡文件!\n");
		return;
	}
	do
	{ 
		 printf("请输入你的卡号，而且卡号不得超过15位数\n");
	     scanf("%lf",&num3);
         while(num>pow(10,15))
		 {
			printf("你输入的卡号超过15位数!\n");
			printf("请输入你的卡号，而且卡号不得超过15位数\n");
	        scanf("%lf",&num3);
		 }
        while(num3<0)
		{
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的卡号，而且卡号不得超过15位数\n");
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
	    if(flag==-1) //查明是否有该卡
		{
			count++;
		    printf("此卡不存在!请重新输入:\n");
		}
		if(count==5)
		{
			printf("你输入的卡号已经输入超过5次，系统将自动返回主菜单!\n");
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
		printf("请先建立饭卡文件!\n");
		return;
	}
	do
	{
	    printf("请输入你的饭卡号，而且卡号不得超过15位数:\n");
	    scanf("%lf",&num4); 
        while(num4>pow(10,15))
		{
			printf("你输入的卡号超过15位数!\n");
			printf("请输入你的饭卡号，而且卡号不得超过15位数:\n");
	        scanf("%lf",&num4);
		}
        while(num4<0)
		{
			printf("输入的饭卡号不能为负数!\n");
		    printf("请输入你的饭卡号，而且卡号不得超过15位数:\n");
	        scanf("%lf",&num4);
		}
        for(m=0;m<i;m++)
           if(student[m].num==num4)
		   {
		 	  flag=m;
			  break;
		   }
        if(flag==-1)	//查明是否有该卡
		{
			count++;
		    printf("找不到该卡!请重新输入:\n");
		}
        if(count==5)
		{
			printf("你输入的卡号已经输入超过5次，系统将自动返回主菜单!\n");
			return;
		} 
	}while(flag==-1);
	printf("请输入你要修改的挂失信息(info=0表示没有挂失，info=1表示已经挂失):\n");
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
		printf("请先建立饭卡文件!\n");
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

