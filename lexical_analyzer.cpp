#/*******************************************************************************
# * Author	 : jingbo.li | work at r.
# * Email	 : ljb90@live.cn
# * Last modified : 2013-10-19 15:10
# * Filename	 : lexical_analyzer.cpp
# * Description	 : 
# * *****************************************************************************/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include <stdlib.h>

int m=0;
char *blz[8]=
{
    "const","main",
    "if","else",
    "while","int",
    "for","return"
};

char *ysf[10]=
{
    "+","-","*","/",
    "=","<","<=",">",
    ">=","!="
};

char *fgf[6]=
{
    "(",")","{","}",
    ";",","
};


/*char bsf[]={
<标识符>    ::=  <字母>{<字母>|<数字> }
}*/

///*char sz[]={
/*<无符号整数> ::=  <数字>{<数字>}
}*/

/*char sz[] = {
  <数字>      ::=  0 | 1 | 2 | … | 9
}*/

int Find_char(char buf[], int type)
{
    int i;
    switch (type)
    {
    case 1:
        for(i=0; i<8; i++)
        {
            if(strcmp(blz[i],buf) == 0)
                return 1;
        }
    case 2:
    {
        for(i=0; i<10; i++)
        {
            if(strcmp(ysf[i],buf)==0)
                return 1;
        }
        break;
    }
    case 3:
    {
        for(i=0; i<6; i++)
        {
            if(strcmp(fgf[i],buf) ==0)
                return 1;
        }
        break;
    }
    default:
        return 0;
    }
    return 0;
}

void Is_Char(char buf[])
{
    //  printf("\nCHAR:\n");
    int j = 0;
    char t[10];
    int i = 0;
    while (isalnum(buf[m]) != 0)
    {
        //memset(t, 0, sizeof(t));
        t[j]=buf[m];
        j++;
        m++;
    }
    t[j]='\0';

//printf("buf[%d]=%c",m,buf[m]);
//printf("t=%s\n",t);

    while(isspace(buf[m])!=0)//空格向后移动
        m++;

    if(Find_char(t,1))
    {
        printf("(1保留字,%s)\n",t);
    }
    else
        printf("(2标示符,%s)\n",t);
}

void Is_Num(char buf[])
{
    //printf("\nIs_Num:\n");

    int j = 0;
    char t[10];

    while (isdigit(buf[m]) != 0)
    {
        t[j]=buf[m];
        j++;
        m++;
    }
    t[j]='\0';

    while(isspace(buf[m])!=0)//空格向后移动
        m++;

    printf("(3无符号整数,%s)\n",t);
}

void Other(char buf[])
{
    // printf("\nOther:\n");

    int j = 0;
    char t[10];
    while ((isspace(buf[m])==0)&& (isalnum(buf[m])==0))//既不是空也不是字符数
    {
        t[j]=buf[m];
        j++;
        m++;
    }
    t[j]='\0';

    while(isspace(buf[m])!=0)//空格向后移动
        m++;

    if (Find_char(t,2))
        printf("(4运算符,%s)\n",t);
    else if (Find_char(t,3))
        printf("(5分隔符,%s)\n",t);
//    else
//        printf("(系统库暂无此字符,%s)\n",t);
}

int main (char argc, char *argv[])
{
    FILE *fp;
    char buf[1000];

    if ((fp=fopen(argv[1],"r")) == NULL)
        printf("读取失败！\n");
    else
    {
        while ((!feof(fp)))
        {
            m=0;
            fgets(buf, 1000, fp);
            while(buf[m] != '\0')
            {
                if (isalpha(buf[m])!=0)//字符开头
                    Is_Char(buf);
                else
                {
                    if (isdigit(buf[m])!=0)//数字开头
                        Is_Num(buf);
                    else
                        Other(buf);//其他
                }
            }
        }
    }
    return 0;
}
