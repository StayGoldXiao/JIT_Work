/*
InitList(LinkList &L) 初始化
ListLength(LinkList L) 获得单链表长度
ListInsert(LinkList &L,int i,ElemType e)位置i后插 时间复杂度O(n)
ListDelete(LinkList &L,int i) 删除位置i元素
LocateElem(LinkList L,ElemType e) 查找第一个等于e的元素，返回指针
*/
#include<stdio.h>
#include<stdlib.h>

#define ElemType int

typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;


int InitList(LinkList& L) {
	L = (LNode*)malloc(sizeof(LNode));
	// 初始化新节点的next指针为NULL  
	L->next = NULL;
	return 1; // 如果成功，返回1表示成功  
}

//获取单链表长度
int ListLength(LinkList L)
{
	LinkList p = L; int sum = 0;
	while (p)
	{
		sum++;
		p = p->next;
	}
	return sum - 1;//去除头结点
}

//插入函数--后插法 插入到第i(1<=i<=length+1)个位置 即i-1之后 不必区分i的位置
bool ListInsert(LinkList& L, int i, ElemType e)
{
	LNode* s; LinkList p = L; int j = 0;
	while (p && (j < i - 1))//j指到i-1位置或者p已经到最后时跳出
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)//i<1或者i>ListLength(L)+1时,插入位置无效 不调用ListLength,提高效率
	{
		printf("插入位置无效！！！\n");
		return false;
	}
	s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

/*
//删除函数 删除位置i的结点 即删除i-1之后的结点
bool ListDelete(LinkList& L, int i)
{
	LNode* s; LinkList p = L; int j = 0;
	LinkList q;
	while (p && (j < i - 1))//j指到i-1位置
	{
		p = p->next;
		++j;
	}
	if (p == nullptr || !(p->next) || j > i - 1)//i<1或者i>ListLength(L)时,删除位置无效
	{
		printf("删除位置无效！！！\n");
		return false;
	}
	q = p->next;
	p->next = q->next;
	free(q);//释放空间
	return true;
}*/

//查找函数 按值查找 查找第一个等于e的结点 成功返回该结点指针，否则返回NULL
LNode* LocateElem(LinkList L, ElemType e)
{
	LNode* p = L;
	while (p && (p->data != e))
	{
		p = p->next;
	}
	return p;
}


//遍历输出函数
void PrintList(LinkList L)
{
	//LinkList p = L->next;//跳过头结点
	LinkList p = L;//无头结点
	if (ListLength(L))
	{
		printf("当前单链表所有元素:");
		while (p)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
	}
	else
	{
		printf("当前单链表已空！\n");
	}
}

//原地逆置函数
void reverseList(LinkList& L) {
	if (!L || !L->next) {
		return; // 空链表或只有一个节点的链表无需逆置  
	}
	LNode* prev = NULL;
	LNode* curr = L->next;
	while (curr) {
		LNode* nextNode = curr->next;
		curr->next = prev;
		prev = curr;
		curr = nextNode;
	}
	L->next = prev;
}


/*p始终指向原链表的第一个结点，
q结点始终指向p结点的后继结点结点，
且同时为当轮循环的将要被放到最前面的结点
循环开始后，将p结点指向后方的第二个结点即q结点的后继结点
*/
void reverse(LinkList& L)
{
	if (!L || !L->next)
		return; // 空链表或只有一个节点的链表无需逆置  
	LNode* p = L->next;
	LNode* q = L->next->next;
	while (q != NULL)
	{
		p->next = q->next;
		q->next = L->next;
		L->next = q;
		q = p->next;
	}
	p = NULL;
}

//从表LA中删除自第i个元素起共len个元素后，将它们插入到表LB中第j个元素之前。
void D_Connect(LinkList& LA, LinkList& LB, int i, int len, int j) {
	LNode* p, * q, * tail;
	p = LA;
	for (int a = 1; a < i - 1; a++)//指向第i-1个元素
		p = p->next;
	for (int a = 0; a < len; a++)
		p->next = p->next->next;
	tail = LA;
	while (tail->next != NULL) {//指向LA尾结点
		tail = tail->next;
	}

	p = LB;
	for (int a = 1; a < j - 1; a++)//指向第j-1个元素
		p = p->next;
	q = p->next;//指向第j个元素

	p->next = LA;
	tail->next = q;
}

/*
int main()
{
	LinkList L;
	InitList(L);
	LNode* p = (LNode*)malloc(sizeof(LNode));
	p = L;
	for (int i = 0; i < 10; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		p->next = q;
		printf("请为第%d个元素赋值:", i + 1);
		scanf("%d", &q->data);
		q->next = NULL;
		p = q;
	}
	PrintList(L);
	return 0;
}*/


/*
int main() {
	LinkList L;
	InitList(L);
	LNode* p = L;
	printf("请先建立一个长度为10的非递减排序链表：\n");
	for (int i = 0; i < 10; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		p->next = q;
		printf("请为第%d个元素赋值:", i + 1);
		scanf("%d", &q->data);
		q->next = NULL;
		p = q;
	}
	PrintList(L);
	reverse(L);
	PrintList(L);
	return 0;
}*/


/*
int main() {
	LinkList LA, LB;//先创建两个无头结点单链表
	LA = (LNode*)malloc(sizeof(LNode));
	LB = (LNode*)malloc(sizeof(LNode));
	LA->next = NULL;
	LB->next = NULL;
	LNode* p = LA;
	printf("请先建立一个长度为10的非递减排序链表：\n");
	scanf("%d", &p->data);
	p->next = NULL;
	for (int i = 0; i < 9; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		//printf("请为第%d个元素赋值:", i + 1);
		scanf("%d", &q->data);
		p->next = q;
		q->next = NULL;
		p = q;
	}
	printf("LA链表");
	PrintList(LA);
	p = LB;
	printf("请先建立一个长度为10的非递减排序链表：\n");
	scanf("%d", &p->data);
	p->next = NULL;
	for (int i = 0; i < 9; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		//printf("请为第%d个元素赋值:", i + 1);
		scanf("%d", &q->data);
		p->next = q;
		q->next = NULL;
		p = q;
	}
	printf("LB链表");
	PrintList(LB);

	D_Connect(LA, LB, 3, 5, 7);
	printf("\n从表LA中删除自第3个元素起共5个元素后，将它们插入到表LB中第7个元素之前后\n");
	PrintList(LB);
	return 0;
}*/
