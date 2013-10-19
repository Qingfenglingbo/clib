#include <stdlib.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef struct DulNode //˫������洢�ṹ
{
    struct DulNode *prior;//ǰָ��
    struct DulNode *next;//��ָ��
    int data;//�ڵ�����
} DulNode,*DuList;

int InistList(DuList &L,char fh)//��������������ʼ��,fhΪ���ű�ʶ��
{
    L = (DuList)malloc(sizeof(DulNode));//��̬����洢�ռ�
    if(fh == '-')
        L->data = 1;//L->data��ŷ��Žڵ㣬����ǡ�-����Ϊ1������Ϊ0
    else
        L->data = 0;
    L->prior = L;
    L->next = L;
    return OK;
}

int DestroyList(DuList &L)//�ͷſռ�
{
    DuList p,q;//���������ṹ��ָ��
    if(!L)
        return ERROR;//��������
    p = L->prior;//pָ������ͷ�ڵ��ǰ��
    while(p!=L)//ɾ���ڵ�ڵ�p
    {
        q = p->prior;
        free(p);//�ͷŽڵ�p�Ŀռ�
        p = q;
    }
    free(L);//�ͷ�����L�Ĵ洢�ռ�
    return OK;
}

int Insfirst(DuList &L,int e)//��ͷ��������½ڵ�p
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

int Inslast(DuList &L,int e)//�������������½ڵ�
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

int CountNode(DuList L)//��������Ľڵ���
{
    DuList p;
    p = L;
    int i;
    for(i = 0; p->next!=L; i++,p=p->next);
    return i;
}

int Count(int e)//����ڵ�Ԫ��e��λ��
{
    int i,k;
    for(i = 1,k=1000; e/k<=0; i++,k=k/10);
    return i;
}

int Dzero(DuList &L)//ȥ����Ч0
{
    DuList p;
    if(CountNode(L)<=1)
        return ERROR;//����ڵ�Ϊ��
    p = L->next;
    while(!p->data)
        p = p->next;
    L->next = p;
    p->prior = L;
    return OK;
}

int CountB(DuList L)//���㳤����λ������
{
    int i;
    if(L->next == L)
        return 0;//������
    Dzero(L);//ɾ��0
    i = Count(L->next->data)+(CountNode(L)-1)*4;//ͷ�ڵ����ݵ�λ�����Ͻڵ����*4��ÿ���ڵ�����λ��
    return i;
}

int Creat(DuList &L,char *s)//ͨ����Ӧ���ַ�����������
{
    InistList(L,s[0]);//����������,�жϷ���

    if(*s=='-')
        s++;//����Ϊ������ȥ��-��λ

    while(*s!='\0')//ÿ���ڵ�����λ����ȥ������
    {
        if(*s==',')
        {
            //��4��λת�����Σ���������β
            Inslast(L,atoi(s-4));
        }
        s++;
    }
    Inslast(L,atoi(s-4));//���ڵ����λ��
    return OK;
}

int Cmp(DuList L,DuList K)//�����ͬʱ�ıȽ�������С
{
    DuList p,q;
    p=L->next;
    q=K->next;
    while(p!=L&&q!=K)//��������û����
    {
        if(p->data>q->data)
            return 1;//p����ֵ>q��ֵ
        if(p->data<q->data)
            return -1;//p����ֵ<q��ֵ
        p=p->next;
        q=q->next;
    }
    return 0;
}


int print(DuList L)//���������
{
    int i;
    DuList p;
    if(L->data==1&&L->next->data==0)//��������-0����ű�ʶ��0�����0
        L->data = 0;
    if(L->data==1&&L->next->data!=0)
        cout<<"-";//�������
    p = L->next;
    while(p->data==0&&p->next!=L)//������Ч��
        p=p->next;
    if(p==L)      //���0
    {
        cout<<0;
        return OK;
    }
    if(p->next==L)     //p�����һ���ڵ㣬������һ��������ֵ
    {
        cout<<p->data;
        return OK;
    }
    if(p->next!=L)//p�������һ���ڵ㣬�����ֵ���������������Ϊ�ָ���
        cout<<p->data<<',';
    p=p->next;
    while(p->next!=L)    //ѭ�����������������
    {
        if(p->data==0)
            cout<<"0000"<<",";
        else
        {
            for(i=1; i<Count(p->data); i++) //�ڵ������ĳһλΪ0�������0�����������ֵ
                cout<<'0';
            cout<<p->data<<",";
        }
        p=p->next;
    }
    if(p->data==0)
        cout<<"0000";//������һ���ڵ����ֵ
    else
    {
        for(i=1; i<Count(p->data); i++)
            cout<<'0';
        cout<<p->data;
    }
    return OK;
}

DuList add(DuList L,DuList K,char fh)//�޷��żӷ�,fhΪ����ʶ
{
    int temp,cf=0;//tempΪ�� cfΪ��λ
    DuList p,q,R;//RΪ�洢���
    InistList(R,fh);//�������Žڵ�
    p=L->prior;
    q=K->prior;
    while(p!=L&&q!=K)        //�����һ���ڵ㿪ʼ���мӷ�������10000
    {
        temp=p->data+q->data+cf;
        if(temp>=10000)//������ӵĺʹ���10000��temp=temp-10000�ҽ�λ��ʶΪ1
        {
            Insfirst(R,temp-temp/10000*10000);//ȥ�����λ
            cf=1;
        }
        else
        {
            Insfirst(R,temp);//�޽�λ
            cf=0;
        }
        p=p->prior;//p��ǰ����
        q=q->prior;//q��ǰ����
    }
    while(p!=L)//K���꣬L����û�ӵģ�p���Ͻ�λ
    {
        temp=p->data+cf;
        cf=temp/10000;
        Insfirst(R,temp-temp/10000*10000);
        p=p->prior;
    }
    while(q!=K)//L���꣬K����û�ӵģ�q�ӽ�λ
    {
        temp=q->data+cf;
        cf=temp/10000;
        Insfirst(R,temp-temp/10000*10000);
        q=q->prior;
    }
    if(cf!=0)
        Insfirst(R,cf);//����ж��Ƿ��н�λ��������������ͷ����һ���ڵ㣬����Ϊ��λ
    return R;
}

DuList sub(DuList L,DuList K,char fh)//�޷��ż�������,����L>K,fhΪ���ű�ʶλ
{
    DuList p,q,R;
    int temp,cf=0;
    InistList(R,fh);
    p=L->prior;
    q=K->prior;
    while(p!=L&&q!=K)//���м������������ͽ�λ
    {
        temp=p->data-q->data-cf;//�����������ȥ��λ
        if(temp<0)//�н�λ
        {
            temp=temp+10000;
            Insfirst(R,temp);
            cf=1;//�н�λ
        }
        else
        {
            Insfirst(R,temp);//�޽�λ
            cf=0;
        }
        p=p->prior;
        q=q->prior;
    }
    while(p!=L&&cf)//���꣬���н�λ
    {
        if(p->data-cf==0&&p->prior==L)//��ȥ��λ
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
    while(p!=L)//��Lʣ�µĶ����ƹ��������
    {
        Insfirst(R,p->data);
        p=p->prior;
    }
    return R;
}

DuList Computing(DuList L,DuList K,char ys)//�����������
{
    DuList R;
    Dzero(L);//ɾȥ��λ��ǰ����0
    Dzero(K);
    switch(ys)    //���ݴ�������������ڵ�����ģ�����ֵ�ʹ�
    {
    case '+'://���������ķ����б��ǽ��мӷ����Ǽ�����ͬʱ�жϳ�����ķ��ţ��ٵ����޷��żӷ����߼���������
        if(!L->data&&!K->data)
            R=add(L,K,'+');//��������Ϊ������ִ�мӷ������ű�ʶλΪ+

        else if(L->data&&K->data)
            R=add(L,K,'-');//���������Ǹ���ִ�мӷ���������Ϊ�������ű�ʶλΪ-

        else if(!L->data&&K->data)//�����������������Ǹ���
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'+');//������ֵ�������ڼ�������ֵ��ִ�м��������ű�ʶλΪ+

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'-');//����������ֵС�ڼ�������ֵ���ñ�������ȥ���������ű�ʶλΪ-

            else if(Cmp(L,K)==1||Cmp(L,K)==0)//1ΪL>K��0Ϊ=
                R=sub(L,K,'+');//������ڵ�����ͬ��Lֵ����Kֵ���ñ�������ȥ���������ű�ʶ��Ϊ+

            else if(Cmp(L,K)==-1) //-1ΪL<K
                R=sub(K,L,'-');//������ڵ�����ͬ���ü�����ȥ�����������ű�ʶ��Ϊ-
        }

        else//�������Ǹ���������������
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'-');// ����������ֵ���ڼ�������ֵ��ִ�б�������ȥ���������ű�ʶ��Ϊ-

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'+');//����������ֵС�ڼ�����ִ�м�����ȥ�����������ű�ʶ��Ϊ+

            else if(Cmp(L,K)==1||Cmp(L,K)==0)
                R=sub(L,K,'-');

            else if(Cmp(L,K)==-1)
                R=sub(K,L,'+');
        }
        break;
    case '-'://���������ķ����б��ǽ��мӷ����Ǽ�����ͬʱ�жϳ�����ķ��ţ��ٵ����޷��żӷ����߼���������
        if(!L->data&&K->data)
            R=add(L,K,'+');//������Ϊ������Ϊ����ִ�мӷ������ű�ʶλΪ+

        else if(L->data&&!K->data)
            R=add(L,K,'-');//������Ϊ������Ϊ����ִ�мӷ������ű�ʶλΪ-

        else if(L->data&&K->data)//������Ϊ������Ϊ��
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'-');//����������ֵ���ڼ�������ֵ���ñ�������ȥ���������ű�ʶλΪ+

            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'+');//����������ֵС�ڼ�������ֵ���ü�����ȥ�����������ű�ʶλΪ+

            else if(Cmp(L,K)==0||Cmp(L,K)==1)
                R=sub(L,K,'-');

            else if(Cmp(L,K)==-1)
                R=sub(K,L,'+');
        }
        else//������Ϊ������Ϊ��
        {
            if(CountNode(L)>CountNode(K))
                R=sub(L,K,'+');//����������ֵ���ڼ�������ֵ���ü�����ȥ�����������ű�ʶλΪ+
            else if(CountNode(L)<CountNode(K))
                R=sub(K,L,'-');//����������ֵС�ڼ�������ֵ���ñ�������ȥ���������ű�ʶλΪ-
            else if(Cmp(L,K)==0||Cmp(L,K)==1)
                R=sub(L,K,'+');//������ڵ�����ͬ��Lֵ���ڵ���Kֵ���ñ�������ȥ���������ű�ʶ��Ϊ+
            else if(Cmp(L,K)==-1)
                R=sub(K,L,'-');//������ڵ�����ͬ��LֵС��Kֵ���ü�����ȥ���������������ű�ʶ��Ϊ-
        }
        break;
    }
    return R;
}

int PanGS(char *s)//�ж������ʽ
{
    int k,i=1;//kΪ�ڵ��ַ���
    if((*s<'0'&&*s!='-')||(*s>'9'))
        return ERROR;//����Ĳ�������Ҳ���ǡ�-��������
    if(*s=='-') k=0;//�������Ų�����ڵ�λ��
    else k=1;
    while(*(s+i)!=','&&*(s+i)!='\0')//������ַ�����','��'\0'���������
    {
        if(*(s+i)<'0'||*(s+i)>'9')
            return ERROR;
        k++;
        i++;
    }
    if(k>4)
        return ERROR;//ÿ���ڵ�������ַ�����4�����������
    if(*(s+i)=='\0')
        return OK;//�������
    k=4;
    while(*(s+i)!='\0')//����Ĳ��ǡ�\0�����Ҳ��ǡ��������������
    {
        if((*(s+i)<'0'&&*(s+i)!=',')||(*(s+i)>'9'))
            return ERROR;
        if(*(s+i)==',')//���������������k��-1��ʼ�㱣֤ÿ���ڵ�λ������λ
        {
            if(k!=4)//�м�ڵ��λ��������λ���������
                return ERROR;
            k=-1;
        }
        k++;//���������������k���㿪ʼ
        i++;
    }
    if(k!=4)
        return ERROR;
    return OK;
}

int Menu1()//��ʾ���˵�
{
    cout<<"1����1�ӷ�"<<endl<<"2����2����"<<endl;
    return OK;
}

int Menu2()//��ʾ�˵���Ϣ
{
    cout<<"1����1��������"<<endl<<"2����2������ѡ��"<<endl;
    return OK;
}

int InputS(char *cz,char *cz1)//�Ӽ�����������������
{
    cout<<"����������!"<<endl;
    cout<<"����1:";
    cin>>cz;
    while(!PanGS(cz))//�ж������ʽ�Ƿ���ȷ
    {
        cout<<"�����ʽ����,����������!"<<endl
            <<"�����ʽӦΪ��XXXX��XXXX��������XXXX(X������)"<<endl<<"����1:";
        cin>>cz;//���������������
    }
    cout<<"����2:";
    cin>>cz1;
    while(!PanGS(cz1))//�ж������ʽ�Ƿ���ȷ
    {
        cout<<"�����ʽ����,����������!"<<endl
            <<"�����ʽӦΪ��XXXX��XXXX��������XXXX(X������)"<<endl<<"����2:";
        cin>>cz1;//���������������
    }
    return OK;
}

int main()
{
    char cz[99999];      //�����ַ������飬���ﱣ��Ӽ�������ĳ�����
    char cz1[99999];
    DuList L1,L2,R;
    int flag=1;
    char xz;

    cout<<"�����������ʽΪ��XXXX��XXXX��������XXXX;"<<endl;
    while(1)
    {
        Menu1();
        cin>>xz;
        while(xz<='0'||xz>'2')//�жϼ�����Ƿ�Ϊ��Ч����
        {
            cout<<"������������д�����������!"<<endl;
            Menu1();
            cin>>xz;//����Ĳ�����Ч��������
        }
        switch(xz)//ѡ��ִ�е�����
        {
        case '1':
            while(flag==1)//ͬһ���������������ȥ
            {
                cout<<"����ִ�е��Ǽӷ�����"<<endl;
                InputS(cz,cz1);//�Ӽ������볤������ʽ���ַ�����ͬʱ�ݴ�
                Creat(L1,cz);//�ѳ������ַ���ת��Ϊѭ������Ĵ���ṹ
                Creat(L2,cz1);
                R=Computing(L1,L2,'+');
                cout<<"������:";
                print(R);//����Գ�������׼��ʽ���
                cout<<endl;
                DestroyList(L1);//���ٺ��������ͷſռ�
                DestroyList(L2);
                DestroyList(R);
                Menu2();
                cin>>flag;//�Ƿ��˳��������˵��ı�־
            }
            break;
        case '2':
            while(flag==1)
            {
                cout<<"����ִ�е��Ǽ�������"<<endl;
                InputS(cz,cz1);//�Ӽ������볤������ʽ���ַ�������ͬʱ�б������ʽ�Ƿ��д�
                Creat(L1,cz);//�ѳ������ַ���ת��Ϊѭ������Ĵ���ṹ
                Creat(L2,cz1);
                R=Computing(L1,L2,'-');
                cout<<"������:";
                print(R);
                cout<<endl;
                DestroyList(L1);//���ٺ��������ͷſռ�
                DestroyList(L2);
                DestroyList(R);
                Menu2();
                cin>>flag; //�Ƿ��˳��������˵��ı�־
            }
            break;
        }
        flag=1;
    }
    return 0;
}
