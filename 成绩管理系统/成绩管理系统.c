#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct stu
{
    int num;
    char duty[10];
    char name[10];
    char sex[3];
    unsigned char age;
    char edu[10];
    int grade;
    char chinese[13];
    char math[13];
    char cs[13];
    char English[11];
    char mobile[31];
    struct stu *next;    
}STU;
    
    char password[9];
    STU *stu_first,*stu_end;
    char gsave,gfirst;
    
    void addstu(void);
    void findstu(void);
    void liststu(void);
    void modifystu(void);
    void summarystu(void);
    void delstu(void);
    void resetpwd(void);
    void readdata(void);
    void savedata(void);
    int modi_age(int s);
    int modi_grade(int s);
    char *modi_field(char *field,char *s,int n);
    STU *findname(char *name);
    STU *findnum(int num);
    STU *findtelephone(char *name);
    STU *findEnglish(char *name);
    void displaystu(STU *stu,char *field,char *name);
    void checkfirst(void);
    void bound(char ch,int n);
    void login();
    void menu();



void addstu()
{
    FILE *fp;
    STU *stu1;
    int i=0;
    char choice='y';
    
    if((fp=fopen("stu.dat","ab"))==NULL)
    {
        printf("打开文件stu.dat出错！\n");
        getch();
        return;                                         
    }     
    
    do{
         i++;
         stu1=(STU *)malloc(sizeof(STU));
         
         if(stu1==NULL)
         {
             printf("内存分配失败，按任意键退出！\n");
             getch();
             return;              
         }
         printf("请输入第%d个学生的信息，\n",i);
         bound('_',30);
         printf("学号：");
         scanf("%d",&stu1->num);
         
         printf("职务：");
         scanf("%s",&stu1->duty);
         
         printf("姓名：");
         scanf("%s",&stu1->name);
         
         printf("性别：");
         scanf("%s",&stu1->sex);
         
         printf("年龄：");
         scanf("%d",&stu1->age);
         
         printf("文化程度：");
         scanf("%s",&stu1->edu);
         
         printf("成绩：");
         scanf("%d",&stu1->grade);
         
         printf("语文成绩：");
         scanf("%s",&stu1->chinese);
         
         printf("数学成绩：");
         scanf("%s",&stu1->math);
         
         printf("计算机成绩：");
         scanf("%s",&stu1->cs);
         
         printf("英语成绩:");
         scanf("%s",&stu1->English);
         
         printf("电话：");
         scanf("%s",&stu1->mobile);
         
         stu1->next=NULL;
         if(stu_first==NULL)
         {
             stu_first=stu1;
             stu_end=stu1;                   
         }else {
             stu_end->next=stu1;
             stu_end=stu1;      
         }
         
         fwrite(stu_end,sizeof(STU),1,fp);
         
         gfirst=0;
         printf("\n");
         bound('_',30);
         printf("\n是否继续输入?(y/n)");
         fflush(stdin);
         choice=getch();
         
         if(toupper(choice)!='Y')
         {
             fclose(fp);
             printf("\n输入完毕，按任意键返回\n");
             getch();
             return;                        
         }
         
         system("cls");      
    }while(1);
}



void bound(char ch,int n)
{
   while(n--)
       putch(ch);
       
   printf("\n");
   return;     
}


/*首次使用，进行用户信息初始化*/
void checkfirst()
{
    FILE *fp,*fp1; 
    char pwd[9],pwd1[9],pwd2[9],pwd3[9],ch;
    int i;
    char strt='8';    
    
    if((fp=fopen("config.bat","rb"))==NULL)
    {
        printf("\n新系统，请进行相应的初始化操作！\n");
        bound('_',50);
        getch();
        
        do{
            printf("\n设置密码，请不要超过8位：");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n再确认一次密码：");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n两次密码输入不一致，请重新输入！\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\n系统创建失败，请按任意键退出！");
            getch();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
                 
            pwd2[i]=(pwd[i]^ strt);        
            putw(pwd2[i],fp1);
            i++;             
        }
        
        fclose(fp1);
        printf("\n\n系统初始化成功，按任意键退出后，再重新进入！\n");
        getch();
        exit(1);
        
    }else{
        i=0;
        while(!feof(fp)&&i<8)
            pwd[i++]=(getw(fp)^strt);
            
            
        pwd[i]='\0';
        
        if(i>=8) i--;
        while(pwd[i]!=-1&&i>=0)
            i--;
        
        pwd[i]='\0';
        strcpy(password,pwd); 
    } 
}


void delstu()
{
    int findok=0;
    STU *stu1,*stu2;
    char name[10],choice;
    
    system("cls");
    printf("\n输入要删除的学生姓名：");
    scanf("%s",name);
    
    stu1=stu_first;
    stu2=stu1;
    while(stu1)
    {
        if(strcmp(stu1->name,name)==0)
        {
            findok=1;
            system("cls");
            
          printf("学生：%s的信息如下：",stu1->name);
            bound('_',40);
            printf("学号：%d\n",stu1->num);
            printf("职务：%s\n",stu1->duty);
            printf("姓名：%s\n",stu1->name);
            printf("性别：%s\n",stu1->sex);
            printf("年龄：%d\n",stu1->age);
            printf("文化程度：%s\n",stu1->edu);
            printf("成绩：%d\n",stu1->grade);
            printf("语文成绩：%s\n",stu1->chinese);
            printf("数学成绩：%s\n",stu1->math);
            printf("计算机成绩：%s\n",stu1->cs);
            printf("英语成绩：%s\n",stu1->English);
            printf("电话:%s\ns",stu1->mobile);  
            bound('_',40);
            printf("您真的要删除该学生吗？(yes/no)");
            
            fflush(stdin);
            choice=getchar();
            
            if(choice!='y' && choice!='Y') return;
            if(stu1==stu_first) stu_first=stu1->next;
            else stu2->next=stu1->next;
            
            free(stu1);
            gsave=1;
            savedata();
            return;                           
        }  else{        
            stu2=stu1;
            stu1=stu1->next;
        }
    }    
    if(!findok)
    {
        bound('_',40);
        printf("\n没有找到姓名是：%s的信息！\n",name);
        getch();           
    } 
    return;
}


void displaystu(STU *stu,char *field,char *name)
{
    if(stu)
    {
        printf("\n%s:%s信息如下：\n",field,name);
        bound('_',30); 
           printf("学号：%d\n",stu->num);
            printf("职务：%s\n",stu->duty);
            printf("姓名：%s\n",stu->name);
            printf("性别：%s\n",stu->sex);
            printf("年龄：%d\n",stu->age);
            printf("文化程度：%s\n",stu->edu);
            printf("成绩：%d\n",stu->grade);
            printf("语文成绩：%s\n",stu->chinese);
            printf("数学成绩：%s\n",stu->math);
            printf("计算机成绩：%s\n",stu->cs);
            printf("英语成绩：%s\n",stu->English);
            printf("电话:%s\ns",stu->mobile); 
        bound('_',30);      
    }else {
    bound('_',40);
    printf("资料库中没有%s为：%s的学生！请重新确认！",field,name);
    }
    return;
}


STU *findname(char *name)
{
    STU *stu1;
    stu1=stu_first;
    
    while(stu1)
    {
        if(strcmp(name,stu1->name)==0)  return stu1;
        stu1=stu1->next;          
    }    
    return NULL;
}


STU *findnum(int num)
{
   STU *stu1;
   
   stu1=stu_first;
   while(stu1)
   {
       if(num==stu1->num)  return stu1;
       stu1=stu1->next;           
   }  
   return NULL;  
}

STU *findtelephone(char *name)
{
     STU *stu1;
     
     stu1=stu_first;
     while(stu1)
     {
         if((strcmp(name,stu1->chinese)==0)||
         (strcmp(name,stu1->math)==0)||
         (strcmp(name,stu1->cs)==0))
         return stu1;
         stu1=stu1->next;
                 
     }  
      return NULL;       
}


STU *findEnglish(char *name)
{
    STU *stu1;
    
    stu1=stu_first;
    while(stu1)
    {
        if(strcmp(name,stu1->English)==0)  return stu1;
        stu1=stu1->next;           
    }  
    return NULL;  
}


void findstu()
{
     int choice,ret=0,num;
     char str[13];
     STU *stu1;
     
     system("cls");
     
     do{
         printf("\t查询学生信息\n");
         bound('_',30);
          printf("\t1.按姓名查询\n");
         printf("\t2.按学号查询\n");
         printf("\t3.按计算机成绩查询\n");
         printf("\t4.按英语成绩查询\n");
         printf("\t0.返回主菜单\n");
         bound('_',30);
         printf("\n请选择菜单：");
         
         do{
             fflush(stdin);
             choice=getchar();
             system("cls");
             
             switch(choice)
             {
                 case '1':
                      printf("\n输入要查询的姓名：");
                      scanf("%s",str);
                      
                      stu1=findname(str);
                      displaystu(stu1,"姓名",str);
                      getch();
                      break; 
                      
                 case '2':
                      printf("\n请输入要查询的学生的学号"); 
                      scanf("%d",&num); 
                      
                      stu1=findnum(num);
                      itoa(num,str,10);
                      displaystu(stu1,"学号",str);
                      getch();
                      break;
                      
                  case '3':
                       printf("\n输入要查询学生的电话:");
                       scanf("%s",str);
                       
                       stu1=findtelephone(str); 
                       displaystu(stu1,"电话",str);
                       getch();
                       break;
                       
                  case '4':
                       printf("\n输入要查询的学生的English号：");
                       scanf("%s",str);
                       
                       stu1=findEnglish(str);
                       displaystu(stu1,"English号码",str);
                       getch();
                       break;
                       
                   case '0':
                        ret=1;
                        break;          
             }                         
         }while(choice<'0'||choice>'4');
         
         system("cls");
         if(ret) break;
     }while(1);         
}


void liststu()
{
    STU *stu1;
    
    printf("\n资料库中的学生信息列表\n");
    bound('_',40);
    stu1=stu_first;
    
    while(stu1) 
    {
        printf("学号：%d\n",stu1->num);
        printf("职务：%s\n",stu1->duty);
        printf("姓名：%s\n",stu1->name);
        printf("性别：%s\n",stu1->sex);
        printf("年龄：%d\n",stu1->age);
        printf("文化程度：%s\n",stu1->edu);
        printf("成绩：%d\n",stu1->grade);
        printf("办公电话：%s\n",stu1->chinese);
        printf("数学成绩：%s\n",stu1->math);
        printf("计算机成绩：%s\n",stu1->cs);
        printf("English：%s\n",stu1->English);
        printf(" :%s\n",stu1->mobile);  
        bound('_',40);
        stu1=stu1->next;      
    }    
    printf("\n显示完毕，按任意键退出！\n");
    getch();
    return;
}


/*检测登录密码*/
void login()
{
    int i,n=3;
    char pwd[9];
    
    do{
        printf("请输入密码：");
        for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(pwd,password))
        {
            printf("\n密码错误，请重新输入！\n");
            system("cls");
            n--;                        
        }else break;
    } while(n>0);
    
    if(!n)
    {
        printf("请退出，你的三次输入密码错误！");
        getch();
        exit(1);      
    }
}


void menu()
{
    char choice;
    
    system("cls");
    
    do{
        printf("\t  -学生管理系统\n");
        bound('_',40);
        printf("\t1.输入学生信息\n");
        printf("\t2.查询学生信息\n");
        printf("\t3.显示学生信息\n");
        printf("\t4.修改学生信息\n");
        printf("\t5.删除学生信息\n");
        printf("\t6.统计学生信息\n");
        printf("\t7.重置系统密码\n");
        printf("\t0.退出系统\n");
        bound('_',40);
        printf("\n请选择您需要的操作！");
        
        do{
            fflush(stdin);
            choice=getchar();
            system("cls");
            
            switch(choice)
            {
                case '1':
                   addstu();
                   break;
                case '2':
                   if(gfirst)
                   {
                       printf("系统信息中无学生信息，请先添加学生信息！\n");
                       getch();
                       break;          
                   }  
                   
                   findstu();
                   break;
                case '3':
                   if(gfirst)
                   {
                       printf("系统信息中无学生信息，请先添加学生信息！\n");
                       getch();
                       break;       
                   }
                   
                   liststu();
                   break;
               case '4':
                   if(gfirst)
                   {
                       printf("系统信息中无学生信息，请先添加学生信息！\n");
                       getch();
                       break;       
                   }
                   
                   modifystu();
                   break;
               case '5':
                    if(gfirst)
                   {
                       printf("系统信息中无学生信息，请先添加学生信息！\n");
                       getch();
                       break;       
                   }
                   
                   delstu();
                   break;
               case '6':
                    if(gfirst)
                   {
                       printf("系统信息中无学生信息，请先添加学生信息！\n");
                       getch();
                       break;       
                   }
                   
                   summarystu();
                   break; 
               case '7':
                   resetpwd();
                   break;
               case '0':
                   savedata();
                   exit(0);        
            }                             
        } while(choice<'0'||choice>'7');  
        
        
         system("cls");        
    }while(1);    
}


int modi_grade(int grade){
    int newgrade;
    printf("原来的成绩数为：%d",grade);
    printf("新的成绩数：");
    scanf("%d",&newgrade);
    
    return(newgrade);
}



int modi_age(int age){
    int newage;
    printf("原来的年龄为：%d",age);
    printf("新的年龄：");
    scanf("%d",&newage);
    
    return(newage);
}
char *modi_field(char *field,char *content,int len)
{
     char *str;
     str=malloc(sizeof(char)*len);
     if(str==NULL)
     {
         printf("内存分配失败，按任意键退出！");
         getch();
         return NULL;             
     }
     printf("原来%s为：%s\n",field,content);
     printf("修改为（内容不要超过%d个字符！）：",len);
     scanf("%s",str);
     
     return str;
}

void modifystu()
{
     STU *stu1;
     char name[10],*newcontent;
     int choice;
     
     printf("\n请输入您要修改的学生的信息:");
     scanf("%s",&name);
     
     stu1=findname(name);
     displaystu(stu1,"姓名",name);
     
     if(stu1)
     {
         printf("\n 请输入你要修改的内容选项！\n");
         bound('_',40);
         printf("1.修改职务                2.修改年龄\n");
         printf("3.修改文化程度            4.修改成绩\n");
         printf("5.修改语文成绩          6.修改数学成绩\n");
         printf("7.修改计算机成绩            8.修改English号码 \n");
         printf("9.修改电话                0.返回\n  ");
         bound('_',40);
         
         do{
             fflush(stdin);
             choice=getchar();
             switch(choice) 
             {
                 case '1':
                      newcontent=modi_field("职务",stu1->duty,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->duty,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '2':
                      stu1->age=modi_age(stu1->age);
                      break;
                  case '3':
                      newcontent=modi_field("文化程度",stu1->edu,10);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->edu,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '4':
                      stu1->grade=modi_grade(stu1->grade);
                      break;
                 case '5':
                      newcontent=modi_field("语文成绩",stu1->chinese,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->chinese,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '6':
                      newcontent=modi_field("数学成绩",stu1->math,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->math,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '7':
                      newcontent=modi_field("计算机成绩",stu1->cs,12);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->cs,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '8':
                      newcontent=modi_field("English",stu1->English,10);
                      if(newcontent==NULL)
                      {
                          strcpy(stu1->English,newcontent);
                          free(newcontent);                    
                      } 
                      break;  
                  case '9':
                      newcontent=modi_field("电话",stu1->mobile,30);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->mobile,newcontent);
                          free(newcontent);                    
                      } 
                      break;     
                  case '0':
                      return;             
             }             
         }while(choice<'0' || choice>'9');
         
         gsave=1;
         savedata();
         printf("\n修改完毕，按任意键退出！\n");
         getch();
     }  
     return;   
}



/*读取数据*/ 
void readdata(void)
{
    FILE *fp;
    STU *stu1;
    
    if((fp=fopen("stu.dat","rb"))==NULL)
    {
        gfirst=1;
        return;                                        
    }     
    
    while(!feof(fp))
    {
        stu1=(STU *)malloc(sizeof(STU));
        if(stu1==NULL)
        {
            printf("内存分配失败！\n");
            getch();
            return;              
        }          
        
        fread(stu1,sizeof(STU),1,fp);
        if(feof(fp))  break;
        
        if(stu_first==NULL)
        {
           stu_first=stu1;
           stu_end=stu1;                   
        }else{
            stu_end->next=stu1;
            stu_end=stu1;   
        }
        stu_end->next=NULL;
    }
    gfirst=0;
    fclose(fp);
}


void resetpwd()
{
    char pwd[9],pwd1[9],ch;
    int i;
    FILE *fp1;
    
    system("cls");
    
    printf("\n请输入旧密码：\n");
     for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(password,pwd)!=0)
        {
            printf("\n密码错误，请按任意键退出！\n");
            getch();
            return;             
        }   
     do{
         printf("\n设置新密码，请不要超过8位：");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n再确认一次密码：");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n两次密码输入不一致，请重新输入！\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\n系统创建失败，请按任意键退出！");
            getch();
            exit(1);                                        
        }
        
        i=0;
        while(pwd[i])
        {
            putw(pwd[i],fp1);
            i++;             
        }
        
        fclose(fp1);
        printf("\n密码修改成功，按任意键退出！\n");
        getch();
        return;       
}


void savedata()
{
      FILE *fp;
      STU *stu1;
      
      if(gsave==0) return;
      
      if((fp=fopen("stu.dat","wb"))==NULL)
      {
          printf("打开文件stu.dat出错！\n");
          getch();
          return;                                         
      }   
      
      stu1=stu_first;
      while(stu1)
      {
          fwrite(stu1,sizeof(STU),1,fp);
          stu1=stu1->next;          
      }
      
      gsave=0;
      fclose(fp);
}


void summarystu()
{
   STU *stu1;
   int sum=0,num=0,man=0,woman=0;
   
   stu1=stu_first;
   while(stu1)
   {
       num++;
       sum+=stu1->grade;
       char strw[2];
       strncpy(strw,stu1->sex,2);
       if((strcmp(strw,"ma")==0)||(strcmp(stu1->sex,"男")==0)) man++;
       else woman++;
       stu1=stu1->next;          
   }     
   
   printf("\n下面是相关学生的统计信息！\n");
   bound('_',40);
   printf("学生总数是：%d\n",num);
   printf("学生的成绩总数是：%d\n",sum);
   printf("男学生数为：%d\n",man);
   printf("女学生数为：%d\n",woman);
   bound('_',40);
   printf("按任意键退出！\n");
   getch();
   return;
}


int main(void)
{
  stu_first=stu_end=NULL;
  gsave=gfirst=0;
  
  checkfirst();
  login();
  readdata();
  menu();
  system("PAUSE");	
  return 0;
}

