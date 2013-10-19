#include <stdio.h>
#define Max 99999
#define NUM 10
#include<windows.h>

//两景点相邻边
typedef struct Way
{
    int adj;  //边的长度
} Way;

//定点类型
typedef struct VertexType
{
    int number;  //位置编号
    char name[50];  // 位置名称
    char inf[50]; //相关描述
} VertexType;

//图的类型
typedef struct
{
    VertexType vex[NUM]; //顶点号
    Way arcs[NUM][NUM]; /* 图中的边，即为景点间的距离 */
    int v_num,e_num;
} Map;

Map G;   //图

int P[NUM][NUM];  //路径存在判断
long int D[NUM]; //最短路径长度

void Create_school(int v,int a); //造图函数
void Print_Inf();
void ShortestPath(int num); //最短路径
void output(int sight1,int sight2);

int main()
{
    char a;
    int i,j;
    Create_school(NUM,11);

    while(1)
    {
        Print_Inf();//信息
        printf("请选择：\n1.查询景点路径\n");
        printf("2.退出\n");
        fflush(stdin);
        a=getchar();
        switch(a)
        {
        case '1' :
            printf("请选择起点地点的代号（0～9）：");
            fflush(stdin);
            while(scanf("%d",&i))
            {
                if(i>=0 && i<=9)
                    break;
                else
                {
                    printf("请输入0--9内的相应代号数字！\n");
                    printf("请选择起点地点的代号（0～9）：");
                    fflush(stdin);
                }
            }
            printf("请选择终点景点的代号（0～9）：");
            fflush(stdin);
            while(scanf("%d",&j))
            {
                if(j>=0 && j<=9)
                    break;
                else
                {
                    printf("请输入0--9内的相应代号数字！\n");
                    printf("请选择终点地点的代号（0～9）：");
                    fflush(stdin);
                }
            }
            ShortestPath(i); //最短路径
            output(i,j);     //输出
            printf("\n\n请按任意键开始下次导航...\n");
            system("pause");
            break;
        case '2' :
            system("cls");
            printf("/~~拜拜( ^_^ )/~~拜拜( ^_^ )/~~拜拜( ^_^ )/~~拜拜\n");
            system("PAUSE");
            return 0;
            break;
        default:
            system("cls");
            printf("\n输入错误请重新选择：\n");
        }
    }
    return 0;
}

void Create_school(int v,int a)
{
    char name[10];
    char inf[10];
    char szPath[256],*pSz;
    GetModuleFileName(NULL,szPath,256);//读取当前配置文件路径
    pSz=strrchr(szPath,'\\');
    if(pSz != NULL)
    {
        *pSz = '\0';
        strcat(szPath, "\\school_inf.ini");//配置文件
    }

    int i,j;
    G.v_num=v; //顶点，边
    G.e_num=a;
    for(i=0; i<G.v_num; ++i)//设定定点标号和相关信息
    {
        sprintf(name,"%s%d","name",i);
        sprintf(inf,"%s%d","inf",i);
        G.vex[i].number=i;
        GetPrivateProfileString("INF",name,NULL,G.vex[i].name,50,szPath);//读取位置名称
        GetPrivateProfileString("INF",inf,NULL,G.vex[i].inf,50,szPath);//读取位置信息
    }
    //把所有的边假定为最长，为两个景点之间是不可到达
    for(i=0; i<G.v_num; ++i)
        for(j=0; j<G.v_num; ++j)
            G.arcs[i][j].adj=Max;
    //设置联通路径
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
    printf("\n*********************北京信息科技大学健翔桥校区导航系统*************************\n");
    for(i=0; i<NUM; i++)
    {
        printf("代号：%d   名称： %-10s",i,G.vex[i].name);
        printf("\t信息描述：%-25s\n",G.vex[i].inf);
        k=k+1;
    }
    printf("\n********************************************************************************");
}

void ShortestPath(int num) // 迪杰斯特拉算法最短路径
{
    int v,w,i,t;  //i、w和v为计数变量
    int final[NUM];
    int min;
    for(v=0; v<NUM; v++)
    {
        final[v]=0;  //点集合标记初始0
        D[v]=G.arcs[num][v].adj;//存入相关权值-》1
        for(w=0; w<NUM; w++) // 初始路径为空
            P[v][w]=0;
        if(D[v]<99999)  //判断路径存在
        {
            P[v][num]=1; //存在为1
            P[v][v]=1;
        }
    }

    D[num]=0; //自己到自己权值0
    final[num]=1;      //设顶点属于S集合
    // 开始主循环，每一次求得num到某个顶点的最短路径，并将其加入到S集合
    for(i=0; i<NUM; ++i)
    {
        min=Max;     //设当前所知离顶点num的最近距离
        for(w=0; w<NUM; ++w)
            if(!final[w])  //没比较过得
                if(D[w]<min)   //当W点离顶点num点更近
                {
                    v=w;//记录该点，以便下次从该点比较
                    min=D[w];
                }
        final[v]=1;   //离num点更近的v（即上面w）加入到s集合
        for(w=0; w<NUM; ++w) // 更新当前最短路径极其距离
            if(!final[w]&&((min+G.arcs[v][w].adj)<D[w]))// 不在s集合，相对较短距离+此点到所有点最短距离点的长度比num点到w点距离短
            {
                D[w]=min+G.arcs[v][w].adj;//更新最短距离（权值）
                for(t=0; t<NUM; t++)
                    P[w][t]=P[v][t];//更新路径
                P[w][w]=1;//设为已经比较过的点
            }
    }
}

void output(int i,int j)
{
    int a,b,c,d;
    a=j;     //目的地为a
    if(a!=i)    // 如果不是同一个地点
    {
        printf("从%s到%s的最短路径是:",G.vex[i].name,G.vex[j].name);
        printf("%s",G.vex[i].name) ;
        d=i;      //定义起点
        for(c=0; c<NUM; ++c)
        {
gate:
            P[a][i]=0;
            for(b=0; b<NUM; b++)
            {
                if(G.arcs[d][b].adj<99999&&P[a][b])  //判断出现短的路径
                {
                    printf("-->%s",G.vex[b].name);  //输出节点的名
                    P[a][b]=0;
                    d=b;     // 将b作为出发点,进行下一次输出
                    goto gate;
                }
            }
        }
        printf("\n最短距离为 %dm\n",D[a]);
    }
    else
        printf("起点与终点相同！！！！\n");
}
