#include <stdlib.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef struct DulNode //双向链表存储结构
{
    struct DulNode *prior;//前指针
    struct DulNode *next;//后指针
    int data;//节点数据
} DulNode,*DuList;

int InistList(DuList &L,char fh)//创建空链表，并初始化,fh为符号标识符
{
    L = (DuList)malloc(sizeof(DulNode));//动态分配存储空间
    if(fh == '-')
        L->data = 1;//L->data存放符号节点，如果是‘-’则为1，否则为0
    else
        L->data = 0;
    L->prior = L;
    L->next = L;
    return OK;
}

int DestroyList(DuList &L)//释放空间
{
    DuList p,q;//定义两个结构体指针
    if(!L)
        return ERROR;//链表不存在
    p = L->prior;//p指向链表头节点的前驱
    while(p!=L)//删除节点节点p
    {
        q = p->prior;
        free(p);//释放节点p的空间
        p = q;
    }
    free(L);//释放链表L的存储空间
    return OK;
}

int Insfirst(DuList &L,int e)//在头结点后插入新节点p
{
    DuList p,q;
    p = (DuList)malloc(sizeof(DulNode));
    p->data = e;
    q = L->next;
    L->next = p;
    p->prior = L;
    p->next = q;
    q->prior = p;
    return OK;
}

int Inslast(DuList &L,int e)//在链表最后插入新节点
{
    DuList p,q;
    p = (DuList)malloc(sizeof(DulNode));
    p ->data = e;
    q = L->prior;
    q->next = p;
    p->prior = q;//p->prior = L->prior;
    p->next = L;
    L->prior = p;
    return OK;
}

int CountNode(DuList L)//计算链表的节点数
{
    DuList p;
    p = L;
    int i;
    for(i = 0; p->next!=L; i++,p=p->next);
    return i;
}

int Count(int e)//计算节点元素e的位数
{
    int i,k;
    for(i = 1,k=1000; e/k<=0; i++,k=k/10);
    return i;
}

int Dzero(DuList &L)//去掉无效0
{
    DuList p;
    if(CountNode(L)<=1)
        return ERROR;//链表节点为空
    p = L->next;
    while(!p->data)
        p = p->next;
    L->next = p;
    p->prior = L;
    return OK;
}

int CountB(DuList L)//计算长整数位数函数
{
    int i;
    if(L->next == L)
        return 0;//空链表
    Dzero(L);//删除0
    i = Count(L->next->data)+(CountNode(L)-1)*4;//头节点数据的位数加上节点个数*4，每个节点有四位数
    return i;
}

int Creat(DuList &L,char *s)//通过相应的字符串建立链表
{
    InistList(L,s[0]);//建立空链表,判断符号

    if(*s=='-')
        s++;//整数为负数，去除-号位

    while(*s!='\0')//每个节点存放四位数（去除，）
    {
        if(*s==',')
        {
            //把4数位转成整形，插入链表尾
            Inslast(L,atoi(s-4));
        }
        s++;
    }
    Inslast(L,atoi(s-4));//最后节点的四位数
    return OK;
}

int Cmp(DuList L,DuList K)//结点相同时的比较两数大小
{
    DuList p,q;
    p=L->next;
    q=K->next;
    while(p!=L&&q!=K)//两链表都还没读完
    {
        if(p->data>q->data)
            return 1;//p的数值>q数值
        if(p->data<q->data)
            return -1;//p的数值<q数值
        p=p->next;
        q=q->next;
    }
    return 0;
}


int print(DuList L)//输出链表函数
{
    int i;
    DuList p;
    if(L->data==1&&L->next->data==0)//如果结果是-0则符号标识清0，输出0
        L->data = 0;
    if(L->data==1&&L->next->data!=0)
        cout<<"-";//输出符号
    p = L->next;
    while(p->data==0&&p->next!=L)//跳过无效零
        p=p->next;
    if(p==L)      //输出0
    {
        cout<<0;
        return OK;
    }
    if(p->next==L)     //p是最后一个节点，输出最后一个结点的数值
    {
        cout<<p->data;
        return OK;
    }
    if(p->next!=L)//p不是最后一个节点，输出数值并且输出‘，’作为分隔符
        cout<<p->data<<',';
    p=p->next;
    while(p->next!=L)    //循环输出不是最后结点的数
    {
        if(p->data==0)
            cout<<"0000"<<",";
        else
        {
            for(i=1; i<Count(p->data); i++) //节点上如果某一位为0，则输出0，否则输出数值
                cout<<'0';
            cout<<p->data<<",";
        }
        p=p->next;
    }
    if(p->data==0)
        cout<<"0000";//输出最后一个节点的数值
    else
    {
        for(i=1; i<Count(p->data); i++)
            cout<<'0';
        cout<<p->data;
    }
    return OK;
}

DuList add(DuList L,DuList K,char fh)//无符号加法,fh为符标识
{
    int temp,cf=0;//temp为和 cf为进位
    DuList p,q,R;//R为存储结果
    InistList(R,fh);//创建符号节点
    p=L->prior;
    q=K->prior;
    while(p!=L&&q!=K)        //从最后一个节点开始进行加法，进制10000
    {
        temp=p->data+q->data+cf;
        if(temp>=10000)//两数相加的和大于10000，temp=temp-10000且进位标识为1
        {
            Insfirst(R,temp-temp/10000*10000);//去掉最高位
            cf=1;
        }
        else
        {
            Insfirst(R,temp);//无进位
            cf=0;
        }
        p=p->prior;//p向前搜索
        q=q->prior;//q向前搜索
    }
    while(p!=L)//K加完，L还有没加的，p加上进位
    {
        temp=p->data+cf;
        cf=temp/10000;
        Insfirst(R,temp-temp/10000*10000);
        p=p->prior;
    }
    while(q!=K)//L加完，K还有没加的，q加进位
    {
        temp=q->data+cf;
        cf=temp/10000;
        Insfirst(R,temp-temp/10000*10000);
        q=q->prior;
    }
    if(cf!=0)
        Insfirst(R,cf);//最后判断是否还有进位，如果有在链表表头新增一个节点，数据为进位
    return R;
}

DuList sub(DuList L,DuList K,char fh)//无符号减法函数,参数L>K,fh为符号标识位
{
    DuList p,q,R;
    int temp,cf=0;
    InistList(R,fh);
    p=L->prior;
    q=K->prior;
    while(p!=L&&q!=K)//进行减法，不够减就借位
    {
        temp=p->data-q->data-cf;//两数相减并减去借位
        if(temp<0)//有借位
        {
            temp=temp+10000;
            Insfirst(R,temp);
            cf=1;//有借位
        }
        else
        {
            Insfirst(R,temp);//无借位
            cf=0;
        }
        p=p->prior;
        q=q->prior;
    }
    while(p!=L&&cf)//减完，还有借位
    {
        if(p->data-cf==0&&p->prior==L)//减去借位
            return R;
        temp=p->data-cf;
        if(temp>0)
        {
            Insfirst(R,temp);
            p=p->prior;
            break;
        }
        else
        {
            Insfirst(R,temp+10000);
            cf=1;
        }
        p=p->prior;
    }
    while(p!=L)//把L剩下的都复制过结果链表
    {
        Insfirst(R,p->data);
        p=p->prior;
    }
    return R;
}

DuList Computing(DuList L,DuList K,char ys)//四则运算控制
{
    DuList R;
    Dzero(L);//删去两位数前面的填补0
    Dzero(K);
    switch(ys)    //根据从主函数，链表节点数大的，绝对值就大
    {
    case '+'://根据整数的符号判别是进行加法还是减法，同时判断出结果的符号，再调用无符号加法或者减法算出结果
        if(!L->data&&!K->data)
            R=add(L,K,'+');//两加数都为正数，执行加法，符号标识位为+

        else if(L->data&&K->data)
            R=add(L,K,'-');//两加数都是负数执行加法，运算结果为负，符号标识位为-

        else if(!L->data&&K->data)//被加数是正数，加是负数
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'+');//被绝对值加数大于加数绝对值，执行减法，符号标识位为+

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'-');//被加数绝对值小于加数绝对值，用被加数减去加数，符号标识位为-

            else if(Cmp(L,K)==1||Cmp(L,K)==0)//1为L>K，0为=
                R=sub(L,K,'+');//两链表节点数相同，L值大于K值，用被加数减去加数，符号标识符为+

            else if(Cmp(L,K)==-1) //-1为L<K
                R=sub(K,L,'-');//两链表节点数相同，用加数减去被加数，符号标识符为-
        }

        else//被加数是负数，加数是正数
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'-');// 被加数绝对值大于加数绝对值，执行被加数减去加数，符号标识符为-

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'+');//被加数绝对值小于加数，执行加数减去被加数，符号标识符为+

            else if(Cmp(L,K)==1||Cmp(L,K)==0)
                R=sub(L,K,'-');

            else if(Cmp(L,K)==-1)
                R=sub(K,L,'+');
        }
        break;
    case '-'://根据整数的符号判别是进行加法还是减法，同时判断出结果的符号，再调用无符号加法或者减法算出结果
        if(!L->data&&K->data)
            R=add(L,K,'+');//被减数为正减数为负，执行加法，符号标识位为+

        else if(L->data&&!K->data)
            R=add(L,K,'-');//被减数为负减数为正，执行加法，符号标识位为-

        else if(L->data&&K->data)//被减数为负减数为负
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'-');//被减数绝对值大于减数绝对值，用被减数减去减数，符号标识位为+

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'+');//被减数绝对值小于减数绝对值，用减数减去被减数，符号标识位为+

            else if(Cmp(L,K)==0||Cmp(L,K)==1)
                R=sub(L,K,'-');

            else if(Cmp(L,K)==-1)
                R=sub(K,L,'+');
        }
        else//被减数为正减数为正
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'+');//被减数绝对值大于减数绝对值，用减数减去被减数，符号标识位为+
            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'-');//被减数绝对值小于减数绝对值，用被减数减去减数，符号标识位为-
            else if(Cmp(L,K)==0||Cmp(L,K)==1)
                R=sub(L,K,'+');//两链表节点数相同，L值大于等于K值，用被减数减去减数，符号标识符为+
            else if(Cmp(L,K)==-1)
                R=sub(K,L,'-');//两链表节点数相同，L值小于K值，用减数减去被减数加数，符号标识符为-
        }
        break;
    }
    return R;
}

int PanGS(char *s)//判断输入格式
{
    int k,i=1;//k为节点字符数
    if((*s<'0'&&*s!='-')||(*s>'9'))
        return ERROR;//输入的不是数字也不是‘-’，出错
    if(*s=='-') k=0;//负数符号不算入节点位数
    else k=1;
    while(*(s+i)!=','&&*(s+i)!='\0')//输入的字符不是','和'\0'，输入错误
    {
        if(*(s+i)<'0'||*(s+i)>'9')
            return ERROR;
        k++;
        i++;
    }
    if(k>4)
        return ERROR;//每个节点输入的字符大于4个，输入错误
    if(*(s+i)=='\0')
        return OK;//输入完成
    k=4;
    while(*(s+i)!='\0')//输入的不是‘\0’并且不是‘，’则输入错误
    {
        if((*(s+i)<'0'&&*(s+i)!=',')||(*(s+i)>'9'))
            return ERROR;
        if(*(s+i)==',')//如果遇到‘，’，k从-1开始算保证每个节点位数是四位
        {
            if(k!=4)//中间节点的位数不是四位，输入错误
                return ERROR;
            k=-1;
        }
        k++;//如果遇到‘，’后，k从零开始
        i++;
    }
    if(k!=4)
        return ERROR;
    return OK;
}

int Menu1()//显示主菜单
{
    cout<<"1、按1加法"<<endl<<"2、按2减法"<<endl;
    return OK;
}

int Menu2()//显示菜单信息
{
    cout<<"1、按1继续运算"<<endl<<"2、按2返回主选单"<<endl;
    return OK;
}

int InputS(char *cz,char *cz1)//从键盘输入两个长整数
{
    cout<<"请输入整数!"<<endl;
    cout<<"整数1:";
    cin>>cz;
    while(!PanGS(cz))//判断输入格式是否正确
    {
        cout<<"输入格式错误,请重新输入!"<<endl
            <<"输入格式应为：XXXX，XXXX，……，XXXX(X是数字)"<<endl<<"整数1:";
        cin>>cz;//输入错误，重新输入
    }
    cout<<"整数2:";
    cin>>cz1;
    while(!PanGS(cz1))//判断输入格式是否正确
    {
        cout<<"输入格式错误,请重新输入!"<<endl
            <<"输入格式应为：XXXX，XXXX，……，XXXX(X是数字)"<<endl<<"整数2:";
        cin>>cz1;//输入错误，重新输入
    }
    return OK;
}

int main()
{
    char cz[99999];      //定义字符串数组，用里保存从键盘输入的长整数
    char cz1[99999];
    DuList L1,L2,R;
    int flag=1;
    char xz;

    cout<<"整数的输入格式为：XXXX，XXXX，……，XXXX;"<<endl;
    while(1)
    {
        Menu1();
        cin>>xz;
        while(xz<='0'||xz>'2')//判断键入的是否为无效命令
        {
            cout<<"输入命令代号有错，请重新输入!"<<endl;
            Menu1();
            cin>>xz;//输入的操作无效重新输入
        }
        switch(xz)//选择执行的运算
        {
        case '1':
            while(flag==1)//同一个运算继续进行下去
            {
                cout<<"现在执行的是加法运算"<<endl;
                InputS(cz,cz1);//从键盘输入长整数形式的字符串，同时容错
                Creat(L1,cz);//把长整数字符串转换为循环链表的储存结构
                Creat(L2,cz1);
                R=Computing(L1,L2,'+');
                cout<<"运算结果:";
                print(R);//结果以长整数标准形式输出
                cout<<endl;
                DestroyList(L1);//销毁函数，以释放空间
                DestroyList(L2);
                DestroyList(R);
                Menu2();
                cin>>flag;//是否退出返回主菜单的标志
            }
            break;
        case '2':
            while(flag==1)
            {
                cout<<"现在执行的是减法运算"<<endl;
                InputS(cz,cz1);//从键盘输入长整数形式的字符串，且同时判别输入格式是否有错
                Creat(L1,cz);//把长整数字符串转换为循环链表的储存结构
                Creat(L2,cz1);
                R=Computing(L1,L2,'-');
                cout<<"运算结果:";
                print(R);
                cout<<endl;
                DestroyList(L1);//销毁函数，以释放空间
                DestroyList(L2);
                DestroyList(R);
                Menu2();
                cin>>flag; //是否退出返回主菜单的标志
            }
            break;
        }
        flag=1;
    }
    return 0;
}
