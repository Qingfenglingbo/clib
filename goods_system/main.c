#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char     goodsNo[10];//��Ʒ���
    char    goodsName[20];//��Ʒ��
    char    brand[20];//Ʒ��
    char    model[20];//�ͺ�
    float    price;//�۸�
    char     day[20];//��������
    int    total;//����
    struct node * next;
} Goods;

int  t=0;//��Ʒ����

void menu ()  //���˵�
{
    printf("\t\t\t��Ʒ������ϵͳv1.0\n");
    printf("********************************************************************************\n");
    printf("�밴����(1-9)ѡ��:\n");
    printf("1.¼����Ʒ��Ϣ.\n");
    printf("2.��ѯ��Ʒ��Ϣ.\n");
    printf("3.ȡ������.\n");
    printf("4.������Ʒ��Ϣ.\n");
    printf("5.���۸�����.\n");
    printf("6.�޸���Ʒ��Ϣ.\n");
    printf("7.���ļ�������Ʒ��Ϣ.\n");
    printf("8.����.\n");
    printf("9.�˳�ϵͳ!\n");
    printf("********************************************************************************\n");
}


int enter(Goods *head) //¼���ȡ��Ϣ
{
    Goods *p=head,*temp;
    // Goods *q=head->next;
    char     goodsNo[20];//��Ʒ���
    char    goodsName[20];//��Ʒ��
    char    brand[20];//Ʒ��
    char    model[20];//�ͺ�
    float    price;//�۸�
    char     day[20];//��������
    int    total;//����
    char k;
    while(1)
    {
        Goods *q=head->next;
        fflush(stdin);
        printf("**********************************¼����Ʒ**************************************\n");
        printf("��%d����Ʒ��\n",t+1);
        printf("����ţ�\n");
        scanf("%s",goodsNo);
        fflush(stdin);
        printf("��Ʒ����\n");
        scanf("%s",goodsName);
        fflush(stdin);
        printf("Ʒ�ƣ�\n");
        scanf("%s",brand);
        fflush(stdin);
        printf("�ͺţ�\n");
        scanf("%s",model);
        fflush(stdin);
        printf("�۸�\n");
        scanf("%f",&price);
        fflush(stdin);
        printf("�������ڣ�\n");
        scanf("%s",day);
        fflush(stdin);
        printf("¼��������\n");
        scanf("%d",&total);
        printf("\n");

        while(NULL!=q)
        {
            if(!strcmp(q->goodsNo,goodsNo) && NULL!=q)//�Ƚϻ����Ƿ��ظ����ظ��������ӣ��������Բ���
            {
                q->total = q->total + total;
                printf("����Ϊ��%s��Ʒ�Ѿ����ڣ������ԭ����%d�����ӵ�%d����\n",q->goodsNo,q->total-total,q->total);
                printf("�������Բ��䣬���ı��������ԣ��뵽�������޸Ĵ��޸ģ�\n");
                system("pause");
                return 1;
            }
            q=q->next;
        }

        temp=(Goods*)malloc(sizeof(Goods));
        if(temp)//���Ų��ظ���¼����Ϣ
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
        printf("***********************����r�˻����˵�,�����������¼��*************************\n");
        if((k=getchar())=='r')//r�˳�¼��
        {
            system ("cls");
            return 0;
        }
    }
    return 0;
}

void menu2() //��ѯ����˵�
{
    printf("*******************************��ѯ������Ϣ*************************************\n");
    printf("�밴1~3ѡ��\n");
    printf("1.��ʾ���л�����Ϣ\n");
    printf("2.�������Ų�ѯ\n");
    printf("3.������������ѯ\n");
    printf("4.�˻����˵�\n");
    printf("*******************************��ѯ������Ϣ*************************************\n");
}

int print(Goods * head)//������л������Ϣ
{
    int i=1;
    Goods *temp=head->next;
    if(temp==NULL)//û�п�棬��ʾ
    {
        printf("\n�ֿ���û�л������¼�������Ϣ:\n");
        enter(head);
    }
    else
    {
        while(temp!=NULL)//���������Ϣ
        {
            printf("*******************************��%d��������Ϣ************************************\n",i++);
            printf("����ţ�%s\n",temp->goodsNo);
            printf("��Ʒ����%s\n",temp->goodsName);
            printf("Ʒ�ƣ�%s\n",temp->brand);
            printf("�ͺţ�%s\n",temp->model);
            printf("�۸�%4.3f\n",temp->price);
            printf("�������ڣ�%s\n",temp->day);
            printf("¼��������%d\n",temp->total);
            temp=temp->next;
        }
        if(NULL == temp)
            printf("���������л������Ϣ�������� \n");
        system("pause");
    }
    return 0;
}

int scanno(Goods *head) //�Ի��Ų�ѯ
{
    Goods *temp=head->next;
    char number[10];
    if(temp==NULL)//û�л�����Ϣ����ʾ
    {
        printf("\n�ֿ���û�л������¼�������Ϣ:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("���������ţ�");
        scanf("%s",number);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsNo,number) && NULL!=temp)//����Ӧ���ţ������Ӧ��Ϣ
            {
                printf("����ţ�%s\n",temp->goodsNo);
                printf("��Ʒ����%s\n",temp->goodsName);
                printf("Ʒ�ƣ�%s\n",temp->brand);
                printf("�ͺţ�%s\n",temp->model);
                printf("�۸�%4.3f\n",temp->price);
                printf("�������ڣ�%s\n",temp->day);
                printf("¼��������%d\n",temp->total);
                system("pause");
                return 0;
            }
        }
        if(NULL==temp)//û����Ӧ�Ļ��ţ���ʾ
        {
            printf("û����Ӧ�Ļ�����Ϣ����¼����ѯ�������� \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

int scanname(Goods *head) //�Ի�������ѯ
{
    Goods *temp=head->next;
    char name[5];
    if(temp==NULL)
    {
        printf("\n�ֿ���û�л������¼�������Ϣ:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("������������ƣ�");
        scanf("%s",name);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsName,name) && NULL!=temp)//����������ͬ�������
            {
                printf("����ţ�%s\n",temp->goodsNo);
                printf("��Ʒ����%s\n",temp->goodsName);
                printf("Ʒ�ƣ�%s\n",temp->brand);
                printf("�ͺţ�%s\n",temp->model);
                printf("�۸�%4.3f\n",temp->price);
                printf("�������ڣ�%s\n",temp->day);
                printf("¼��������%d\n",temp->total);
                system("pause");
                return 0;
            }
        }
        if(NULL==temp)//û��ƥ��������ƣ���ʾ
        {
            printf("û����Ӧ�Ļ�����Ϣ����¼����ѯ�������� \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

int scan(Goods *head) //�鿴ѡ��
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
            print(head);//������л�����Ϣ
            break;
        case '2':
            system("cls");
            scanno(head);//�����Ų�ѯ
            break;
        case '3':
            system("cls");
            scanname(head);//��������ѯ
            break;
        case '4':
            system("cls");//�������˵�
            return 0;
        default:
            system ("cls");
            printf("�q�ɨr(���ᣩ�q�ɨrϵͳ�����㣡�q�ɨr(���ᣩ�q�ɨrϵͳ�����㣡o(�s���t)o\n");
            printf("������ѡ��:\n");
            system("pause");
        }
    }
}

int delete_xh(Goods *head) //��ȡ������Ϣ
{
    char goodsNo[10];
    int no;
    Goods *temp=head,*p;
    printf("*********************************�������**************************************\n");
    printf("�������ȥ�Ļ���Ļ���:\n");
    fflush(stdin);
    scanf("%s",goodsNo);
    fflush(stdin);
    printf("�������ȥ�Ļ��������:\n");
    scanf("%d",&no);

    while(temp->next!=NULL)
    {
        if(!strcmp(temp->next->goodsNo,goodsNo))//�����Ų�����Ӧ�Ļ���
        {
            if(temp->next->total>no)//�����ȡ����<�������
            {
                temp->next->total=temp->next->total - no;//���������ȥ��ȡ����
                printf("�Ѿ���ȡ%s��Ʒ%d��,ʣ��%d����\n",temp->next->goodsName,no,temp->next->total);
            }
            else if((0==temp->next->total-no)) //�����ȡ�������ڿ������
            {
                printf("����Ʒʣ����Ϊ�գ��뼰ʱ¼�벹�䣡\n");
                p = temp->next;//���Ϊ�գ�ɾ�������Ϣ
                temp->next=p->next;
                free(p);
                t--;
            }
            else//�����ȡ�������ڿ����������ʾ������ȡ
            {
                printf("����Ʒ����ֻ��%d����������ȡ��\n",temp->next->total);
            }
            return 1;
        }
        temp=temp->next;
    }
    printf("�ֿ���û�л���Ϊ��%s�Ļ��\n",goodsNo);
    return 0;
}


/* struct _iobuf {
 *         char *_ptr;   //�ļ��������һ��λ��
 *         int   _cnt;  //��ǰ�����������λ��
 *         char *_base;  //ָ����λ��(�����ļ�����ʼλ��)
 *         int   _flag;  //�ļ���־
 *         int   _file;   //�ļ�����Ч����֤
 *         int   _charbuf;  //��黺����״��,����޻������򲻶�ȡ
 *         int   _bufsiz;   //�ļ��Ĵ�С
 *         char *_tmpfname;  //��ʱ�ļ���
 *         };
 * typedef struct _iobuf FILE;
 */

int readFile(Goods *head) //��ȡ�ļ�
{
    FILE* fp;
    Goods *p=head,*temp;
    if((fp = fopen("�����Ϣ.txt","rb"))==NULL)
    {
        printf("û����Ӧ���ļ���\n");
        return 1;
    }

    if(t!=0)
    {
        printf("��������Ѿ��������ݣ����˳�������ٴζ�ȡ��\n");
        return 0;
    }

    while ((fp->_flag==1||fp->_cnt>0))//��֤�ļ���ʶ��������λ��
    {
        temp=(Goods*)malloc(sizeof(Goods));
        fread(temp,sizeof(Goods),1,fp);//��ȡ��Ϣ������������
        temp->next = p->next;
        p->next = temp;
        t++;
    }
    printf("�ɹ�������%d����Ʒ��Ϣ��\n",t);
    fclose(fp);
    system("pause");
    return 0;
}

void writeFile(Goods *head) //�����ļ�
{
    FILE* fp;
    Goods * temp = head->next;

    if((fp = fopen("�����Ϣ.txt","wb"))==NULL)
    {
        printf("���������ļ�����\n");
        return;
    }

    while (NULL != temp)
    {
        fwrite(temp,sizeof(Goods),1,fp);//�Խṹ����ʽ���棬�˷ѿռ䣬�����ȶ�
        temp = temp->next;
    }
    printf("����ɹ�,������%d����¼��",t);
    fclose(fp);
    system("pause");
}

/*
    //��Ϊ�ļ���д�ĵڶ��ַ������ȵ�һ�������˵�鷳
    //��һ���ȶ������˷ѿռ䣬�ļ���ȡʱ�ѽṹ����Ϊ���壬ָ�벻�����ң��ڶ������׳���ָ�����׶�ʧ
int readFile(Goods *head)
{
    FILE* fp;
    Goods *p=head,*temp;

    if((fp = fopen("�����Ϣ.txt","rb"))==NULL)
    {
        printf("û����Ӧ���ļ���\n");
        return 1;
    }

    while ((fp->_flag==1||fp->_cnt>0))//��֤�ļ���ʶ��������λ��
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
    printf("�ɹ�������%d����Ʒ��Ϣ��\n",t);
    fclose(fp);
}

void writeFile(Goods *&head)
{
    FILE* fp;
    Goods * temp = head->next;

    if((fp = fopen("�����Ϣ.txt","wb"))==NULL)
    {
        printf("���������ļ�����\n");
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
    printf("����ɹ�,������%d����¼��",t);
    fclose(fp);
}
*/

int change(Goods *head)//�޸Ĳֿ���Ϣ
{
    Goods *temp = head->next;
    char number[10];
    if(temp == NULL)//û�л�����ʾ
    {
        printf("\n�ֿ���û�л������¼�������Ϣ:\n");
        enter(head);
    }
    else
    {
        fflush(stdin);
        printf("************************************�޸Ļ�����Ϣ********************************\n");
        printf("��������Ҫ�޸ĵĻ���ţ�");
        scanf("%s",number);
        for(; NULL!=temp; temp=temp->next)
        {
            if(!strcmp(temp->goodsNo,number) && NULL!=temp)//�Ƚϲ�����Ӧ������ʾ���޸�
            {
                printf("��Ҫ�޸ĵĻ�����Ϣ���£�\n");//��ʾ��Ӧ�Ļ�����Ϣ
                printf("����ţ�%s\n",temp->goodsNo);
                printf("��Ʒ����%s\n",temp->goodsName);
                printf("Ʒ�ƣ�%s\n",temp->brand);
                printf("�ͺţ�%s\n",temp->model);
                printf("�۸�%4.3f\n",temp->price);
                printf("�������ڣ�%s\n",temp->day);
                printf("¼��������%d\n",temp->total);
                printf("**************************************************************************\n");
                fflush(stdin);
                printf("�������µ���Ʒ����\n");//�޸���Ӧ������Ϣ
                scanf("%s",temp->goodsName);
                fflush(stdin);
                printf("�������µ�Ʒ�ƣ�\n");
                scanf("%s",temp->brand);
                fflush(stdin);
                printf("�������µ��ͺ�:\n");
                scanf("%s",temp->model);
                fflush(stdin);
                printf("�������µļ۸�\n");
                scanf("%f",&temp->price);
                fflush(stdin);
                printf("�������µ��������ڣ�\n");
                scanf("%s",temp->day);
                fflush(stdin);
                printf("�������µ�¼��������\n");
                scanf("%d",&temp->total);
                printf("�޸���ɣ���������\n");
                system("pause");

                return 0;
            }
        }
        if(NULL == temp)//���û����Ӧ�Ļ������ʾ
        {
            printf("û����Ӧ�Ļ�����Ϣ����¼����ѯ�������� \n");
            system("pause");
            return -1;
        }
    }
    return 0;
}

void free_head(Goods *head) //ɾ������
{
    while (head)//�ͷ�����
    {
        Goods *temp = head;
        head = head->next;
        free(temp);
    }
    head = NULL;
}

int paixu(Goods *head) //���۸�����
{
    Goods *p1,*p2,*small;
    p1 = head;
    if(NULL == p1->next)//���Ϊ��
    {
        printf("���κ���Ϣ����¼�������\n");
        system("pause");
        return -1;
    }

    for(p1 = head->next; p1->next != NULL; p1 = p1->next)
    {
        small = p1;//�ڵ����ݣ�����ѭ��
        for(p2 = p1->next; p2; p2 = p2->next)//˫��ѭ��
        {
            if(p2->price <= small->price)//�۸�Ƚ�
            {
                Goods *temp=(Goods *)malloc(sizeof(Goods));
                strcpy(temp->goodsNo,p2->goodsNo);//������Ӧ�ڵ������
                strcpy(p2->goodsNo,small->goodsNo);//�ַ���������strcpy
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
    printf("������ɣ�\n");
    system("pause");
    return 0;
}

void help() //����
{
    printf("1.�״�ʹ�ñ�ϵͳʱ¼�������Ϣ���뼰ʱ���棡\n");
    printf("2.�����ļ�Ĭ��·���ͱ������ͬһ·�����ļ���Ϊ�������Ϣ.txt��.\n");
    printf("3.�ñ�ϵͳ¼�����Ϣ�ұ���ɹ����ٴβ鿴��Ϣʱ�����ȵ������ݺ��ٲ鿴\n");
    printf("\n\t\t\t\t\t\t���ߣ��ƿ�0903 ���\n\t\t\t\t\t\t2011.11\n");
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
            enter(head);//¼��
            break;
        case '2' :
            system("cls");
            scan(head);//��ѯ
            break;
        case '3' :
            system("cls");
            delete_xh(head);//ȡ������
            break;
        case '4' :
            system("cls");
            writeFile(head);//�����ļ�
            break;
        case '5' :
            system("cls");
            paixu(head);//���۸�����
            break;
        case '6' :
            system("cls");
            change(head);//�޸���Ϣ
            break;
            system ("exit");
        case '7' :
            system("cls");
            readFile(head);//�����ļ���Ϣ
            break;
        case '8' :
            system("cls");
            help();//����
            break;
        case '9' :
            system("cls");
            free(head);//ɾ��
            printf("/~~�ݰ�( ^_^ )/~~�ݰ�( ^_^ )/~~�ݰ�( ^_^ )/~~�ݰ�\n");
            system("PAUSE");
            return 0;
            break;
        default:
            system("cls");
            menu ();
            printf("�q�ɨr(���ᣩ�q�ɨrϵͳ�����㣡�q�ɨr(���ᣩ�q�ɨrϵͳ�����㣡o(�s���t)o\n");
            printf("�������������ѡ��\n");
        }
    }
    return 0;
}
