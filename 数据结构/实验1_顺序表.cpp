#include <stdio.h>
#include<stdlib.h>

//预定义常量和类型
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
	printf("接下来的 %d 个输入将赋值给顺序表:", n);
	if (n >= L.listsize) {
		int* newbase = (ElemType*)realloc(L.elem, (n) * sizeof(ElemType));
		if (!newbase) return 0;
		L.elem = newbase;//新基址
		L.listsize = n;//增加储存容量
	}
	int* q;
	q = L.elem;               //q为初始位置
	//遍历输入数组元素
	for (int i = 1; i <= n; i++) {//遍历输入数组元素
		int e;
		scanf("%d", &e);
		printf("添加新元素：%d 成功\n", e);
		*q = e;
		q++;
		L.length++;
	}
}

int ListInsert_Sq(SqList& L, int i, ElemType e) {
	if (i<1 || i>L.length + 1) return 0;//插入元素不合法
	if (L.length >= L.listsize) {
		int* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase) printf("新基址分配失败"); return 0;
		L.elem = newbase;
		L.listsize += LISTINCREMENT;
	}
	int* q;
	int* p;
	q = &(L.elem[i - 1]);
	for (p = &(L.elem[L.length - 1]); p >= q; p--) {
		*(p + 1) = *p;
	}
	*q = e;//插入e
	L.length++;
	printf("插入元素：%d 成功\n", e);
	return 1;
}


int GetElem(SqList& L, int i, ElemType e) {
	if (i<1 || i>L.length) printf("输入的值不合法！"); return 0;

	int* p;
	p = L.elem;
	while (i <= L.length && *p != e) {
		i++;
		*p++;
	}
	if (i <= L.length) {
		printf("次序为：%d\n", i);
		return 0;
	}
	else {
		printf("线性表L中查无此值");
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
		//=的优先级高于++
	}
	while (pa < pa_last) *pc++ = *pa++;//插入La的剩余元素
	while (pb < pb_last) *pc++ = *pb++;//插入Lb的剩余元素
}


bool ListEmpty_Sq(SqList L) {
	if (L.length = 0) return true;
	else return false;
	return 0;
}

int ListLength_Sq(SqList& L) {
	//使用L.length即可
	return L.length;
}



void PrintList(SqList L)
{
	printf("当前顺序表所有元素:");
	for (int i = 0; i < L.length; i++)
	{
		printf("%d ", L.elem[i]);
	}
	printf("\n");
}


//按值查找函数，查找第一个值等于e的元素 并返回位置，如果不存在，返回－1
int LocateElem(SqList L, ElemType e)
{
	for (int i = 0; i < L.length; i++)//从低位置查找
	{
		if (L.elem[i] == e)
			return i + 1;
	}
	return -1;
}

void InsertAscend(SqList& L, ElemType e)
{
	/* 在L中按非降序插入新的数据元素e，L的长度加1 */
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


//删除函数 删除位置i的元素 i之后的元素依次前移
bool  ListDelete(SqList& L, int i)
{
	if (i<1 || i>L.length)
	{
		printf("位置无效！！！\n");
		return false;
	}
	for (int j = i; j <= L.length - 1; j++)//位置i之后元素依次前移覆盖
	{
		L.elem[j - 1] = L.elem[j];
	}
	L.length--;
	return true;
}

ElemType* Sq_Connect(SqList& L1, SqList& L2, SqList& L3) {
	while (L1.length + L2.length > L3.listsize) {
		// 使用realloc扩大L3的内存空间，并检查是否成功  
		ElemType* newBase = (ElemType*)realloc(L3.elem, L3.listsize * sizeof(ElemType));
		if (newBase == NULL) {
			// 如果realloc返回NULL，表示内存分配失败  
			printf("内存分配失败，无法连接顺序表。\n");
			exit(EXIT_FAILURE); // 终止程序  
		}
		else
			// 如果realloc成功，更新L3的elem指针和listsize  
			L3.elem = newBase;
	}
	int i = L1.length - 1, j = L2.length - 1, k = 0; //由非递增合并为非递减，故设置两个尾指针，一个头指针
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
	//逐个输出顺序表中所有数据元素的值。编写主函数测试结果。
	SqList L;
	CreatList_Sq(L, 10);
	PrintList(L);
	return 0;
}*/

/*
int main() {
	SqList L;
	CreatList_Sq(L, 10);
	printf("请输入需要定位的值:");
	int fact;
	scanf("%d", &fact);
	int l = LocateElem(L,fact);
	if (l == -1)
		printf("顺序表不存在该值");
	else
		printf("该值在顺序表的位序为%d", l);
	return 0;
}*/

/*
int main() {
	SqList L;
	CreatList_Sq(L, 10);
	int fact;
	printf("请输入需要插入的值:");
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
	printf("请输入需要删除的值:");
	scanf("%d", &fact);
	while (true)
	{
		int l = LocateElem(L, fact);
		if (l == -1) {
			printf("删除完成");
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