/*
	InitTree(BiTree &T) ��ʼ��������������ݹ鴴��
	PreOrder(BiTree T)  �������
	InOrder(BiTree T)   �������
	PostOrder(BiTree T) �������
	CreateBiTree(BiTree &T) ����InitTree������������
*/

#include<stdio.h>
#include<stdlib.h>

#define TElemType int


//��ʽ���������ݽṹ
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;


/*����������
�涨������Ϊ-1����Ϊ��,���򴴽�
�������Ҷ�ӽ��ʱ���轫��������data����Ϊ-1
���磺1 2 3 -1 -1 4 -1 -1 5 -1 -1
��ʾ��   1  
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

//�������
void PreOrder(BiTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

//�������
void InOrder(BiTree T)
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		printf("%d ", T->data);
		InOrder(T->rchild);
	}
}

//�������
void PostOrder(BiTree T)
{
	if (T != NULL)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%d ", T->data);
	}
}

// ����Ҷ�ڵ���  
int countLeafNodes(BiTree T) {
	if (T == NULL) return 0;
	if (T->lchild == NULL && T->rchild == NULL) return 1;
	return countLeafNodes(T->lchild) + countLeafNodes(T->rchild);
}

// ����ڵ�����  
int countTotalNodes(BiTree T) {
	if (T == NULL) return 0;
	return 1 + countTotalNodes(T->lchild) + countTotalNodes(T->rchild);
}

// ���������  
int calculateDepth(BiTree T) {
	if (T == NULL) return 0;
	int leftDepth = calculateDepth(T->lchild);
	int rightDepth = calculateDepth(T->rchild);
	return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

//˳������ݽṹ
typedef struct {
	TElemType* elem;  //�洢����ֵ
	TElemType last;   // ��¼���������һ��Ԫ�ص�����  
} SeqList;

// ��˳������������ĵݹ麯��
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
	printf("�밴������������������(����-1��ʾΪ��,Ҷ�ӽ������������-1):\n");
	InitTree(T);
	printf("�ö��������������Ϊ��");
	PreOrder(T);
	printf("\n�ö��������������Ϊ��");
	InOrder(T);
	printf("\n�ö������ĺ������Ϊ��");
	PostOrder(T);

	printf("\n��������Ҷ���ĸ���Ϊ��%d \n", countLeafNodes(T));
	printf("�������н������Ϊ: %d\n", countTotalNodes(T));
	printf("�����������Ϊ: %d\n", calculateDepth(T));
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
	sa.elem = (int*)malloc(100 * sizeof(int)); // ����˳���Ĵ�С������100
	printf("��������ȫ�������Ľ��ֵ����-1��ʾ�ս�㣩���Կո�ָ�����0�������룺\n");
	int num, i = 1;
	while (scanf("%d", &num) && num != 0) {
		sa.elem[i++] = num;
	}
	sa.last = i - 1;

	BiTree T;
	CreateBinaryTree(sa, T, 1); // ������1��ʼ����������

	printf("�ö��������������Ϊ��");
	PreOrder(T);
	printf("\n�ö��������������Ϊ��");
	InOrder(T);
	printf("\n�ö������ĺ������Ϊ��");
	PostOrder(T);
	printf("\n");

	free(sa.elem); // �ͷŶ�̬������ڴ�

	return 0;
}*/