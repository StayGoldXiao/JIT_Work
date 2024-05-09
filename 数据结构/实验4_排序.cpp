#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���������
void Random(int array[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 1000000; // ����������ķ�ΧΪ0��999999
    }
}

// ֱ�Ӳ�������
void insertionSort(int array[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// ϣ������
void shellSort(int array[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            int temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] > temp) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
}

//ð������
void bubbleSort(int nums[], int size) {
    for (int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }
}

// �������� 
void swap(int nums[], int i, int j) {
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}
int partition(int nums[], int left, int right) {
    int i = left, j = right;
    while (i < j) {
        while (i < j && nums[j] >= nums[left]) 
            j--;
        while (i < j && nums[i] <= nums[left]) 
            i++; 
        swap(nums, i, j); 
    }
    swap(nums, i, left);
    return i;
}
void quickSort(int nums[], int left, int right) {
    if (left >= right) 
        return;
    int pivot = partition(nums, left, right);
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

/*
int main() {
    const int SIZE = 100000;
    int* array1 = (int*)malloc(SIZE * sizeof(int));
    int* array2 = (int*)malloc(SIZE * sizeof(int));
    int* array3 = (int*)malloc(SIZE * sizeof(int));
    int* array4 = (int*)malloc(SIZE * sizeof(int));
    // ���������
    Random(array1, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        array2[i] = array1[i]; // ����һ����ͬ����������ϣ������
        array3[i] = array1[i]; // ����һ����ͬ����������ð������
        array4[i] = array1[i]; // ����һ����ͬ���������ڿ�������
    }
    // ����ֱ�Ӳ��������ִ��ʱ��
    clock_t start = clock();
    insertionSort(array1, SIZE);
    clock_t end = clock();
    double insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ֱ�Ӳ��������ִ��ʱ�䣺%.6f��\n", insertionTime);
    // ����ϣ�������ִ��ʱ��
    start = clock();
    shellSort(array2, SIZE);
    end = clock();
    double shellTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ϣ�������ִ��ʱ�䣺%.6f��\n", shellTime);
    // ����ð�������ִ��ʱ��
    start = clock();
    bubbleSort(array3, SIZE);
    end = clock();
    double bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("ð�������ִ��ʱ�䣺%.6f��\n", bubbleTime);
    // ���Կ��������ִ��ʱ��
    start = clock();
    quickSort(array4, 0, SIZE - 1);
    end = clock();
    double quikTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("���������ִ��ʱ�䣺%.6f��\n", quikTime);

    return 0;
}*/




// ͳ������
void countingSort(int array[], int n, int v, int w) {
    int range = w - v + 1;
    int* count = (int*)calloc(range, sizeof(int));
    int* result = (int*)malloc(n * sizeof(int));

    // ͳ�ƹؼ��ֳ��ֵĴ���
    for (int i = 0; i < n; ++i) 
        count[array[i] - v]++;

    // ����ͳ�ƽ����������
    int index = 0;
    for (int i = 0; i < range; ++i) 
        for (int j = 0; j < count[i]; ++j)
            result[index++] = i + v;

    // �����������ƻ�ԭ����
    for (int i = 0; i < n; ++i) 
        array[i] = result[i];

    // �ͷŶ�̬������ڴ�
    free(count);
    free(result);
}

/*
int main() {
    const int SIZE = 20;
    int array[SIZE];

    // ���������
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 10; // ����������ķ�ΧΪ0��9
    }
    // �������ǰ������
    printf("����ǰ������Ϊ��\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
    // ����ͳ������
    countingSort(array, SIZE, 0, 999);

    // �������������
    printf("����������Ϊ��\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ",array[i]);

    return 0;
}*/
