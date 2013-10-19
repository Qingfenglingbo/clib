#include<stdio.h>
#include<malloc.H>
#define LH 1  //左高
#define EH 0 //等高
#define RH -1 //右高
#define EQ(a,b) ((a)==(b)) //a==b
#define LT(a,b) ((a)<(b))//a<b

enum Boolean {FALSE,TRUE};

typedef struct BSTNode
{
    int data;
    int bf;//结点的平衡因子
    struct BSTNode *lchild,*rchild;//左、右孩子指针
} BSTNode,*BSTree;


//右旋处理，处理之后P指向新的树根结点，放置处理之前的左子树的根结点
void R_Rotate(BSTree &p)
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

//左旋处理
void L_Rotate(BSTree &p)
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

//对心指针T所指结点为根的二叉树作左平衡旋转处理，算法结束时，指针T指向新的根结点
void LeftBalance(BSTree &T)
{
    BSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf)  //检查*T的左子树的平衡度，并作相应平衡处理
    {
    case LH:  //新结点插入在*T的左孩子的左子树上，要作单右旋处理
        T->bf=lc->bf=EH;
        R_Rotate(T);
        break;
    case RH:  //新结点插入在*T的左孩子的右子树上，要作双旋处理
        rd=lc->rchild; //rd指向*T的左孩子的右子树根
        switch(rd->bf)   //修改*T4及其左孩子的平衡因子
        {
        case LH:
            T->bf=RH;
            lc->bf=EH;
            break;
        case EH:
            T->bf=lc->bf=EH;
            break;
        case RH:
            T->bf=EH;
            lc->bf=LH;
            break;
        }
        rd->bf=EH;
        L_Rotate(T->lchild);  //对*T的左子树作左旋平衡处理
        R_Rotate(T);   //对*T作右旋平衡处理
    }
}

void RightBalance(BSTree &T)
{
//对心指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时，指针T指向新的根结点
    BSTree rc,ld;
    rc=T->rchild;  //rc指向*T的右子树根结点
    switch(rc->bf)  //检查*T的右子树的平衡度，并作相应平衡处理
    {
    case RH:  //新结点插入在*T的右孩子的右子树上，要作单左旋处理
        T->bf=rc->bf=EH;
        L_Rotate(T);
        break;
    case LH:  //新结点插入在*T的右孩子的左子树上，要作双旋处理
        ld=rc->lchild; //ld指向*T的右孩子的左子树根
        switch(ld->bf)   //修改*T及其右孩子的平衡因子
        {
        case LH:
            T->bf=EH;
            rc->bf=LH;
            break;
        case EH:
            T->bf=rc->bf=EH;
            break;
        case RH:
            T->bf=RH;
            rc->bf=EH;
            break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);  //对*T的右子树作右旋平衡处理
        L_Rotate(T);   //对*T作左旋平衡处理
    }
}

//插入新结点
int InsertAVL(BSTree &T,int e,enum Boolean &taller)
{
    if(!T)
    {
        //根节点，树“长高”，置taller为TRUE
        T=(BSTree)malloc(sizeof(BSTNode));
        T->data=e;
        T->lchild=T->rchild=NULL;
        T->bf=EH;
        taller=TRUE;
    }
    else
    {
        if(EQ(e,T->data))  //树中已存在和e有相同关键字的点则不再插入
        {
            taller=FALSE;
            printf("此数已存在树中，请输入其他数字：\n");
            return 0;
        }
        if(LT(e,T->data))    //继续在*T的左子树中进行搜索e<t->data
        {
            if(!InsertAVL(T->lchild,e,taller))
                return 0;  //未插入
            if(taller)    //已插入到*T的左子树中且左子树“长高”
                switch(T->bf)   //检查*T的平衡度
                {
                case LH:  //原本左子树比右子树高，需要作左平衡处理
                    LeftBalance(T);
                    taller=FALSE;
                    break;
                case EH:  //原本左、右子树等高，现因左子树增高而使树增高
                    T->bf=LH;
                    taller=TRUE;
                    break;
                case RH:  //原本右子树比左子树高，现因左、右子树等高
                    T->bf=EH;
                    taller=FALSE;
                    break;
                }
        }
        else       //继续在*T的右子树中进行搜索
        {
            if(!InsertAVL(T->rchild,e,taller))
                return 0;//未插入
            if(taller)  //已插入到*T的右子树且右子树长高
                switch(T->bf) //检查*T的平衡度
                {
                case LH://原本左子树比右子树高，现左、右子树等高
                    T->bf=EH;
                    taller=FALSE;
                    break;
                case EH://原本左、右子树等高，现因右子树增高而使树增高
                    T->bf=RH;
                    taller=TRUE;
                    break;
                case RH:   //原本右子树比左子树高，需要作右平衡处理
                    RightBalance(T);
                    taller=FALSE;
                    break;
                }//switch(T->bf)
        }
    }
    return 1;
}


//删除平衡二叉树的元素，并做平衡处理
int DeleteAVL(BSTree &T,int e,enum Boolean &taller)
{

    if(!T)
        return 0;
    else
    {
        if(EQ(e,T->data))  //找到和e相等的结点
        {
            if(!T->lchild&&!T->rchild)
            {
                taller=FALSE;    //该结点为叶子结点
                free(T);
                T=NULL;
                return 1;
            }
            else if(T->lchild)  //该结点有左子树
            {
                if(!T->lchild->rchild)  //在左子树中寻找最大值来替代T
                {
                    T->data=T->lchild->data;
                    T->lchild->data=e;
                    DeleteAVL(T->lchild,e,taller);
                }
                else
                {
                    T->data=T->lchild->rchild->data;
                    T->lchild->rchild->data=e;
                    DeleteAVL(T->lchild->rchild,e,taller);
                }
                if(!taller)  //已从左子树删除且左子树变矮
                    switch(T->bf) //检查*T的平衡度
                    {
                    case LH://原本左子树比右子树高，现左、右子树等高
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    case EH://原本左、右子树等高，现因左子树变矮而使树增高
                        T->bf=RH;
                        taller=TRUE;
                        break;
                    case RH:   //原本右子树比左子树高，需要作右平衡处理
                        RightBalance(T);
                        taller=FALSE;
                        break;
                    }
            }
            else if(T->rchild)  //该结点有右子树
            {
                if(!T->rchild->lchild)  //在右子树中寻找最小值来替代T
                {
                    T->data=T->rchild->data;
                    T->rchild->data=e;
                    DeleteAVL(T->rchild,e,taller);
                }
                else
                {
                    T->rchild->data=T->rchild->lchild->data;
                    T->rchild->lchild->data=e;
                    DeleteAVL(T->rchild->lchild,e,taller);
                }
                if(!taller)    //已从右子树删除且右子树变矮
                    switch(T->bf)   //检查*T的平衡度
                    {
                    case LH:  //原本左子树比右子树高，需要作左平衡处理
                        LeftBalance(T);
                        taller=FALSE;
                        break;
                    case EH:  //原本左、右子树等高，现因右子树变矮而使树增高
                        T->bf=LH;
                        taller=TRUE;
                        break;
                    case RH:  //原本右子树比左子树高，现左、右子树等高
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    }
            }
        }
        if(LT(e,T->data))    //继续在*T的左子树中进行搜索
        {
            if(!DeleteAVL(T->lchild,e,taller))
                return 0;  //未删除
        }
        else       //继续在*T的右子树中进行搜索
        {
            if(!DeleteAVL(T->rchild,e,taller))
                return 0;//未删除
        }
    }
    return 1;
}

//按树状打印输出二叉树
void Print_BSTree(BSTree T,int i)
{
    int j;
    if(T->rchild)
        Print_BSTree(T->rchild,i+1);
    for(j=1; j<=i; j++)
        printf("     "); //打印i个空格以表示出层次
    printf("%5d\n",T->data); //打印T元素,换行
    if(T->lchild)
        Print_BSTree(T->lchild,i+1);
}

//销毁平衡二叉树
void Destroy_BSTree(BSTree &T)
{
    BSTree p;
    p=T;
    while(p->lchild&&p->rchild)
    {
        Destroy_BSTree(p->lchild);
        Destroy_BSTree(p->rchild);
    }
    if(!p->lchild&&p->rchild)
        Destroy_BSTree(p->rchild);
    if(!p->rchild&&p->lchild)
        Destroy_BSTree(p->lchild);
    if(!p->lchild&&!p->rchild)
        free(p);
    T=NULL;
}

int main()
{
    char x;
    int e,i=0;
    enum Boolean taller;
    BSTree T=NULL;
    while(1)
    {
        printf("-----------------------------------------------------------------\n");
        printf("                      平衡二叉树 \n\n");
        printf("                     1.创建二叉树\n");
        printf("                     2.插入结点  \n");
        printf("                     3.删除结点  \n");
        printf("                     4.删除树    \n");
        printf("                     5.退出      \n");
        printf("-----------------------------------------------------------------\n");
        printf(" 请选择:");
        x=getchar();
        if(x=='1')
        {
            e=0;
            printf("创建树(当输入为-1时，二叉树创建结束):\n");
            while(e!=-1)
            {
                scanf("%d",&e);
                if(e!=-1)
                {
                    taller=FALSE;
                    InsertAVL(T,e,taller);//插入树内
                }
            }
            printf("二叉树为:\n");
            Print_BSTree(T,0);
        }
        else if(x=='2')
        {
            e=0;
            while(e!=-1)
            {
                printf("插入整数:");
                scanf("%d",&e);
                if(e!=-1)
                {
                    taller=FALSE;
                    InsertAVL(T,e,taller);
                    Print_BSTree(T,i);
                }
            }
        }
        else if(x=='3')
        {
            if(T==NULL)
                printf("空树!\n");
            else
            {
                e=0;
                while(e!=-1)
                {
                    printf("请输入一个整数:");
                    scanf("%d",&e);
                    if(e!=-1)
                    {
                        taller=TRUE;
                        DeleteAVL(T,e,taller);
                        if(T==NULL)
                            printf("空树!\n");
                        else
                            Print_BSTree(T,i);
                    }
                }
            }
        }
        else if(x=='4')
        {
            Destroy_BSTree(T);
            printf("树已清空!\n");
        }
        else if(x=='5')
            break;
        else
            printf("Error!\n");
        getchar();
    }
}
