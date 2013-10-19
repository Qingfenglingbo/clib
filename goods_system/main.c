#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char     goodsNo[10];//商品编号
    char    goodsName[20];//商品名
    char    brand[20];//品牌
    char    model[20];//型号
    float    price;//价格
    char     day[20];//生产日期
    int    total;//数量
    struct node * next;
} Goods;

int  t=0;//商品总数

void menu ()  //主菜单
{
    printf("\t\t\t商品库存管理系统v1.0\n");
    printf("********************************************************************************\n");
    printf("请按数字(1-9)选择:\n");
    printf("1.录入商品信息.\n");
    printf("2.查询商品信息.\n");
    printf("3.取出货物.\n");
    printf("4.保存商品信息.\n");
    printf("5.按价格排序.\n");
    printf("6.修改商品信息.\n");
    printf("7.从文件导入商品信息.\n");
    printf("8.帮助.\n");
    printf("9.退出系统!\n");
    printf("********************************************************************************\n");
}


int enter(Goods *head) //录入获取信息
{
    Goods *p=head,*temp;
    // Goods *q=head->next;
    char     goodsNo[20];//商品编号
    char    goodsName[20];//商品名
    char    brand[20];//品牌
    char    model[20];//型号
    float    price;//价格
    char     day[20];//生产日期
    int    total;//数量
    char k;
    while(1)
    {
        Goods *q=head->next;
        fflush(stdin);
        printf("**********************************录入商品**************************************\n");
        printf("第%d个商品：\n",t+1);
        printf("货物号：\n");
        scanf("%s",goodsNo);
        fflush(stdin);
        printf("商品名：\n");
        scanf("%s",goodsName);
        fflush(stdin);
        printf("品牌：\n");
        scanf("%s",brand);
        fflush(stdin);
        printf("型号：\n");
        scanf("%s",model);
        fflush(stdin);
        printf("价格：\n");
        scanf("%f",&price);
        fflush(stdin);
        printf("生产日期：\n");
        scanf("%s",day);
        fflush(stdin);
        printf("录入总数：\n");
        scanf("%d",&total);
        printf("\n");

        while(NULL!=q)
        {
            if(!strcmp(q->goodsNo,goodsNo) && NULL!=q)//比较货号是否重复，重复数量增加，其他属性不变
            {
                q->total = q->total + total;
                printf("货号为：%s商品已经存在，库存由原来的%d个增加到%d个。\n",q->goodsNo,q->total-total,q->total);
                printf("其他属性不变，欲改变其他属性，请到主界面修改处修改！\n");
                system("pause");
                return 1;
            }
            q=q->next;
        }

        temp=(Goods*)malloc(sizeof(Goods));
        if(temp)//货号不重复，录入信息
        {
            strcpy(temp->goodsNo,goodsNo);
            strcpy(temp->goodsName,goodsName);
            strcpy(temp->brand,brand);
            strcpy(temp->model,model);
            temp->price=price;
            strcpy(temp->day,day);
            temp->total=total;
            temp->next = p->next;
            p->next = temp;
            t++;
        }
        else
        {
            return 0;
        }
        fflush(stdin);
        printf("***********************输入r退回主菜单,按任意键继续录入*************************\n");
        if((k=getchar())=='r')//r退出录入
        {
            system ("cls");
            return 0;
        }
    }
    return 0;
}

void menu2() //查询货物菜单
{
    printf("*******************************查询货物信息*************************************\n");
    printf("请按1~3选择：\n");
    printf("1.显示所有货物信息\n");
    printf("2.搜索货号查询\n");
    printf("3.搜索货物名查询\n");
    printf("4.退回主菜单\n");
    printf("*******************************查询货物信息*************************************\n");
}

int print(Goods * head)//输出所有货物的信息
{
    int i=1;
    Goods *temp=head->next;
    if(temp==NULL)//没有库存，提示
    {
        printf("\n仓库中没有货物。请先录入货物信息:\n");
        enter(head);
    }
    else
    {
        while(temp!=NULL)//输出所有信息
        {
            printf("*******************************第%d个货物信息************************************\n",i++);
            printf("货物号：%s\n",temp->goodsNo);
            printf("商品名：%s\n",temp->goodsName);
            printf("品牌：%s\n",temp->brand);
            printf("型号：%s\n",temp->model);
            printf("价格：%4.3f\n",temp->price);
            printf("生产日期：%s\n",temp->day);
            printf("录入总数：%d\n",temp->total);
            temp=temp->next;
        }
        if(NULL == temp)
            printf("以上是所有货物的信息！！！！ \n");
        system("pause");
    }
    return 0;
}

int scanno(Goods *head) //以货号查询
{
    Goods *temp=head->next;
    char number[10];
    if(temp==NULL)//没有货物信息，提示
    {
        printf("\n仓库中没有货物。请先录入货物信息:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("请输入货物号：");
        scanf("%s",number);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsNo,number) && NULL!=temp)//有相应货号，输出相应信息
            {
                printf("货物号：%s\n",temp->goodsNo);
                printf("商品名：%s\n",temp->goodsName);
                printf("品牌：%s\n",temp->brand);
                printf("型号：%s\n",temp->model);
                printf("价格：%4.3f\n",temp->price);
                printf("生产日期：%s\n",temp->day);
                printf("录入总数：%d\n",temp->total);
                system("pause");
                return 0;
            }
        }
        if(NULL==temp)//没有相应的货号，提示
        {
            printf("没有相应的货物信息，请录入后查询！！！！ \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

int scanname(Goods *head) //以货物名查询
{
    Goods *temp=head->next;
    char name[5];
    if(temp==NULL)
    {
        printf("\n仓库中没有货物。请先录入货物信息:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("请输入货物名称：");
        scanf("%s",name);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsName,name) && NULL!=temp)//货物名称相同，则输出
            {
                printf("货物号：%s\n",temp->goodsNo);
                printf("商品名：%s\n",temp->goodsName);
                printf("品牌：%s\n",temp->brand);
                printf("型号：%s\n",temp->model);
                printf("价格：%4.3f\n",temp->price);
                printf("生产日期：%s\n",temp->day);
                printf("录入总数：%d\n",temp->total);
                system("pause");
                return 0;
            }
        }
        if(NULL==temp)//没有匹配货物名称，提示
        {
            printf("没有相应的货物信息，请录入后查询！！！！ \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

int scan(Goods *head) //查看选择
{
    while(1)
    {
        char b;
        menu2();
        fflush(stdin);
        scanf("%c",&b);
        switch(b)
        {
        case '1':
            system("cls");
            print(head);//输出所有货物信息
            break;
        case '2':
            system("cls");
            scanno(head);//按货号查询
            break;
        case '3':
            system("cls");
            scanname(head);//按货名查询
            break;
        case '4':
            system("cls");//返回主菜单
            return 0;
        default:
            system ("cls");
            printf("╭∩╮(︶︿︶）╭∩╮系统鄙视你！╭∩╮(︶︿︶）╭∩╮系统鄙视你！o(╯□╰)o\n");
            printf("请重新选择:\n");
            system("pause");
        }
    }
}

int delete_xh(Goods *head) //提取货物信息
{
    char goodsNo[10];
    int no;
    Goods *temp=head,*p;
    printf("*********************************输出货物**************************************\n");
    printf("请输入出去的货物的货号:\n");
    fflush(stdin);
    scanf("%s",goodsNo);
    fflush(stdin);
    printf("请输入出去的货物的数量:\n");
    scanf("%d",&no);

    while(temp->next!=NULL)
    {
        if(!strcmp(temp->next->goodsNo,goodsNo))//按货号查找相应的货物
        {
            if(temp->next->total>no)//如果提取数量<库存数量
            {
                temp->next->total=temp->next->total - no;//库存数量减去提取数量
                printf("已经提取%s商品%d个,剩余%d个。\n",temp->next->goodsName,no,temp->next->total);
            }
            else if((0==temp->next->total-no)) //如果提取数量等于库存数量
            {
                printf("此商品剩余量为空，请及时录入补充！\n");
                p = temp->next;//库存为空，删除库存信息
                temp->next=p->next;
                free(p);
                t--;
            }
            else//如果提取数量大于库存数量，提示少量提取
            {
                printf("此商品总量只有%d，请少量提取！\n",temp->next->total);
            }
            return 1;
        }
        temp=temp->next;
    }
    printf("仓库中没有货号为：%s的货物。\n",goodsNo);
    return 0;
}


/* struct _iobuf {
 *         char *_ptr;   //文件输入的下一个位置
 *         int   _cnt;  //当前缓冲区的相对位置
 *         char *_base;  //指基础位置(即是文件的其始位置)
 *         int   _flag;  //文件标志
 *         int   _file;   //文件的有效性验证
 *         int   _charbuf;  //检查缓冲区状况,如果无缓冲区则不读取
 *         int   _bufsiz;   //文件的大小
 *         char *_tmpfname;  //临时文件名
 *         };
 * typedef struct _iobuf FILE;
 */

int readFile(Goods *head) //读取文件
{
    FILE* fp;
    Goods *p=head,*temp;
    if((fp = fopen("库存信息.txt","rb"))==NULL)
    {
        printf("没有相应的文件！\n");
        return 1;
    }

    if(t!=0)
    {
        printf("请程序内已经存入数据，请退出程序后再次读取！\n");
        return 0;
    }

    while ((fp->_flag==1||fp->_cnt>0))//验证文件标识，缓冲区位置
    {
        temp=(Goods*)malloc(sizeof(Goods));
        fread(temp,sizeof(Goods),1,fp);//读取信息，并构建链表
        temp->next = p->next;
        p->next = temp;
        t++;
    }
    printf("成功读入了%d个商品信息！\n",t);
    fclose(fp);
    system("pause");
    return 0;
}

void writeFile(Goods *head) //保存文件
{
    FILE* fp;
    Goods * temp = head->next;

    if((fp = fopen("库存信息.txt","wb"))==NULL)
    {
        printf("创建保存文件错误！\n");
        return;
    }

    while (NULL != temp)
    {
        fwrite(temp,sizeof(Goods),1,fp);//以结构体形式保存，浪费空间，但是稳定
        temp = temp->next;
    }
    printf("保存成功,保存了%d个记录。",t);
    fclose(fp);
    system("pause");
}

/*
    //此为文件读写的第二种方法，比第一种相对来说麻烦
    //第一种稳定，但浪费空间，文件读取时把结构体视为整体，指针不容易乱，第二种容易出错，指针容易丢失
int readFile(Goods *head)
{
    FILE* fp;
    Goods *p=head,*temp;

    if((fp = fopen("库存信息.txt","rb"))==NULL)
    {
        printf("没有相应的文件！\n");
        return 1;
    }

    while ((fp->_flag==1||fp->_cnt>0))//验证文件标识，缓冲区位置
    {
        temp=(Goods*)malloc(sizeof(Goods));
        fread(temp->goodsNo,sizeof(char),10,fp);
        fread(temp->goodsName,sizeof(char),20,fp);
        fread(temp->brand,sizeof(char),20,fp);
        fread(temp->price,sizeof(char),3,fp);
        fread(temp->model,sizeof(char),20,fp);
        fread(temp->day,sizeof(char),20,fp);
        fread(temp->total,sizeof(char),3,fp);

        temp->next = p->next;
        p->next = temp;
        t++;
    }
    printf("成功读入了%d个商品信息！\n",t);
    fclose(fp);
}

void writeFile(Goods *&head)
{
    FILE* fp;
    Goods * temp = head->next;

    if((fp = fopen("库存信息.txt","wb"))==NULL)
    {
        printf("创建保存文件错误！\n");
        return;
    }

    while (NULL  != temp)
    {
        fwrite(temp->goodsNo,sizeof(char),10,fp);
        fwrite(temp->goodsName,sizeof(char),20,fp);
        fwrite(temp->brand,sizeof(char),20,fp);
        fwrite(temp->price,sizeof(char),3,fp);
        fwrite(temp->model,sizeof(char),20,fp);
        fwrite(temp->day,sizeof(char),20,fp);
        fwrite(temp->total,sizeof(char),3,fp);
        temp = temp->next;
    }
    printf("保存成功,保存了%d个记录。",t);
    fclose(fp);
}
*/

int change(Goods *head)//修改仓库信息
{
    Goods *temp = head->next;
    char number[10];
    if(temp == NULL)//没有货物提示
    {
        printf("\n仓库中没有货物。请先录入货物信息:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("************************************修改货物信息********************************\n");
        printf("请输入想要修改的货物号：");
        scanf("%s",number);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsNo,number) && NULL!=temp)//比较查找相应货号提示并修改
            {
                printf("想要修改的货物信息如下：\n");//显示相应的货物信息
                printf("货物号：%s\n",temp->goodsNo);
                printf("商品名：%s\n",temp->goodsName);
                printf("品牌：%s\n",temp->brand);
                printf("型号：%s\n",temp->model);
                printf("价格：%4.3f\n",temp->price);
                printf("生产日期：%s\n",temp->day);
                printf("录入总数：%d\n",temp->total);
                printf("**************************************************************************\n");
                fflush(stdin);
                printf("请输入新的商品名：\n");//修改相应货物信息
                scanf("%s",temp->goodsName);
                fflush(stdin);
                printf("请输入新的品牌：\n");
                scanf("%s",temp->brand);
                fflush(stdin);
                printf("请输入新的型号:\n");
                scanf("%s",temp->model);
                fflush(stdin);
                printf("请输入新的价格：\n");
                scanf("%f",&temp->price);
                fflush(stdin);
                printf("请输入新的生产日期：\n");
                scanf("%s",temp->day);
                fflush(stdin);
                printf("请输入新的录入总数：\n");
                scanf("%d",&temp->total);
                printf("修改完成！！！！！\n");
                system("pause");

                return 0;
            }
        }
        if(NULL == temp)//如果没有相应的货物号提示
        {
            printf("没有相应的货物信息，请录入后查询！！！！ \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

void free_head(Goods *head) //删除链表
{
    while (head)//释放链表
    {
        Goods *temp = head;
        head = head->next;
        free(temp);
    }
    head = NULL;
}

int paixu(Goods *head) //按价格排序
{
    Goods *p1,*p2,*small;
    p1 = head;
    if(NULL == p1->next)//库存为空
    {
        printf("无任何信息，请录入后排序！\n");
        system("pause");
        return -1;
    }

    for(p1 = head->next; p1->next != NULL; p1 = p1->next)
    {
        small = p1;//节点数据，单重循环
        for(p2 = p1->next; p2; p2 = p2->next)//双重循环
        {
            if(p2->price <= small->price)//价格比较
            {
                Goods *temp=(Goods *)malloc(sizeof(Goods));
                strcpy(temp->goodsNo,p2->goodsNo);//交换相应节点的数据
                strcpy(p2->goodsNo,small->goodsNo);//字符串交换用strcpy
                strcpy(small->goodsNo,temp->goodsNo);

                strcpy(temp->goodsName,p2->goodsName);
                strcpy(p2->goodsName,small->goodsName);
                strcpy(small->goodsName,temp->goodsName);

                strcpy(temp->brand,p2->brand);
                strcpy(p2->brand,small->brand);
                strcpy(small->brand,temp->brand);

                strcpy(temp->model,p2->model);
                strcpy(p2->model,small->model);
                strcpy(small->model,temp->model);

                strcpy(temp->day,p2->day);
                strcpy(p2->day,small->day);
                strcpy(small->day,temp->day);

                temp->price=p2->price;
                p2->price=small->price;
                small->price=temp->price;

                temp->total=p2->total;
                p2->total=small->total;
                small->total=temp->total;

                free(temp);
            }
        }
    }
    printf("排序完成！\n");
    system("pause");
    return 0;
}

void help() //帮助
{
    printf("1.首次使用本系统时录入货物信息后请及时保存！\n");
    printf("2.保存文件默认路径和本软件是同一路径，文件名为“库存信息.txt”.\n");
    printf("3.用本系统录入过信息且保存成功，再次查看信息时，请先导入数据后再查看\n");
    printf("\n\t\t\t\t\t\t编者：计科0903 李静波\n\t\t\t\t\t\t2011.11\n");
    system("PAUSE");
    system("cls");
}

int main()
{
    char a;
    Goods *head;
    head = (Goods*)malloc(sizeof(Goods));
    head->next=NULL;
    menu ();
    while(1)
    {

        fflush(stdin);
        a=getchar();
        switch(a)
        {
        case '1' :
            system("cls");
            enter(head);//录入
            break;
        case '2' :
            system("cls");
            scan(head);//查询
            break;
        case '3' :
            system("cls");
            delete_xh(head);//取出货物
            break;
        case '4' :
            system("cls");
            writeFile(head);//保存文件
            break;
        case '5' :
            system("cls");
            paixu(head);//按价格排序
            break;
        case '6' :
            system("cls");
            change(head);//修改信息
            break;
            system ("exit");
        case '7' :
            system("cls");
            readFile(head);//读入文件信息
            break;
        case '8' :
            system("cls");
            help();//帮助
            break;
        case '9' :
            system("cls");
            free(head);//删除
            printf("/~~拜拜( ^_^ )/~~拜拜( ^_^ )/~~拜拜( ^_^ )/~~拜拜\n");
            system("PAUSE");
            return 0;
            break;
        default:
            system("cls");
            menu ();
            printf("╭∩╮(︶︿︶）╭∩╮系统鄙视你！╭∩╮(︶︿︶）╭∩╮系统鄙视你！o(╯□╰)o\n");
            printf("输入错误请重新选择：\n");
        }
    }
    return 0;
}
