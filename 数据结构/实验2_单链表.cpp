/*
InitList(LinkList &L) ��ʼ��
ListLength(LinkList L) ��õ�������
ListInsert(LinkList &L,int i,ElemType e)λ��i��� ʱ�临�Ӷ�O(n)
ListDelete(LinkList &L,int i) ɾ��λ��iԪ��
LocateElem(LinkList L,ElemType e) ���ҵ�һ������e��Ԫ�أ�����ָ��
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
	// ��ʼ���½ڵ��nextָ��ΪNULL  
	L->next = NULL;
	return 1; // ����ɹ�������1��ʾ�ɹ�  
}

//��ȡ��������
int ListLength(LinkList L)
{
	LinkList p = L; int sum = 0;
	while (p)
	{
		sum++;
		p = p->next;
	}
	return sum - 1;//ȥ��ͷ���
}

//���뺯��--��巨 ���뵽��i(1<=i<=length+1)��λ�� ��i-1֮�� ��������i��λ��
bool ListInsert(LinkList& L, int i, ElemType e)
{
	LNode* s; LinkList p = L; int j = 0;
	while (p && (j < i - 1))//jָ��i-1λ�û���p�Ѿ������ʱ����
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)//i<1����i>ListLength(L)+1ʱ,����λ����Ч ������ListLength,���Ч��
	{
		printf("����λ����Ч������\n");
		return false;
	}
	s = new LNode;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

/*
//ɾ������ ɾ��λ��i�Ľ�� ��ɾ��i-1֮��Ľ��
bool ListDelete(LinkList& L, int i)
{
	LNode* s; LinkList p = L; int j = 0;
	LinkList q;
	while (p && (j < i - 1))//jָ��i-1λ��
	{
		p = p->next;
		++j;
	}
	if (p == nullptr || !(p->next) || j > i - 1)//i<1����i>ListLength(L)ʱ,ɾ��λ����Ч
	{
		printf("ɾ��λ����Ч������\n");
		return false;
	}
	q = p->next;
	p->next = q->next;
	free(q);//�ͷſռ�
	return true;
}*/

//���Һ��� ��ֵ���� ���ҵ�һ������e�Ľ�� �ɹ����ظý��ָ�룬���򷵻�NULL
LNode* LocateElem(LinkList L, ElemType e)
{
	LNode* p = L;
	while (p && (p->data != e))
	{
		p = p->next;
	}
	return p;
}


//�����������
void PrintList(LinkList L)
{
	//LinkList p = L->next;//����ͷ���
	LinkList p = L;//��ͷ���
	if (ListLength(L))
	{
		printf("��ǰ����������Ԫ��:");
		while (p)
		{
			printf("%d ", p->data);
			p = p->next;
		}
		printf("\n");
	}
	else
	{
		printf("��ǰ�������ѿգ�\n");
	}
}

//ԭ�����ú���
void reverseList(LinkList& L) {
	if (!L || !L->next) {
		return; // �������ֻ��һ���ڵ��������������  
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


/*pʼ��ָ��ԭ����ĵ�һ����㣬
q���ʼ��ָ��p���ĺ�̽���㣬
��ͬʱΪ����ѭ���Ľ�Ҫ���ŵ���ǰ��Ľ��
ѭ����ʼ�󣬽�p���ָ��󷽵ĵڶ�����㼴q���ĺ�̽��
*/
void reverse(LinkList& L)
{
	if (!L || !L->next)
		return; // �������ֻ��һ���ڵ��������������  
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

//�ӱ�LA��ɾ���Ե�i��Ԫ����len��Ԫ�غ󣬽����ǲ��뵽��LB�е�j��Ԫ��֮ǰ��
void D_Connect(LinkList& LA, LinkList& LB, int i, int len, int j) {
	LNode* p, * q, * tail;
	p = LA;
	for (int a = 1; a < i - 1; a++)//ָ���i-1��Ԫ��
		p = p->next;
	for (int a = 0; a < len; a++)
		p->next = p->next->next;
	tail = LA;
	while (tail->next != NULL) {//ָ��LAβ���
		tail = tail->next;
	}

	p = LB;
	for (int a = 1; a < j - 1; a++)//ָ���j-1��Ԫ��
		p = p->next;
	q = p->next;//ָ���j��Ԫ��

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
		printf("��Ϊ��%d��Ԫ�ظ�ֵ:", i + 1);
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
	printf("���Ƚ���һ������Ϊ10�ķǵݼ���������\n");
	for (int i = 0; i < 10; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		p->next = q;
		printf("��Ϊ��%d��Ԫ�ظ�ֵ:", i + 1);
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
	LinkList LA, LB;//�ȴ���������ͷ��㵥����
	LA = (LNode*)malloc(sizeof(LNode));
	LB = (LNode*)malloc(sizeof(LNode));
	LA->next = NULL;
	LB->next = NULL;
	LNode* p = LA;
	printf("���Ƚ���һ������Ϊ10�ķǵݼ���������\n");
	scanf("%d", &p->data);
	p->next = NULL;
	for (int i = 0; i < 9; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		//printf("��Ϊ��%d��Ԫ�ظ�ֵ:", i + 1);
		scanf("%d", &q->data);
		p->next = q;
		q->next = NULL;
		p = q;
	}
	printf("LA����");
	PrintList(LA);
	p = LB;
	printf("���Ƚ���һ������Ϊ10�ķǵݼ���������\n");
	scanf("%d", &p->data);
	p->next = NULL;
	for (int i = 0; i < 9; i++) {
		LNode* q = (LNode*)malloc(sizeof(LNode));
		//printf("��Ϊ��%d��Ԫ�ظ�ֵ:", i + 1);
		scanf("%d", &q->data);
		p->next = q;
		q->next = NULL;
		p = q;
	}
	printf("LB����");
	PrintList(LB);

	D_Connect(LA, LB, 3, 5, 7);
	printf("\n�ӱ�LA��ɾ���Ե�3��Ԫ����5��Ԫ�غ󣬽����ǲ��뵽��LB�е�7��Ԫ��֮ǰ��\n");
	PrintList(LB);
	return 0;
}*/
