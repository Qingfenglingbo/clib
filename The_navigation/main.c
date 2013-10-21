#include <stdio.h>
#define Max 99999
#define NUM 10
//#include<windows.h>

//���������ڱ�
typedef struct Way
{
    int adj;  //�ߵĳ���
} Way;

//��������
typedef struct VertexType
{
    int number;  //λ�ñ��
    char name[50];  // λ������
    char inf[50]; //�������
} VertexType;

//ͼ������
typedef struct
{
    VertexType vex[NUM]; //�����
    Way arcs[NUM][NUM]; /* ͼ�еıߣ���Ϊ�����ľ��� */
    int v_num,e_num;
} Map;

Map G;   //ͼ

int P[NUM][NUM];  //·�������ж�
long int D[NUM]; //���·������

void Create_school(int v,int a); //��ͼ����
void Print_Inf();
void ShortestPath(int num); //���·��
void output(int sight1,int sight2);

/*
on the linux
int GetModuleFileName(char* name, int size)
{
  FILE* stream = fopen("/proc/self/cmdline", "r");
  fgets(name, size, stream);
  fclose(stream);

  return strlen(name);
}
*/
int main()
{
    char a;
    int i,j;
    Create_school(NUM,11);

    while(1)
    {
        Print_Inf();//��Ϣ
        printf("��ѡ��\n1.��ѯ����·��\n");
        printf("2.�˳�\n");
        fflush(stdin);
        a=getchar();
        switch(a)
        {
        case '1' :
            printf("��ѡ�����ص�Ĵ��ţ�0��9����");
            fflush(stdin);
            while(scanf("%d",&i))
            {
                if(i>=0 && i<=9)
                    break;
                else
                {
                    printf("������0--9�ڵ���Ӧ�������֣�\n");
                    printf("��ѡ�����ص�Ĵ��ţ�0��9����");
                    fflush(stdin);
                }
            }
            printf("��ѡ���յ㾰��Ĵ��ţ�0��9����");
            fflush(stdin);
            while(scanf("%d",&j))
            {
                if(j>=0 && j<=9)
                    break;
                else
                {
                    printf("������0--9�ڵ���Ӧ�������֣�\n");
                    printf("��ѡ���յ�ص�Ĵ��ţ�0��9����");
                    fflush(stdin);
                }
            }
            ShortestPath(i); //���·��
            output(i,j);     //���
            printf("\n\n�밴�������ʼ�´ε���...\n");
            system("pause");
            break;
        case '2' :
            system("cls");
            printf("/~~�ݰ�( ^_^ )/~~�ݰ�( ^_^ )/~~�ݰ�( ^_^ )/~~�ݰ�\n");
            system("PAUSE");
            return 0;
            break;
        default:
            system("cls");
            printf("\n�������������ѡ��\n");
        }
    }
    return 0;
}

void Create_school(int v,int a)
{
    char name[10];
    char inf[10];
    char szPath[256],*pSz;
    GetModuleFileName(NULL,szPath,256);//��ȡ��ǰ�����ļ�·��
    pSz=strrchr(szPath,'\\');
    if(pSz != NULL)
    {
        *pSz = '\0';
        strcat(szPath, "\\school_inf.ini");//�����ļ�
    }

    int i,j;
    G.v_num=v; //���㣬��
    G.e_num=a;
    for(i=0; i<G.v_num; ++i)//�趨�����ź������Ϣ
    {
        sprintf(name,"%s%d","name",i);
        sprintf(inf,"%s%d","inf",i);
        G.vex[i].number=i;
        GetPrivateProfileString("INF",name,NULL,G.vex[i].name,50,szPath);//��ȡλ������
        GetPrivateProfileString("INF",inf,NULL,G.vex[i].inf,50,szPath);//��ȡλ����Ϣ
    }
    //�����еı߼ٶ�Ϊ���Ϊ��������֮���ǲ��ɵ���
    for(i=0; i<G.v_num; ++i)
        for(j=0; j<G.v_num; ++j)
            G.arcs[i][j].adj=Max;
    //������ͨ·��
    G.arcs[0][2].adj=G.arcs[2][0].adj= GetPrivateProfileInt("INF","0-->2", 0,szPath);
    G.arcs[0][3].adj=G.arcs[3][0].adj=GetPrivateProfileInt("INF", "0-->3", 0,szPath);
    G.arcs[1][2].adj=G.arcs[2][1].adj=GetPrivateProfileInt("INF", "1-->2", 0,szPath);
    G.arcs[1][4].adj=G.arcs[4][1].adj=GetPrivateProfileInt("INF", "1-->4", 0,szPath);
    G.arcs[1][6].adj=G.arcs[6][1].adj=GetPrivateProfileInt("INF", "1-->6", 0,szPath);
    G.arcs[1][7].adj=G.arcs[7][1].adj=GetPrivateProfileInt("INF", "1-->7", 0,szPath);
    G.arcs[1][9].adj=G.arcs[9][1].adj=GetPrivateProfileInt("INF", "1-->9", 0,szPath);
    G.arcs[2][4].adj=G.arcs[4][2].adj=GetPrivateProfileInt("INF", "2-->4", 0,szPath);
    G.arcs[2][7].adj=G.arcs[7][2].adj=GetPrivateProfileInt("INF", "2-->7", 0,szPath);
    G.arcs[2][9].adj=G.arcs[9][2].adj=GetPrivateProfileInt("INF", "2-->9", 0,szPath);
    G.arcs[3][4].adj=G.arcs[4][3].adj=GetPrivateProfileInt("INF", "3-->4", 0,szPath);
    G.arcs[3][5].adj=G.arcs[5][3].adj=GetPrivateProfileInt("INF", "3-->5", 0,szPath);
    G.arcs[4][5].adj=G.arcs[5][4].adj=GetPrivateProfileInt("INF", "4-->5", 0,szPath);
    G.arcs[4][9].adj=G.arcs[9][4].adj=GetPrivateProfileInt("INF", "4-->9", 0,szPath);
    G.arcs[5][8].adj=G.arcs[8][5].adj=GetPrivateProfileInt("INF", "5-->8", 0,szPath);
    G.arcs[6][7].adj=G.arcs[7][6].adj=GetPrivateProfileInt("INF", "6-->7", 0,szPath);
    G.arcs[6][9].adj=G.arcs[9][6].adj=GetPrivateProfileInt("INF", "6-->9", 0,szPath);
    G.arcs[7][8].adj=G.arcs[8][7].adj=GetPrivateProfileInt("INF", "7-->8", 0,szPath);
    G.arcs[7][9].adj=G.arcs[9][7].adj=GetPrivateProfileInt("INF", "7-->9", 0,szPath);
}

void Print_Inf()
{
    int i,k=0;
    printf("\n*********************������Ϣ�Ƽ���ѧ������У������ϵͳ*************************\n");
    for(i=0; i<NUM; i++)
    {
        printf("���ţ�%d   ���ƣ� %-10s",i,G.vex[i].name);
        printf("\t��Ϣ������%-25s\n",G.vex[i].inf);
        k=k+1;
    }
    printf("\n********************************************************************************");
}

void ShortestPath(int num) // �Ͻ�˹�����㷨���·��
{
    int v,w,i,t;  //i��w��vΪ��������
    int final[NUM];
    int min;
    for(v=0; v<NUM; v++)
    {
        final[v]=0;  //�㼯�ϱ�ǳ�ʼ0
        D[v]=G.arcs[num][v].adj;//�������Ȩֵ-��1
        for(w=0; w<NUM; w++) // ��ʼ·��Ϊ��
            P[v][w]=0;
        if(D[v]<99999)  //�ж�·������
        {
            P[v][num]=1; //����Ϊ1
            P[v][v]=1;
        }
    }

    D[num]=0; //�Լ����Լ�Ȩֵ0
    final[num]=1;      //�趥������S����
    // ��ʼ��ѭ����ÿһ�����num��ĳ����������·������������뵽S����
    for(i=0; i<NUM; ++i)
    {
        min=Max;     //�赱ǰ��֪�붥��num���������
        for(w=0; w<NUM; ++w)
            if(!final[w])  //û�ȽϹ���
                if(D[w]<min)   //��W���붥��num�����
                {
                    v=w;//��¼�õ㣬�Ա��´δӸõ�Ƚ�
                    min=D[w];
                }
        final[v]=1;   //��num�������v��������w�����뵽s����
        for(w=0; w<NUM; ++w) // ���µ�ǰ���·���������
            if(!final[w]&&((min+G.arcs[v][w].adj)<D[w]))// ����s���ϣ���Խ϶̾���+�˵㵽���е���̾����ĳ��ȱ�num�㵽w������
            {
                D[w]=min+G.arcs[v][w].adj;//������̾��루Ȩֵ��
                for(t=0; t<NUM; t++)
                    P[w][t]=P[v][t];//����·��
                P[w][w]=1;//��Ϊ�Ѿ��ȽϹ��ĵ�
            }
    }
}

void output(int i,int j)
{
    int a,b,c,d;
    a=j;     //Ŀ�ĵ�Ϊa
    if(a!=i)    // �������ͬһ���ص�
    {
        printf("��%s��%s�����·����:",G.vex[i].name,G.vex[j].name);
        printf("%s",G.vex[i].name) ;
        d=i;      //�������
        for(c=0; c<NUM; ++c)
        {
gate:
            P[a][i]=0;
            for(b=0; b<NUM; b++)
            {
                if(G.arcs[d][b].adj<99999&&P[a][b])  //�жϳ��̵ֶ�·��
                {
                    printf("-->%s",G.vex[b].name);  //����ڵ����
                    P[a][b]=0;
                    d=b;     // ��b��Ϊ������,������һ�����
                    goto gate;
                }
            }
        }
        printf("\n��̾���Ϊ %dm\n",D[a]);
    }
    else
        printf("������յ���ͬ��������\n");
}
