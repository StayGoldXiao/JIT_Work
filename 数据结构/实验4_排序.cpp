#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成随机数
void Random(int array[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        array[i] = rand() % 1000000; // 假设随机数的范围为0到999999
    }
}

// 直接插入排序
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

// 希尔排序
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

//冒泡排序
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

// 快速排序 
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
    // 生成随机数
    Random(array1, SIZE);
    for (int i = 0; i < SIZE; ++i) {
        array2[i] = array1[i]; // 复制一份相同的数据用于希尔排序
        array3[i] = array1[i]; // 复制一份相同的数据用于冒泡排序
        array4[i] = array1[i]; // 复制一份相同的数据用于快速排序
    }
    // 测试直接插入排序的执行时间
    clock_t start = clock();
    insertionSort(array1, SIZE);
    clock_t end = clock();
    double insertionTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("直接插入排序的执行时间：%.6f秒\n", insertionTime);
    // 测试希尔排序的执行时间
    start = clock();
    shellSort(array2, SIZE);
    end = clock();
    double shellTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("希尔排序的执行时间：%.6f秒\n", shellTime);
    // 测试冒泡排序的执行时间
    start = clock();
    bubbleSort(array3, SIZE);
    end = clock();
    double bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("冒泡排序的执行时间：%.6f秒\n", bubbleTime);
    // 测试快速排序的执行时间
    start = clock();
    quickSort(array4, 0, SIZE - 1);
    end = clock();
    double quikTime = (double)(end - start) / CLOCKS_PER_SEC;
    printf("快速排序的执行时间：%.6f秒\n", quikTime);

    return 0;
}*/




// 统计排序
void countingSort(int array[], int n, int v, int w) {
    int range = w - v + 1;
    int* count = (int*)calloc(range, sizeof(int));
    int* result = (int*)malloc(n * sizeof(int));

    // 统计关键字出现的次数
    for (int i = 0; i < n; ++i) 
        count[array[i] - v]++;

    // 根据统计结果重新排序
    int index = 0;
    for (int i = 0; i < range; ++i) 
        for (int j = 0; j < count[i]; ++j)
            result[index++] = i + v;

    // 将排序结果复制回原数组
    for (int i = 0; i < n; ++i) 
        array[i] = result[i];

    // 释放动态分配的内存
    free(count);
    free(result);
}

/*
int main() {
    const int SIZE = 20;
    int array[SIZE];

    // 生成随机数
    srand(time(NULL));
    for (int i = 0; i < SIZE; ++i) {
        array[i] = rand() % 10; // 假设随机数的范围为0到9
    }
    // 输出排序前的数组
    printf("排序前的数组为：\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", array[i]);
    printf("\n");
    // 测试统计排序
    countingSort(array, SIZE, 0, 999);

    // 输出排序后的数组
    printf("排序后的数组为：\n");
    for (int i = 0; i < SIZE; i++)
        printf("%d ",array[i]);

    return 0;
}*/
