#include <stdio.h>
#include<stdlib.h>

//Ԥ���峣��������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;


typedef struct {
	ElemType* elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList& L) {
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem)exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

int CreatList_Sq(SqList& L, int n) {
	InitList_Sq(L);
	printf("�������� %d �����뽫��ֵ��˳���:", n);
	if (n >= L.listsize) {
		int* newbase = (ElemType*)realloc(L.elem, (n) * sizeof(ElemType));
		if (!newbase) return 0;
		L.elem = newbase;//�»�ַ
		L.listsize = n;//���Ӵ�������
	}
	int* q;
	q = L.elem;               //qΪ��ʼλ��
	//������������Ԫ��
	for (int i = 1; i <= n; i++) {//������������Ԫ��
		int e;
		scanf("%d", &e);
		printf("�����Ԫ�أ�%d �ɹ�\n", e);
		*q = e;
		q++;
		L.length++;
	}
}

int ListInsert_Sq(SqList& L, int i, ElemType e) {
	if (i<1 || i>L.length + 1) return 0;//����Ԫ�ز��Ϸ�
	if (L.length >= L.listsize) {
		int* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) printf("�»�ַ����ʧ��"); return 0;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	int* q;
	int* p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; p--) {
		*(p + 1) = *p;
	}
	*q = e;//����e
	L.length++;
	printf("����Ԫ�أ�%d �ɹ�\n", e);
	return 1;
}


int GetElem(SqList& L, int i, ElemType e) {
	if (i<1 || i>L.length) printf("�����ֵ���Ϸ���"); return 0;

	int* p;
	p = L.elem;
	while (i <= L.length && *p != e) {
		i++;
		*p++;
	}
	if (i <= L.length) {
		printf("����Ϊ��%d\n", i);
		return 0;
	}
	else {
		printf("���Ա�L�в��޴�ֵ");
		return -1;
	}
}

int MergeList_Sq(SqList La, SqList Lb, SqList& Lc) {
	int* pa, * pb, * pc;
	pa = La.elem; pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = (ElemType*)malloc(Lc.listsize * sizeof(ElemType));
	if (!Lc.elem) exit(OVERFLOW);
	int* pa_last, * pb_last;
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while (pa < pa_last && pb < pb_last) {
		if (*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
		//=�����ȼ�����++
	}
	while (pa < pa_last) *pc++ = *pa++;//����La��ʣ��Ԫ��
	while (pb < pb_last) *pc++ = *pb++;//����Lb��ʣ��Ԫ��
}


bool ListEmpty_Sq(SqList L) {
	if (L.length = 0) return true;
	else return false;
	return 0;
}

int ListLength_Sq(SqList& L) {
	//ʹ��L.length����
	return L.length;
}



void PrintList(SqList L)
{
	printf("��ǰ˳�������Ԫ��:");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d ", L.elem[i]);
	}
	printf("\n");
}


//��ֵ���Һ��������ҵ�һ��ֵ����e��Ԫ�� ������λ�ã���������ڣ����أ�1
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.length; i++)//�ӵ�λ�ò���
	{
		if (L.elem[i] == e)
			return i + 1;
	}
	return -1;
}

void InsertAscend(SqList& L, ElemType e)
{
	/* ��L�а��ǽ�������µ�����Ԫ��e��L�ĳ��ȼ�1 */
	ElemType* newbase, * p;
	int k;
	if (L.length >= (L.listsize))
	{

		newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
			exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	p = L.elem;
	for (k = 1; k <= L.length; k++)
		if (e > *p)
			p++;
		else
			break;
	ListInsert_Sq(L, k, e);
}


//ɾ������ ɾ��λ��i��Ԫ�� i֮���Ԫ������ǰ��
bool  ListDelete(SqList& L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("λ����Ч������\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//λ��i֮��Ԫ������ǰ�Ƹ���
	{
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;
	return true;
}

ElemType* Sq_Connect(SqList& L1, SqList& L2, SqList& L3) {
	while (L1.length + L2.length > L3.listsize) {
		// ʹ��realloc����L3���ڴ�ռ䣬������Ƿ�ɹ�  
		ElemType* newBase = (ElemType*)realloc(L3.elem, L3.listsize * sizeof(ElemType));
		if (newBase == NULL) {
			// ���realloc����NULL����ʾ�ڴ����ʧ��  
			printf("�ڴ����ʧ�ܣ��޷�����˳���\n");
			exit(EXIT_FAILURE); // ��ֹ����  
		}
		else
			// ���realloc�ɹ�������L3��elemָ���listsize  
			L3.elem = newBase;
	}
	int i = L1.length - 1, j = L2.length - 1, k = 0; //�ɷǵ����ϲ�Ϊ�ǵݼ�������������βָ�룬һ��ͷָ��
	while (i >=0&& j>=0) {
		if (L1.elem[i] >= L2.elem[j]) 
			L3.elem[k++] = L1.elem[i--];
		else 
			L3.elem[k++] = L2.elem[j--];
	}
	while (j>=0) 
		L3.elem[k++] = L2.elem[j--];
	while (i>=0) 
		L3.elem[k++] = L1.elem[i--];
	L3.length = k;
	return L3.elem;
}


/*
int main() {
	//������˳�������������Ԫ�ص�ֵ����д���������Խ����
	SqList L;
	CreatList_Sq(L, 10);
	PrintList(L);
	return 0;
}*/

/*
int main() {
	SqList L;
	CreatList_Sq(L, 10);
	printf("��������Ҫ��λ��ֵ:");
	int fact;
	scanf("%d", &fact);
	int l = LocateElem(L,fact);
	if (l == -1)
		printf("˳������ڸ�ֵ");
	else
		printf("��ֵ��˳����λ��Ϊ%d", l);
	return 0;
}*/

/*
int main() {
	SqList L;
	CreatList_Sq(L, 10);
	int fact;
	printf("��������Ҫ�����ֵ:");
	scanf("%d", &fact);
	InsertAscend(L,fact);
	PrintList(L);
	return 0;
}*/

/*
int main() {
	SqList L;
	CreatList_Sq(L, 10);
	int fact;
	printf("��������Ҫɾ����ֵ:");
	scanf("%d", &fact);
	while (true)
	{
		int l = LocateElem(L, fact);
		if (l == -1) {
			printf("ɾ�����");
			PrintList(L);
			return 0;
		}
		else
			ListDelete(L, l);
	}
}*/

/*
int main() {
	SqList L1, L2, L3;
	InitList_Sq(L3);
	CreatList_Sq(L1, 10);
	CreatList_Sq(L2, 8);
	L3.elem = Sq_Connect(L1, L2, L3);
	PrintList(L3);
	return 0;
}*/