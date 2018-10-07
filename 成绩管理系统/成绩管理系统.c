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
        printf("���ļ�stu.dat����\n");
        getch();
        return;                                         
    }     
    
    do{
         i++;
         stu1=(STU *)malloc(sizeof(STU));
         
         if(stu1==NULL)
         {
             printf("�ڴ����ʧ�ܣ���������˳���\n");
             getch();
             return;              
         }
         printf("�������%d��ѧ������Ϣ��\n",i);
         bound('_',30);
         printf("ѧ�ţ�");
         scanf("%d",&stu1->num);
         
         printf("ְ��");
         scanf("%s",&stu1->duty);
         
         printf("������");
         scanf("%s",&stu1->name);
         
         printf("�Ա�");
         scanf("%s",&stu1->sex);
         
         printf("���䣺");
         scanf("%d",&stu1->age);
         
         printf("�Ļ��̶ȣ�");
         scanf("%s",&stu1->edu);
         
         printf("�ɼ���");
         scanf("%d",&stu1->grade);
         
         printf("���ĳɼ���");
         scanf("%s",&stu1->chinese);
         
         printf("��ѧ�ɼ���");
         scanf("%s",&stu1->math);
         
         printf("������ɼ���");
         scanf("%s",&stu1->cs);
         
         printf("Ӣ��ɼ�:");
         scanf("%s",&stu1->English);
         
         printf("�绰��");
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
         printf("\n�Ƿ��������?(y/n)");
         fflush(stdin);
         choice=getch();
         
         if(toupper(choice)!='Y')
         {
             fclose(fp);
             printf("\n������ϣ������������\n");
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


/*�״�ʹ�ã������û���Ϣ��ʼ��*/
void checkfirst()
{
    FILE *fp,*fp1; 
    char pwd[9],pwd1[9],pwd2[9],pwd3[9],ch;
    int i;
    char strt='8';    
    
    if((fp=fopen("config.bat","rb"))==NULL)
    {
        printf("\n��ϵͳ���������Ӧ�ĳ�ʼ��������\n");
        bound('_',50);
        getch();
        
        do{
            printf("\n�������룬�벻Ҫ����8λ��");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n��ȷ��һ�����룺");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n�����������벻һ�£����������룡\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\nϵͳ����ʧ�ܣ��밴������˳���");
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
        printf("\n\nϵͳ��ʼ���ɹ�����������˳��������½��룡\n");
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
    printf("\n����Ҫɾ����ѧ��������");
    scanf("%s",name);
    
    stu1=stu_first;
    stu2=stu1;
    while(stu1)
    {
        if(strcmp(stu1->name,name)==0)
        {
            findok=1;
            system("cls");
            
          printf("ѧ����%s����Ϣ���£�",stu1->name);
            bound('_',40);
            printf("ѧ�ţ�%d\n",stu1->num);
            printf("ְ��%s\n",stu1->duty);
            printf("������%s\n",stu1->name);
            printf("�Ա�%s\n",stu1->sex);
            printf("���䣺%d\n",stu1->age);
            printf("�Ļ��̶ȣ�%s\n",stu1->edu);
            printf("�ɼ���%d\n",stu1->grade);
            printf("���ĳɼ���%s\n",stu1->chinese);
            printf("��ѧ�ɼ���%s\n",stu1->math);
            printf("������ɼ���%s\n",stu1->cs);
            printf("Ӣ��ɼ���%s\n",stu1->English);
            printf("�绰:%s\ns",stu1->mobile);  
            bound('_',40);
            printf("�����Ҫɾ����ѧ����(yes/no)");
            
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
        printf("\nû���ҵ������ǣ�%s����Ϣ��\n",name);
        getch();           
    } 
    return;
}


void displaystu(STU *stu,char *field,char *name)
{
    if(stu)
    {
        printf("\n%s:%s��Ϣ���£�\n",field,name);
        bound('_',30); 
           printf("ѧ�ţ�%d\n",stu->num);
            printf("ְ��%s\n",stu->duty);
            printf("������%s\n",stu->name);
            printf("�Ա�%s\n",stu->sex);
            printf("���䣺%d\n",stu->age);
            printf("�Ļ��̶ȣ�%s\n",stu->edu);
            printf("�ɼ���%d\n",stu->grade);
            printf("���ĳɼ���%s\n",stu->chinese);
            printf("��ѧ�ɼ���%s\n",stu->math);
            printf("������ɼ���%s\n",stu->cs);
            printf("Ӣ��ɼ���%s\n",stu->English);
            printf("�绰:%s\ns",stu->mobile); 
        bound('_',30);      
    }else {
    bound('_',40);
    printf("���Ͽ���û��%sΪ��%s��ѧ����������ȷ�ϣ�",field,name);
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
         printf("\t��ѯѧ����Ϣ\n");
         bound('_',30);
          printf("\t1.��������ѯ\n");
         printf("\t2.��ѧ�Ų�ѯ\n");
         printf("\t3.��������ɼ���ѯ\n");
         printf("\t4.��Ӣ��ɼ���ѯ\n");
         printf("\t0.�������˵�\n");
         bound('_',30);
         printf("\n��ѡ��˵���");
         
         do{
             fflush(stdin);
             choice=getchar();
             system("cls");
             
             switch(choice)
             {
                 case '1':
                      printf("\n����Ҫ��ѯ��������");
                      scanf("%s",str);
                      
                      stu1=findname(str);
                      displaystu(stu1,"����",str);
                      getch();
                      break; 
                      
                 case '2':
                      printf("\n������Ҫ��ѯ��ѧ����ѧ��"); 
                      scanf("%d",&num); 
                      
                      stu1=findnum(num);
                      itoa(num,str,10);
                      displaystu(stu1,"ѧ��",str);
                      getch();
                      break;
                      
                  case '3':
                       printf("\n����Ҫ��ѯѧ���ĵ绰:");
                       scanf("%s",str);
                       
                       stu1=findtelephone(str); 
                       displaystu(stu1,"�绰",str);
                       getch();
                       break;
                       
                  case '4':
                       printf("\n����Ҫ��ѯ��ѧ����English�ţ�");
                       scanf("%s",str);
                       
                       stu1=findEnglish(str);
                       displaystu(stu1,"English����",str);
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
    
    printf("\n���Ͽ��е�ѧ����Ϣ�б�\n");
    bound('_',40);
    stu1=stu_first;
    
    while(stu1) 
    {
        printf("ѧ�ţ�%d\n",stu1->num);
        printf("ְ��%s\n",stu1->duty);
        printf("������%s\n",stu1->name);
        printf("�Ա�%s\n",stu1->sex);
        printf("���䣺%d\n",stu1->age);
        printf("�Ļ��̶ȣ�%s\n",stu1->edu);
        printf("�ɼ���%d\n",stu1->grade);
        printf("�칫�绰��%s\n",stu1->chinese);
        printf("��ѧ�ɼ���%s\n",stu1->math);
        printf("������ɼ���%s\n",stu1->cs);
        printf("English��%s\n",stu1->English);
        printf(" :%s\n",stu1->mobile);  
        bound('_',40);
        stu1=stu1->next;      
    }    
    printf("\n��ʾ��ϣ���������˳���\n");
    getch();
    return;
}


/*����¼����*/
void login()
{
    int i,n=3;
    char pwd[9];
    
    do{
        printf("���������룺");
        for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(pwd,password))
        {
            printf("\n����������������룡\n");
            system("cls");
            n--;                        
        }else break;
    } while(n>0);
    
    if(!n)
    {
        printf("���˳���������������������");
        getch();
        exit(1);      
    }
}


void menu()
{
    char choice;
    
    system("cls");
    
    do{
        printf("\t  -ѧ������ϵͳ\n");
        bound('_',40);
        printf("\t1.����ѧ����Ϣ\n");
        printf("\t2.��ѯѧ����Ϣ\n");
        printf("\t3.��ʾѧ����Ϣ\n");
        printf("\t4.�޸�ѧ����Ϣ\n");
        printf("\t5.ɾ��ѧ����Ϣ\n");
        printf("\t6.ͳ��ѧ����Ϣ\n");
        printf("\t7.����ϵͳ����\n");
        printf("\t0.�˳�ϵͳ\n");
        bound('_',40);
        printf("\n��ѡ������Ҫ�Ĳ�����");
        
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
                       printf("ϵͳ��Ϣ����ѧ����Ϣ���������ѧ����Ϣ��\n");
                       getch();
                       break;          
                   }  
                   
                   findstu();
                   break;
                case '3':
                   if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����ѧ����Ϣ���������ѧ����Ϣ��\n");
                       getch();
                       break;       
                   }
                   
                   liststu();
                   break;
               case '4':
                   if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����ѧ����Ϣ���������ѧ����Ϣ��\n");
                       getch();
                       break;       
                   }
                   
                   modifystu();
                   break;
               case '5':
                    if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����ѧ����Ϣ���������ѧ����Ϣ��\n");
                       getch();
                       break;       
                   }
                   
                   delstu();
                   break;
               case '6':
                    if(gfirst)
                   {
                       printf("ϵͳ��Ϣ����ѧ����Ϣ���������ѧ����Ϣ��\n");
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
    printf("ԭ���ĳɼ���Ϊ��%d",grade);
    printf("�µĳɼ�����");
    scanf("%d",&newgrade);
    
    return(newgrade);
}



int modi_age(int age){
    int newage;
    printf("ԭ��������Ϊ��%d",age);
    printf("�µ����䣺");
    scanf("%d",&newage);
    
    return(newage);
}
char *modi_field(char *field,char *content,int len)
{
     char *str;
     str=malloc(sizeof(char)*len);
     if(str==NULL)
     {
         printf("�ڴ����ʧ�ܣ���������˳���");
         getch();
         return NULL;             
     }
     printf("ԭ��%sΪ��%s\n",field,content);
     printf("�޸�Ϊ�����ݲ�Ҫ����%d���ַ�������",len);
     scanf("%s",str);
     
     return str;
}

void modifystu()
{
     STU *stu1;
     char name[10],*newcontent;
     int choice;
     
     printf("\n��������Ҫ�޸ĵ�ѧ������Ϣ:");
     scanf("%s",&name);
     
     stu1=findname(name);
     displaystu(stu1,"����",name);
     
     if(stu1)
     {
         printf("\n ��������Ҫ�޸ĵ�����ѡ�\n");
         bound('_',40);
         printf("1.�޸�ְ��                2.�޸�����\n");
         printf("3.�޸��Ļ��̶�            4.�޸ĳɼ�\n");
         printf("5.�޸����ĳɼ�          6.�޸���ѧ�ɼ�\n");
         printf("7.�޸ļ�����ɼ�            8.�޸�English���� \n");
         printf("9.�޸ĵ绰                0.����\n  ");
         bound('_',40);
         
         do{
             fflush(stdin);
             choice=getchar();
             switch(choice) 
             {
                 case '1':
                      newcontent=modi_field("ְ��",stu1->duty,10);
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
                      newcontent=modi_field("�Ļ��̶�",stu1->edu,10);
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
                      newcontent=modi_field("���ĳɼ�",stu1->chinese,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->chinese,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                 case '6':
                      newcontent=modi_field("��ѧ�ɼ�",stu1->math,13);
                      if(newcontent!=NULL)
                      {
                          strcpy(stu1->math,newcontent);
                          free(newcontent);                    
                      } 
                      break;
                  case '7':
                      newcontent=modi_field("������ɼ�",stu1->cs,12);
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
                      newcontent=modi_field("�绰",stu1->mobile,30);
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
         printf("\n�޸���ϣ���������˳���\n");
         getch();
     }  
     return;   
}



/*��ȡ����*/ 
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
            printf("�ڴ����ʧ�ܣ�\n");
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
    
    printf("\n����������룺\n");
     for(i=0;i<8 && ((pwd[i]=getch())!=13);i++)
            putch('*');
            
        pwd[i]='\0';
        if(strcmp(password,pwd)!=0)
        {
            printf("\n��������밴������˳���\n");
            getch();
            return;             
        }   
     do{
         printf("\n���������룬�벻Ҫ����8λ��");
            for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
                putch('*');
            printf("\n��ȷ��һ�����룺");
            for(i=0;i<8&&((pwd1[i]=getch())!=13);i++) 
                putch('*');    
                
            pwd[i]='\0';  
            pwd1[i]='\0';
            
            if(strcmp(pwd,pwd1)!=0)
                printf("\n�����������벻һ�£����������룡\n\n");
            else break;
            
        }while(1);
        
        if((fp1=fopen("config.bat","wb"))==NULL)
        {
            printf("\nϵͳ����ʧ�ܣ��밴������˳���");
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
        printf("\n�����޸ĳɹ�����������˳���\n");
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
          printf("���ļ�stu.dat����\n");
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
       if((strcmp(strw,"ma")==0)||(strcmp(stu1->sex,"��")==0)) man++;
       else woman++;
       stu1=stu1->next;          
   }     
   
   printf("\n���������ѧ����ͳ����Ϣ��\n");
   bound('_',40);
   printf("ѧ�������ǣ�%d\n",num);
   printf("ѧ���ĳɼ������ǣ�%d\n",sum);
   printf("��ѧ����Ϊ��%d\n",man);
   printf("Ůѧ����Ϊ��%d\n",woman);
   bound('_',40);
   printf("��������˳���\n");
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

