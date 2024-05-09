/*
	InitTree(BiTree &T) 初始化二叉树，先序递归创建
	PreOrder(BiTree T)  先序遍历
	InOrder(BiTree T)   中序遍历
	PostOrder(BiTree T) 后序遍历
	CreateBiTree(BiTree &T) 调用InitTree，创建二叉树
*/

#include<stdio.h>
#include<stdlib.h>

#define TElemType int


//链式二叉树数据结构
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;


/*创建二叉树
规定数据域为-1，则为空,先序创建
当结点是叶子结点时，需将左右子树data域置为-1
例如：1 2 3 -1 -1 4 -1 -1 5 -1 -1
表示树   1  
        / \
       2   5
      / \
     3   4     
*/
int InitTree(BiTree& T)
{
	TElemType a;
	scanf("%d", &a);
	if (-1 == a) T = NULL;
	else {
		T = (BiTree)malloc(sizeof(BiTNode));
		T->data = a;
		InitTree(T->lchild);
		InitTree(T->rchild);
	}
	return 0;
}

//先序遍历
void PreOrder(BiTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

//中序遍历
void InOrder(BiTree T)
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		printf("%d ", T->data);
		InOrder(T->rchild);
	}
}

//后序遍历
void PostOrder(BiTree T)
{
	if (T != NULL)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%d ", T->data);
	}
}

// 计算叶节点数  
int countLeafNodes(BiTree T) {
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	return countLeafNodes(T->lchild) + countLeafNodes(T->rchild);
}

// 计算节点总数  
int countTotalNodes(BiTree T) {
	if (T == NULL) return 0;
	return 1 + countTotalNodes(T->lchild) + countTotalNodes(T->rchild);
}

// 计算树深度  
int calculateDepth(BiTree T) {
	if (T == NULL) return 0;
	int leftDepth = calculateDepth(T->lchild);
	int rightDepth = calculateDepth(T->rchild);
	return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

//顺序表数据结构
typedef struct {
	TElemType* elem;  //存储结点的值
	TElemType last;   // 记录数组中最后一个元素的索引  
} SeqList;

// 从顺序表建立二叉树的递归函数
void CreateBinaryTree(SeqList sa, BiTree& T, int i) {
	if (i <= sa.last) {
		if (sa.elem[i] != -1) {
			T = (BiTree)malloc(sizeof(BiTNode));
			T->data = sa.elem[i];
			CreateBinaryTree(sa, T->lchild, 2 * i);
			CreateBinaryTree(sa, T->rchild, 2 * i + 1);
		}
		else {
			T = NULL;
		}
	}
	else {
		T = NULL;
	}
}

/*
int main()
{
	BiTree T = NULL;
	printf("请按照先序遍历输入二叉树(输入-1表示为空,叶子结点左右子树置-1):\n");
	InitTree(T);
	printf("该二叉树的先序遍历为：");
	PreOrder(T);
	printf("\n该二叉树的中序遍历为：");
	InOrder(T);
	printf("\n该二叉树的后序遍历为：");
	PostOrder(T);

	printf("\n二叉树中叶结点的个数为：%d \n", countLeafNodes(T));
	printf("二叉树中结点总数为: %d\n", countTotalNodes(T));
	printf("二叉树的深度为: %d\n", calculateDepth(T));
	return 0;
}*/

/*[1,2,3,-1,-1,4,-1,-1,5,6,-1,-1,7,-1,-1]
         1
	   /   \
	  2     5
	 / \   / \
	3   4 6   7
*/

/*
int main() {
	SeqList sa;
	sa.elem = (int*)malloc(100 * sizeof(int)); // 假设顺序表的大小不超过100
	printf("请输入完全二叉树的结点值（以-1表示空结点），以空格分隔，以0结束输入：\n");
	int num, i = 1;
	while (scanf("%d", &num) && num != 0) {
		sa.elem[i++] = num;
	}
	sa.last = i - 1;

	BiTree T;
	CreateBinaryTree(sa, T, 1); // 从索引1开始构建二叉树

	printf("该二叉树的先序遍历为：");
	PreOrder(T);
	printf("\n该二叉树的中序遍历为：");
	InOrder(T);
	printf("\n该二叉树的后序遍历为：");
	PostOrder(T);
	printf("\n");

	free(sa.elem); // 释放动态分配的内存

	return 0;
}*/